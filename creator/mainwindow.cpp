/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2011 Laszlo Papp <djszapi@archlinux.us>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "mainwindow.h"

#include "lib/plugin.h"
#include "lib/pluginmanager.h"
#include "lib/objectmanager.h"
#include "lib/historymanager.h"
#include "lib/selectionmanager.h"
#include "lib/dockmanager.h"
#include "lib/filemanager.h"
#include "lib/widgets/filearea.h"

#include "gluoncreatorsettings.h"
#include "dialogs/configdialog.h"

#include "core/debughelper.h"
#include "engine/game.h"
#include "engine/gameproject.h"
#include "engine/scene.h"

#include <KDE/KFileDialog>
#include <KDE/KStandardAction>
#include <KDE/KActionCollection>
#include <KDE/KAction>
#include <KDE/KStatusBar>
#include <KDE/KMessageBox>
#include <KDE/KConfigDialog>
#include <KDE/KLocalizedString>
#include <KDE/KPluginSelector>
#include <KDE/KRun>
#include <KDE/KRecentFilesAction>
#include <KDE/KToolBar>
#include <KDE/KRichTextEdit>
#include <KDE/KParts/PartManager>
#include <KDE/KMenuBar>

#include <QtGui/QVBoxLayout>
#include <QtCore/QVariantList>
#include <QtCore/QFileInfo>

using namespace GluonCreator;

class MainWindow::MainWindowPrivate
{
    public:
        MainWindowPrivate()
        {
        }

        bool modified;
        QString fileName;
        KRecentFilesAction* recentFiles;
        ProjectSelectionDialog* projectDialog;

        FileArea* mainArea;
};

MainWindow::MainWindow( const QString& fileName )
    : KParts::MainWindow()
    , d( new MainWindowPrivate )
{
    d->modified = false;

    GluonCore::GluonObjectFactory::instance()->loadPlugins();

    PluginManager::instance()->setParent( this );
    ObjectManager::instance()->setParent( this );
    HistoryManager::instance()->setParent( this );
    SelectionManager::instance()->setParent( this );

    DockManager::instance()->setParent( this );
    DockManager::instance()->setMainWindow( this );

    FileManager::instance()->initialize( this );
    connect( FileManager::instance()->partManager(), SIGNAL( activePartChanged( KParts::Part* ) ), SLOT( createGUI( KParts::Part* ) ) );
    connect( FileManager::instance()->partManager(), SIGNAL(activePartChanged(KParts::Part*)), SLOT(partChanged(KParts::Part*)));

    PluginManager::instance()->setMainWindow( this );
    PluginManager::instance()->loadPlugins();

    setDockNestingEnabled( true );
    setCorner( Qt::TopLeftCorner, Qt::LeftDockWidgetArea );
    setCorner( Qt::BottomLeftCorner, Qt::LeftDockWidgetArea );
    setCorner( Qt::TopRightCorner, Qt::RightDockWidgetArea );
    setCorner( Qt::BottomRightCorner, Qt::RightDockWidgetArea );

    d->mainArea = new FileArea( this );
    setCentralWidget( d->mainArea );

    setupActions();
    setupGUI();
    stateChanged( "initial" );

    d->projectDialog = new ProjectSelectionDialog( this );
    d->projectDialog->setModal( true );
    d->projectDialog->raise( );
    connect( d->projectDialog, SIGNAL( accepted() ), SLOT( projectDialogAccepted() ) );

    DockManager::instance()->setDocksEnabled( false );
    DockManager::instance()->setDocksLocked( GluonCreator::Settings::lockLayout() );

    if( fileName.isEmpty() )
    {
        showNewProjectDialog();
    }
    else
    {
        QFileInfo fi = QFileInfo( fileName );
        if( fi.isRelative() )
            openProject( fi.canonicalFilePath() );
        else
            openProject( fileName );
    }
}

MainWindow::~MainWindow()
{
    d->recentFiles->saveEntries( KGlobal::config()->group( "Recent Files" ) );
    GluonCreator::Settings::setLockLayout( actionCollection()->action( "lockLayout" )->isChecked() );
    GluonCreator::Settings::self()->writeConfig();
}

void MainWindow::closeEvent( QCloseEvent* event )
{
    GluonEngine::Game::instance()->stopGame();
    QWidget::closeEvent( event );
}

void MainWindow::openProject( KUrl url )
{
    openProject( url.path() );
}

void MainWindow::openProject( const QString& fileName )
{
    if( !fileName.isEmpty() && QFile::exists( fileName ) )
    {
        FileManager::instance()->closeFile("view");

        statusBar()->showMessage( i18n( "Opening project..." ) );
        FileManager::instance()->openFile( fileName, "view", i18nc( "View Game Tab", "view" ), "gluon_viewer_part", QVariantList() << QString( "autoplay=false" ) );

        GluonEngine::Game::instance()->initializeAll();
        GluonEngine::Game::instance()->drawAll();
        ObjectManager::instance()->watchCurrentAssets();

        d->fileName = fileName;
        d->recentFiles->addUrl( KUrl( fileName ) );

        stateChanged( "fileOpened" );
        DockManager::instance()->setDocksEnabled( true );

        if( centralWidget() )
            centralWidget()->setEnabled( true );

        statusBar()->showMessage( i18n( "Project successfully opened" ) );
        setCaption( i18n( "%1 - Gluon Creator", fileName.section( '/', -1 ) ) );
        HistoryManager::instance()->clear();
        connect( HistoryManager::instance(), SIGNAL( historyChanged( const QUndoCommand* ) ), SLOT( historyChanged() ) );
    }
    else
    {
        statusBar()->showMessage( i18n( "Unable to open project file..." ) );
    }
}

void MainWindow::saveProject()
{
    saveProject( d->fileName );
}

void MainWindow::saveProject( const QString& fileName )
{
    if( !fileName.isEmpty() )
    {
        statusBar()->showMessage( i18n( "Saving project..." ) );
        GluonEngine::Game::instance()->gameProject()->setFilename( QUrl( fileName ) );
        QDir::setCurrent( KUrl( fileName ).directory() );
        if( !GluonEngine::Game::instance()->gameProject()->saveToFile() )
        {
            KMessageBox::error( this, i18n( "Could not save file." ) );
            return;
        }
        statusBar()->showMessage( i18n( "Project successfully saved." ) );
        setCaption( i18n( "%1 - Gluon Creator", fileName.section( '/', -1 ) ) );
        HistoryManager::instance()->setClean();

        d->recentFiles->addUrl( KUrl( fileName ) );
    }
    else
    {
        saveProjectAs();
    }
}

void MainWindow::saveProjectAs()
{
    d->fileName = KFileDialog::getSaveFileName( KUrl(), i18n( "*%1|Gluon Project Files" ).arg( GluonEngine::projectSuffix ), 0, QString(), KFileDialog::ConfirmOverwrite );
    if( !d->fileName.isEmpty() )
        saveProject();
}

void MainWindow::setupActions()
{
    KStandardAction::openNew( this, SLOT( showNewProjectDialog() ), actionCollection() );
    KStandardAction::open( this, SLOT( showOpenProjectDialog() ), actionCollection() );
    KStandardAction::save( this, SLOT( saveProject() ), actionCollection() );
    KStandardAction::saveAs( this, SLOT( saveProjectAs() ), actionCollection() );
    KStandardAction::quit( this, SLOT( close() ), actionCollection() );
    KStandardAction::preferences( this, SLOT( showPreferences() ), actionCollection() );

    KAction* undo = KStandardAction::undo( HistoryManager::instance(), SLOT( undo() ), actionCollection() );
    connect( HistoryManager::instance(), SIGNAL( canUndoChanged( bool ) ), undo, SLOT( setEnabled( bool ) ) );

    KAction* redo = KStandardAction::redo( HistoryManager::instance(), SLOT( redo() ), actionCollection() );
    connect( HistoryManager::instance(), SIGNAL( canRedoChanged( bool ) ), redo, SLOT( setEnabled( bool ) ) );

    connect( HistoryManager::instance(), SIGNAL( cleanChanged( bool ) ), SLOT( cleanChanged( bool ) ) );

    d->recentFiles = KStandardAction::openRecent( this, SLOT( openProject( KUrl ) ), actionCollection() );
    d->recentFiles->loadEntries( KGlobal::config()->group( "Recent Files" ) );

    KAction* newObject = new KAction( KIcon( "document-new" ), i18n( "New Object" ), actionCollection() );
    actionCollection()->addAction( "newObject", newObject );
    connect( newObject, SIGNAL( triggered( bool ) ), ObjectManager::instance(), SLOT( createNewGameObject() ) );

    KAction* newScene = new KAction( KIcon( "document-new" ), i18n( "New Scene" ), actionCollection() );
    actionCollection()->addAction( "newScene", newScene );
    connect( newScene, SIGNAL( triggered( bool ) ), ObjectManager::instance(), SLOT( createNewScene() ) );

    KAction* play = new KAction( KIcon( "media-playback-start" ), i18n( "Play Game" ), actionCollection() );
    actionCollection()->addAction( "playGame", play );
    connect( play, SIGNAL( triggered( bool ) ), SLOT( playGame() ) );

    KAction* pause = new KAction( KIcon( "media-playback-pause" ), i18n( "Pause Game" ), actionCollection() );
    actionCollection()->addAction( "pauseGame", pause );
    connect( pause, SIGNAL( triggered( bool ) ), SLOT( pauseGame() ) );

    KAction* stop = new KAction( KIcon( "media-playback-stop" ), i18n( "Stop Game" ), actionCollection() );
    actionCollection()->addAction( "stopGame", stop );
    connect( stop, SIGNAL( triggered( bool ) ), SLOT( stopGame() ) );

    KAction* addAsset = new KAction( KIcon( "document-new" ), i18n( "Add Assets..." ), actionCollection() );
    actionCollection()->addAction( "addAsset", addAsset );
    connect( addAsset, SIGNAL( triggered( bool ) ), SLOT( addAsset() ) );

    KAction* chooseEntryPoint = new KAction( KIcon( "media-playback-start" ), i18n( "Set current scene as entry point" ), actionCollection() );
    actionCollection()->addAction( "chooseEntryPoint", chooseEntryPoint );
    connect( chooseEntryPoint, SIGNAL( triggered( bool ) ), SLOT( chooseEntryPoint() ) );

    KAction* lockLayout = new KAction( KIcon( "object-locked" ), i18n( "Lock layout" ), actionCollection() );
    actionCollection()->addAction( "lockLayout", lockLayout );
    lockLayout->setCheckable( true );
    lockLayout->setChecked( GluonCreator::Settings::lockLayout() );
    connect( lockLayout, SIGNAL( triggered( bool ) ), DockManager::instance(), SLOT( setDocksLocked( bool ) ) );
}

void MainWindow::showPreferences()
{
    if( KConfigDialog::showDialog( "settings" ) )
    {
        return;
    }
    ConfigDialog* dialog = new ConfigDialog( this, "settings", GluonCreator::Settings::self() );
    dialog->setAttribute( Qt::WA_DeleteOnClose );
    dialog->show();
}

void MainWindow::playGame( )
{
    if( GluonEngine::Game::instance()->isRunning() )
    {
        GluonEngine::Game::instance()->setPause( false );
        stateChanged( "paused", StateReverse );
    }
    else
    {
        stateChanged( "playing" );

        d->mainArea->setActiveTab( 0 );

        QString currentSceneName = GluonEngine::Game::instance()->currentScene()->fullyQualifiedName();
        saveProject();

        //Set the focus to the entire window, so that we do not accidentally trigger actions
        FileManager::instance()->setCurrentFile(i18nc("View Game Tab", "view"));
        FileManager::instance()->partManager()->activeWidget()->setFocus();

        //Start the game loop
        //Note that this starts an infinite loop in Game
        GluonEngine::Game::instance()->runGame();

        //This happens after we exit the game loop
        stateChanged( "playing", StateReverse );

        setFocus();
        openProject( d->fileName );
        GluonEngine::Game::instance()->setCurrentScene( currentSceneName );
        GluonEngine::Game::instance()->initializeAll();
    }
}

void MainWindow::pauseGame()
{
    GluonEngine::Game::instance()->setPause( true );
    stateChanged( "paused" );
}

void MainWindow::stopGame()
{
    GluonEngine::Game::instance()->stopGame();
}

void MainWindow::historyChanged()
{
    GluonEngine::Game::instance()->drawAll();
    GluonEngine::Game::instance()->currentScene()->savableDirty = true;
    d->modified = true;

    setCaption( i18n( "%1 [modified]", d->fileName.isEmpty() ? i18n( "New Project" ) : d->fileName.section( '/', -1 ) ) );
}

void MainWindow::cleanChanged( bool clean )
{
    if( clean )
    {
        d->modified = false;
        setCaption( i18n( "%1", d->fileName.isEmpty() ? i18n( "New Project" ) : d->fileName.section( '/', -1 ) ) );
    }
}

bool MainWindow::queryClose()
{
    if( d->modified )
    {
        int code = KMessageBox::questionYesNoCancel( this, i18n( "The project has been changed. Do you want to save before closing?" ), i18n( "Save Before Closing?" ),
                   KStandardGuiItem::save(), KStandardGuiItem::dontSave() );

        if( code == KMessageBox::Cancel )
            return false;

        if( code == KMessageBox::No )
            return true;

        saveProject();
        return true;
    }

    return true;
}

void MainWindow::addAsset()
{
    QStringList assets = KFileDialog::getOpenFileNames();

    foreach( const QString & asset, assets )
    {
        ObjectManager::instance()->createNewAsset( asset );
    }
}

void MainWindow::chooseEntryPoint()
{
    if( GluonEngine::Game::instance()->gameProject() )
    {
        if( GluonEngine::Game::instance()->currentScene() )
        {
            GluonEngine::Game::instance()->gameProject()->setEntryPoint( GluonEngine::Game::instance()->currentScene() );
        }
    }
}

void GluonCreator::MainWindow::showNewProjectDialog()
{
    d->projectDialog->setPage( ProjectSelectionDialog::NewProjectPage );
    d->projectDialog->show();
}

void GluonCreator::MainWindow::showOpenProjectDialog()
{
    d->projectDialog->setPage( ProjectSelectionDialog::OpenProjectPage );
    d->projectDialog->show();
}

void GluonCreator::MainWindow::projectDialogAccepted()
{
    openProject( d->projectDialog->fileName() );
}

void MainWindow::initializeGame()
{
}

void MainWindow::partChanged(KParts::Part* part )
{
    if(part == FileManager::instance()->part("view"))
    {
        QTimer::singleShot(100, GluonEngine::Game::instance(), SLOT(drawAll()));
    }

    QList<QAction*> actions = menuBar()->actions();
    foreach(QAction* action, actions)
    {
        if(action->menu() && action->menu()->actions().count() == 0)
        {
            action->setVisible(false);
        }
        else
        {
            action->setVisible(true);
        }
    }
}

