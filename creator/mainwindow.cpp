/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2011 Laszlo Papp <lpapp@kde.org>
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

#include <QtCore/QVariantList>
#include <QtCore/QFileInfo>
#include <QtCore/QTimer>

#include <KDE/KFileDialog>
#include <KDE/KStandardAction>
#include <KDE/KActionCollection>
#include <KDE/KAction>
#include <KDE/KStatusBar>
#include <KDE/KMessageBox>
#include <KDE/KConfigDialog>
#include <KDE/KLocalizedString>
#include <KDE/KRecentFilesAction>
#include <KDE/KParts/PartManager>
#include <KDE/KMenuBar>

#include <engine/game.h>
#include <engine/gameproject.h>
#include <engine/scene.h>

#include "lib/plugin.h"
#include "lib/pluginmanager.h"
#include "lib/objectmanager.h"
#include "lib/historymanager.h"
#include "lib/selectionmanager.h"
#include "lib/dockmanager.h"
#include "lib/filemanager.h"
#include "lib/widgets/filearea.h"

#include "gluoncreatorsettings.h"
#include "dialogs/projectselectiondialog.h"
#include "dialogs/configdialog.h"

using namespace GluonCreator;

class MainWindow::Private
{
    public:
        bool modified;
        QString fileName;
        KRecentFilesAction* recentFiles;
        ProjectSelectionDialog* projectDialog;

        FileArea* mainArea;
};

MainWindow::MainWindow( const QString& fileName, QWidget* parent, Qt::WindowFlags flags )
    : KParts::MainWindow( parent, flags ), d( new Private )
{
    d->modified = false;

    GluonCore::GluonObjectFactory::instance()->loadPlugins();

    DockManager::instance()->setMainWindow( this );

    FileManager::instance()->initialize( this );
    connect( FileManager::instance()->partManager(), SIGNAL(activePartChanged(KParts::Part*)), SLOT(partChanged(KParts::Part*)) );
    connect( FileManager::instance()->partManager(), SIGNAL(activePartChanged(KParts::Part*)), DockManager::instance(), SLOT(updateDockActions()) );

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
    connect( d->projectDialog, SIGNAL(accepted()), SLOT(projectDialogAccepted()) );

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
    GluonCreator::Settings::setLockLayout( actionCollection()->action( "lock_layout" )->isChecked() );
    GluonCreator::Settings::self()->writeConfig();


    if( GluonEngine::Game::instance()->currentScene() )
        GluonEngine::Game::instance()->cleanupAll();
}

void MainWindow::closeEvent( QCloseEvent* event )
{
    GluonEngine::Game::instance()->stopGame();
    QWidget::closeEvent( event );
}

void MainWindow::openProject( const KUrl& url )
{
    openProject( url.path() );
}

void MainWindow::openProject( const QString& fileName )
{
    if( !fileName.isEmpty() && QFile::exists( fileName ) )
    {
        FileManager::instance()->closeAll( true );
        d->fileName = fileName;
        openProject();
    }
    else
    {
        statusBar()->showMessage( i18n( "Unable to open project file..." ) );
    }
}

void MainWindow::openProject()
{
    statusBar()->showMessage( i18n( "Opening project..." ) );
    FileManager::instance()->openFile( d->fileName, "view", i18nc( "View Game Tab", "View" ), QString(), "gluon_viewer_part", QVariantList(), false );
    //TODO: Editor view needs to be implemented
    FileManager::instance()->openFile( d->fileName, "edit", i18nc( "Edit Game Tab", "Edit" ), QString(), "gluon_viewer_part", QVariantList(), false );
    d->mainArea->setActiveTab( "view" );

    GluonEngine::Game::instance()->initializeAll();
    GluonEngine::Game::instance()->drawAll();
    ObjectManager::instance()->watchCurrentAssets();

    d->recentFiles->addUrl( KUrl( d->fileName ) );
    d->recentFiles->saveEntries( KGlobal::config()->group( "Recent Files" ) );

    stateChanged( "fileOpened" );
    DockManager::instance()->setDocksEnabled( true );

    if( centralWidget() )
        centralWidget()->setEnabled( true );

    statusBar()->showMessage( i18n( "Project successfully opened" ) );
    setCaption( i18n( "%1 - Gluon Creator", d->fileName.section( '/', -2, -2 ) ) );

    foreach(GluonEngine::Asset* asset, GluonEngine::Game::instance()->gameProject()->findAssetsByType("GluonEngine::MaterialAsset*"))
    {
        connect(asset, SIGNAL(instanceCreated(GluonGraphics::MaterialInstance*)), ObjectManager::instance(), SLOT(createObjectCommand(GluonGraphics::MaterialInstance*)));
    }

    HistoryManager::instance()->clear();
    connect( HistoryManager::instance(), SIGNAL(historyChanged(const QUndoCommand*)), SLOT(historyChanged()) );
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
        GluonEngine::Game::instance()->gameProject()->setFilename( QUrl::fromLocalFile( fileName ) );
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
    d->fileName = KFileDialog::getSaveFileName( KUrl(), i18n( "*%1|Gluon Project Files", GluonEngine::projectFilename ), 0, QString(), KFileDialog::ConfirmOverwrite );
    if( !d->fileName.isEmpty() )
        saveProject();
}

void MainWindow::setupActions()
{
    KAction* newProject = new KAction( KIcon( "document-new" ), i18n( "New Project..." ), actionCollection() );
    actionCollection()->addAction( "project_new", newProject );
    connect( newProject, SIGNAL(triggered(bool)), SLOT(showNewProjectDialog()) );
    newProject->setShortcut( KShortcut( "Ctrl+Shift+N" ) );

    KAction* openProject = new KAction( KIcon( "document-open" ), i18n( "Open Project..." ), actionCollection() );
    actionCollection()->addAction( "project_open", openProject );
    connect( openProject, SIGNAL(triggered(bool)), SLOT(showOpenProjectDialog()) );
    openProject->setShortcut( KShortcut( "Ctrl+Shift+O" ) );

    KAction* saveProject = new KAction( KIcon( "document-save" ), i18n( "Save Project" ), actionCollection() );
    actionCollection()->addAction( "project_save", saveProject );
    connect( saveProject, SIGNAL(triggered(bool)), SLOT(saveProject()) );
    saveProject->setShortcut( KShortcut( "Ctrl+Shift+S" ) );

    KAction* saveProjectAs = new KAction( KIcon( "document-save-as" ), i18n( "Save Project As..." ), actionCollection() );
    actionCollection()->addAction( "project_save_as", saveProjectAs );
    connect( saveProjectAs, SIGNAL(triggered(bool)), SLOT(saveProjectAs()) );

    KStandardAction::quit( this, SLOT(close()), actionCollection() );
    KStandardAction::preferences( this, SLOT(showPreferences()), actionCollection() );

    KAction* undo = KStandardAction::undo( HistoryManager::instance(), SLOT(undo()), actionCollection() );
    undo->setText( i18n( "Undo Project Action" ) );
    undo->setShortcut( KShortcut( "Ctrl+Alt+Z" ) );
    connect( HistoryManager::instance(), SIGNAL(canUndoChanged(bool)), undo, SLOT(setEnabled(bool)) );

    KAction* redo = KStandardAction::redo( HistoryManager::instance(), SLOT(redo()), actionCollection() );
    redo->setText( i18n( "Redo Project Action" ) );
    undo->setShortcut( KShortcut( "Ctrl+Alt+Shift+Z" ) );
    connect( HistoryManager::instance(), SIGNAL(canRedoChanged(bool)), redo, SLOT(setEnabled(bool)) );

    connect( HistoryManager::instance(), SIGNAL(cleanChanged(bool)), SLOT(cleanChanged(bool)) );

    d->recentFiles = new KRecentFilesAction( KIcon( "document-open-recent" ), i18n( "Recent Projects" ), actionCollection() );
    connect( d->recentFiles, SIGNAL(urlSelected(KUrl)), SLOT(openProject(KUrl)) );
    d->recentFiles->setText( i18n( "Open Recent Project" ) );
    d->recentFiles->setToolTip( i18n( "Open recent project" ) );
    d->recentFiles->setWhatsThis( i18n( "<b>Open recent project</b><p>Opens recently opened project.</p>" ) );
    actionCollection()->addAction( "project_open_recent", d->recentFiles );
    d->recentFiles->loadEntries( KGlobal::config()->group( "Recent Files" ) );

    KAction* newObject = new KAction( KIcon( "document-new" ), i18n( "New Game Object" ), actionCollection() );
    actionCollection()->addAction( "gameobject_new", newObject );
    connect( newObject, SIGNAL(triggered(bool)), ObjectManager::instance(), SLOT(createNewGameObject()) );

    KAction* newScene = new KAction( KIcon( "document-new" ), i18n( "New Scene" ), actionCollection() );
    actionCollection()->addAction( "scene_new", newScene );
    connect( newScene, SIGNAL(triggered(bool)), ObjectManager::instance(), SLOT(createNewScene()) );

    KAction* play = new KAction( KIcon( "media-playback-start" ), i18n( "Play Game" ), actionCollection() );
    actionCollection()->addAction( "game_play", play );
    connect( play, SIGNAL(triggered(bool)), SLOT(playGame()) );

    KAction* pause = new KAction( KIcon( "media-playback-pause" ), i18n( "Pause Game" ), actionCollection() );
    actionCollection()->addAction( "game_pause", pause );
    connect( pause, SIGNAL(triggered(bool)), SLOT(pauseGame()) );

    KAction* stop = new KAction( KIcon( "media-playback-stop" ), i18n( "Stop Game" ), actionCollection() );
    actionCollection()->addAction( "game_stop", stop );
    connect( stop, SIGNAL(triggered(bool)), SLOT(stopGame()) );

    KAction* addAsset = new KAction( KIcon( "document-import" ), i18n( "Import Assets..." ), actionCollection() );
    actionCollection()->addAction( "asset_import", addAsset );
    connect( addAsset, SIGNAL(triggered(bool)), SLOT(addAsset()) );

    KAction* lockLayout = new KAction( KIcon( "object-locked" ), i18n( "Lock layout" ), actionCollection() );
    actionCollection()->addAction( "lock_layout", lockLayout );
    lockLayout->setCheckable( true );
    lockLayout->setChecked( GluonCreator::Settings::lockLayout() );
    connect( lockLayout, SIGNAL(triggered(bool)), DockManager::instance(), SLOT(setDocksLocked(bool)) );
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
    SelectionManager::instance()->clearSelection();
    if( GluonEngine::Game::instance()->isRunning() )
    {
        FileManager::instance()->setCurrentFile( "view" );
        FileManager::instance()->partManager()->activeWidget()->setFocus();

        GluonEngine::Game::instance()->setPause( false );
        stateChanged( "paused", StateReverse );
    }
    else
    {
        stateChanged( "playing" );

        d->mainArea->setActiveTab( "view" );

        QString currentSceneName = GluonEngine::Game::instance()->currentScene()->fullyQualifiedName();
        saveProject();

        //Set the focus to the entire window, so that we do not accidentally trigger actions
        FileManager::instance()->setCurrentFile( "view" );
        FileManager::instance()->partManager()->activeWidget()->setFocus();

        //Start the game loop
        //Note that this starts an infinite loop in Game
        GluonEngine::Game::instance()->runGame();

        //This happens after we exit the game loop
        stateChanged( "playing", StateReverse );

        setFocus();
        GluonEngine::GameProject* oldProject = GluonEngine::Game::instance()->gameProject();
        GluonEngine::Game::instance()->setGameProject(0);
        FileManager::instance()->closeFile("view", true);
        delete oldProject;
        openProject( );
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
    ObjectManager::instance()->createAssets( KFileDialog::getOpenFileNames() );
}

void GluonCreator::MainWindow::showNewProjectDialog()
{
    d->projectDialog->setPage( ProjectSelectionDialog::NewProjectPage );
    d->projectDialog->show();
}

void MainWindow::showOpenProjectDialog()
{
    d->projectDialog->setPage( ProjectSelectionDialog::OpenProjectPage );
    d->projectDialog->show();
}

void MainWindow::projectDialogAccepted()
{
    openProject( d->projectDialog->fileName() );
}

void MainWindow::partChanged( KParts::Part* part )
{
    createGUI( part );

    if( part == FileManager::instance()->part( "view" ) )
    {
        QTimer::singleShot( 100, GluonEngine::Game::instance(), SLOT(drawAll()) );
    }

    QList<QAction*> actions = menuBar()->actions();
    foreach( QAction * action, actions )
    {
        if( action->menu() && action->menu()->actions().count() == 0 )
        {
            action->setVisible( false );
        }
        else
        {
            action->setVisible( true );
        }
    }
}

