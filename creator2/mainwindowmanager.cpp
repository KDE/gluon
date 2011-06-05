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

#include "mainwindowmanager.h"

#include "lib/plugin.h"
#include "lib/pluginmanager.h"
#include "lib/objectmanager.h"
#include "lib/historymanager.h"
#include "lib/selectionmanager.h"
#include "lib/viewmanager.h"
#include "lib/filemanager.h"
#include "lib/widgets/filearea.h"

#include "gluoncreatorsettings.h"
#include "dialogs/configdialog.h"

#include <engine/game.h>
#include <engine/gameproject.h>
#include <engine/scene.h>

#include <interfaces/icore.h>
#include <interfaces/iuicontroller.h>
#include <interfaces/idocumentcontroller.h>

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
#include <KDE/KXMLGUIFactory>

#include <QtGui/QVBoxLayout>
#include <QtCore/QVariantList>
#include <QtCore/QFileInfo>

using namespace GluonCreator;

class MainWindowManager::MainWindowManagerPrivate
{
    public:
        MainWindowManagerPrivate()
        {
        }

        bool modified;
        QString fileName;
        KRecentFilesAction* recentFiles;
        ProjectSelectionDialog* projectDialog;

        KParts::MainWindow *mainWindow;
        // GluonEngine::GameProject* project;
};

MainWindowManager::MainWindowManager( QObject *parent )
    : QObject(parent), KXMLGUIClient()
    , d( new MainWindowManagerPrivate )
{
    d->mainWindow = KDevelop::ICore::self()->uiController()->activeMainWindow();

    d->modified = false;

    GluonCore::GluonObjectFactory::instance()->loadPlugins();

    PluginManager::instance()->setParent( d->mainWindow );
    ObjectManager::instance()->setParent( d->mainWindow );
    HistoryManager::instance()->setParent( d->mainWindow );
    SelectionManager::instance()->setParent( d->mainWindow );

    ViewManager::instance()->setParent( d->mainWindow );
    ViewManager::instance()->setMainWindow( d->mainWindow );

    FileManager::instance()->initialize( d->mainWindow );

    PluginManager::instance()->setMainWindow( d->mainWindow );
    PluginManager::instance()->loadPlugins();

    setupActions();
    d->mainWindow->guiFactory()->addClient(this);

    stateChanged( "initial" );

    d->projectDialog = new ProjectSelectionDialog( d->mainWindow );
    d->projectDialog->setModal( true );
    d->projectDialog->raise( );
    connect( d->projectDialog, SIGNAL( accepted() ), SLOT( projectDialogAccepted() ) );

    ViewManager::instance()->setViewsEnabled( false );

    // if( fileName.isEmpty() )
    // {
        showNewProjectDialog();
    // }
    // else
    // {
        // QFileInfo fi = QFileInfo( fileName );
        // if( fi.isRelative() )
            // openProject( fi.canonicalFilePath() );
        // else
            // openProject( fileName );
    // }
}

MainWindowManager::~MainWindowManager()
{
    d->recentFiles->saveEntries( KGlobal::config()->group( "Recent Files" ) );
        // GluonCreator::Settings::setLockLayout( actionCollection()->action( "lock_layout" )->isChecked() );
        GluonCreator::Settings::self()->writeConfig();
}

// void MainWindowManager::closeEvent( QCloseEvent* event )
// {
    // GluonEngine::Game::instance()->stopGame();
    // QWidget::closeEvent( event );
// }

void MainWindowManager::openProject( KUrl url )
{
    openProject( url.path() );
}

void MainWindowManager::openProject( const QString& fileName )
{
    if( !fileName.isEmpty() && QFile::exists( fileName ) )
    {
        FileManager::instance()->closeFile( "view" );
        // FileManager::instance()->closeFile( "edit" );

        d->mainWindow->statusBar()->showMessage( i18n( "Opening project..." ) );

        KDevelop::ICore::self()->documentController()->openDocument(fileName);

        GluonEngine::Game::instance()->initializeAll();
        GluonEngine::Game::instance()->drawAll();
        ObjectManager::instance()->watchCurrentAssets();

        d->fileName = fileName;
        // d->recentFiles->addUrl( KUrl( fileName ) );

        stateChanged( "fileOpened" );
        ViewManager::instance()->setViewsEnabled( true );

        d->mainWindow->statusBar()->showMessage( i18n( "Project successfully opened" ) );
        d->mainWindow->setCaption( i18n( "%1 - Gluon Creator", fileName.section( '/', -2, -2 ) ) );
        HistoryManager::instance()->clear();
        connect( HistoryManager::instance(), SIGNAL( historyChanged( const QUndoCommand* ) ), SLOT( historyChanged() ) );
    }
    else
    {
        d->mainWindow->statusBar()->showMessage( i18n( "Unable to open project file..." ) );
    }
}

void MainWindowManager::saveProject()
{
    saveProject( d->fileName );
}

void MainWindowManager::saveProject( const QString& fileName )
{
    if( !fileName.isEmpty() )
    {
        d->mainWindow->statusBar()->showMessage( i18n( "Saving project..." ) );
        GluonEngine::Game::instance()->gameProject()->setFilename( QUrl( fileName ) );
        QDir::setCurrent( KUrl( fileName ).directory() );
        if( !GluonEngine::Game::instance()->gameProject()->saveToFile() )
        {
            KMessageBox::error( d->mainWindow, i18n( "Could not save file." ) );
            return;
        }

        d->mainWindow->statusBar()->showMessage( i18n( "Project successfully saved." ) );
        d->mainWindow->setCaption( i18n( "%1 - Gluon Creator", fileName.section( '/', -1 ) ) );
        HistoryManager::instance()->setClean();

        d->recentFiles->addUrl( KUrl( fileName ) );
    }
    else
    {
        saveProjectAs();
    }
}

void MainWindowManager::saveProjectAs()
{
    d->fileName = KFileDialog::getSaveFileName( KUrl(), i18n( "*%1|Gluon Project Files", GluonEngine::projectFilename ), 0, QString(), KFileDialog::ConfirmOverwrite );
    if( !d->fileName.isEmpty() )
        saveProject();
}

void MainWindowManager::setupActions()
{
    setComponentData(KComponentData("gluoncreator", "gluoncreator"));
    KActionCollection* actCollection = actionCollection();

    KAction* newProject = new KAction( KIcon( "document-new" ), i18n( "New Project..." ), actCollection );
    actCollection->addAction( "project_new", newProject );
    connect( newProject, SIGNAL( triggered( bool ) ), SLOT( showNewProjectDialog() ) );
    newProject->setShortcut( KShortcut( "Ctrl+Shift+N" ) );

    KAction* openProject = new KAction( KIcon( "document-open" ), i18n( "Open Project..." ), actCollection );
    actCollection->addAction( "project_open", openProject );
    connect( openProject, SIGNAL( triggered( bool ) ), SLOT( showOpenProjectDialog() ) );
    openProject->setShortcut( KShortcut( "Ctrl+Shift+O" ) );

    KAction* saveProject = new KAction( KIcon( "document-save" ), i18n( "Save Project" ), actCollection );
    actCollection->addAction( "project_save", saveProject );
    connect( saveProject, SIGNAL( triggered( bool ) ), SLOT( saveProject() ) );
    saveProject->setShortcut( KShortcut( "Ctrl+Shift+S" ) );

    KAction* saveProjectAs = new KAction( KIcon( "document-save-as" ), i18n( "Save Project As..." ), actCollection );
    actCollection->addAction( "project_save_as", saveProjectAs );
    connect( saveProjectAs, SIGNAL( triggered( bool ) ), SLOT( saveProjectAs() ) );

    KStandardAction::quit( this, SLOT( close() ), actCollection );
    KStandardAction::preferences( this, SLOT( showPreferences() ), actCollection );

    KAction* undo = KStandardAction::undo( HistoryManager::instance(), SLOT( undo() ), actCollection );
    undo->setText( i18n( "Undo Project Action" ) );
    undo->setShortcut( KShortcut( "Ctrl+Alt+Z" ) );
    connect( HistoryManager::instance(), SIGNAL( canUndoChanged( bool ) ), undo, SLOT( setEnabled( bool ) ) );

    KAction* redo = KStandardAction::redo( HistoryManager::instance(), SLOT( redo() ), actCollection );
    redo->setText( i18n( "Redo Project Action" ) );
    undo->setShortcut( KShortcut( "Ctrl+Alt+Shift+Z" ) );
    connect( HistoryManager::instance(), SIGNAL( canRedoChanged( bool ) ), redo, SLOT( setEnabled( bool ) ) );

    connect( HistoryManager::instance(), SIGNAL( cleanChanged( bool ) ), SLOT( cleanChanged( bool ) ) );

    d->recentFiles = new KRecentFilesAction( KIcon( "document-open-recent" ), i18n( "Recent Projects" ), actCollection );
    connect( d->recentFiles, SIGNAL( urlSelected( const KUrl& ) ), SLOT( openProject( const KUrl& ) ) );
    d->recentFiles->setText( i18n( "Open Recent Project" ) );
    d->recentFiles->setToolTip( i18n( "Open recent project" ) );
    d->recentFiles->setWhatsThis( i18n( "<b>Open recent project</b><p>Opens recently opened project.</p>" ) );
    actCollection->addAction( "project_open_recent", d->recentFiles );
    d->recentFiles->loadEntries( KGlobal::config()->group( "Recent Files" ) );

    KAction* newObject = new KAction( KIcon( "document-new" ), i18n( "New Game Object" ), actCollection );
    actCollection->addAction( "gameobject_new", newObject );
    connect( newObject, SIGNAL( triggered( bool ) ), ObjectManager::instance(), SLOT( createNewGameObject() ) );

    KAction* newScene = new KAction( KIcon( "document-new" ), i18n( "New Scene" ), actCollection );
    actCollection->addAction( "scene_new", newScene );
    connect( newScene, SIGNAL( triggered( bool ) ), ObjectManager::instance(), SLOT( createNewScene() ) );

    KAction* play = new KAction( KIcon( "media-playback-start" ), i18n( "Play Game" ), actCollection );
    actCollection->addAction( "game_play", play );
    connect( play, SIGNAL( triggered( bool ) ), SLOT( playGame() ) );

    KAction* pause = new KAction( KIcon( "media-playback-pause" ), i18n( "Pause Game" ), actCollection );
    actCollection->addAction( "game_pause", pause );
    connect( pause, SIGNAL( triggered( bool ) ), SLOT( pauseGame() ) );

    KAction* stop = new KAction( KIcon( "media-playback-stop" ), i18n( "Stop Game" ), actCollection );
    actCollection->addAction( "game_stop", stop );
    connect( stop, SIGNAL( triggered( bool ) ), SLOT( stopGame() ) );

    // KAction* addAsset = new KAction( KIcon( "document-import" ), i18n( "Import Assets..." ), actCollection );
    // actCollection->addAction( "asset_import", addAsset );
    // connect( addAsset, SIGNAL( triggered( bool ) ), SLOT( addAsset() ) );
    setXMLFile("gluoncreatorui.rc");
}

// void MainWindowManager::showPreferences()
// {
    // if( KConfigDialog::showDialog( "settings" ) )
    // {
        // return;
    // }
    // ConfigDialog* dialog = new ConfigDialog( this, "settings", GluonCreator::Settings::self() );
    // dialog->setAttribute( Qt::WA_DeleteOnClose );
    // dialog->show();
// }

void MainWindowManager::playGame( )
{
    if( GluonEngine::Game::instance()->isRunning() )
    {
        FileManager::instance()->setCurrentFile( "view" );
        // FileManager::instance()->partManager()->activeWidget()->setFocus();

        GluonEngine::Game::instance()->setPause( false );
        stateChanged( "paused", StateReverse );
    }
    else
    {
        stateChanged( "playing" );

        // d->mainArea->setActiveTab( "view" );

        QString currentSceneName = GluonEngine::Game::instance()->currentScene()->fullyQualifiedName();
        saveProject();

        // Set the focus to the entire window, so that we do not accidentally trigger actions
        FileManager::instance()->setCurrentFile( "view" );
        // FileManager::instance()->partManager()->activeWidget()->setFocus();

        // Start the game loop
        // Note that this starts an infinite loop in Game
        GluonEngine::Game::instance()->runGame();

        // This happens after we exit the game loop
        stateChanged( "playing", StateReverse );

        // d->mainWindow->setFocus();
        openProject( d->fileName );
        GluonEngine::Game::instance()->setCurrentScene( currentSceneName );
        GluonEngine::Game::instance()->initializeAll();
    }
}

void MainWindowManager::pauseGame()
{
    GluonEngine::Game::instance()->setPause( true );
    stateChanged( "paused" );
}

void MainWindowManager::stopGame()
{
    GluonEngine::Game::instance()->stopGame();
}

// void MainWindowManager::historyChanged()
// {
    // GluonEngine::Game::instance()->drawAll();
    // GluonEngine::Game::instance()->currentScene()->savableDirty = true;
    // d->modified = true;

    // setCaption( i18n( "%1 [modified]", d->fileName.isEmpty() ? i18n( "New Project" ) : d->fileName.section( '/', -1 ) ) );
// }

// void MainWindowManager::cleanChanged( bool clean )
// {
    // if( clean )
    // {
        // d->modified = false;
        // setCaption( i18n( "%1", d->fileName.isEmpty() ? i18n( "New Project" ) : d->fileName.section( '/', -1 ) ) );
    // }
// }

// bool MainWindowManager::queryClose()
// {
    // if( d->modified )
    // {
        // int code = KMessageBox::questionYesNoCancel( this, i18n( "The project has been changed. Do you want to save before closing?" ), i18n( "Save Before Closing?" ),
                   // KStandardGuiItem::save(), KStandardGuiItem::dontSave() );

        // if( code == KMessageBox::Cancel )
            // return false;

        // if( code == KMessageBox::No )
            // return true;

        // saveProject();
        // return true;
    // }

    // return true;
// }

// void MainWindowManager::addAsset()
// {
    // ObjectManager::instance()->createAssets( KFileDialog::getOpenFileNames() );
// }

void MainWindowManager::showNewProjectDialog()
{
    d->projectDialog->setPage( ProjectSelectionDialog::NewProjectPage );
    d->projectDialog->show();
}

void MainWindowManager::showOpenProjectDialog()
{
    d->projectDialog->setPage( ProjectSelectionDialog::OpenProjectPage );
    d->projectDialog->show();
}

void MainWindowManager::projectDialogAccepted()
{
    openProject( d->projectDialog->fileName() );
}

void MainWindowManager::initializeGame()
{
}

// void MainWindowManager::partChanged( KParts::Part* part )
// {
    // if( part == FileManager::instance()->part( "view" ) )
    // {
        // QTimer::singleShot( 100, GluonEngine::Game::instance(), SLOT( drawAll() ) );
    // }

    // QList<QAction*> actions = menuBar()->actions();
    // foreach( QAction * action, actions )
    // {
        // if( action->menu() && action->menu()->actions().count() == 0 )
        // {
            // action->setVisible( false );
        // }
        // else
        // {
            // action->setVisible( true );
        // }
    // }
// }

