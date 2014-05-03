/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010-2013 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2011 Laszlo Papp <lpapp@kde.org>
 * Copyright (c) 2012 Shreya Pandit <shreya@shreyapandit.com>
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
#include <QWidget>
#include <QFileDialog>
#include <QDeclarativeContext>
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
#include <KDE/KApplication>
#include <KDE/KAboutData>

#include <kdeclarative.h>

#include <engine/game.h>
#include <engine/gameproject.h>
#include <engine/scene.h>
#include <engine/gameobject.h>
#include <engine/component.h>

#include <creator/plugin.h>
#include <creator/pluginmanager.h>
#include <creator/objectmanager.h>
#include <creator/historymanager.h>
#include <creator/selectionmanager.h>
#include <creator/dockmanager.h>
#include <creator/filemanager.h>
#include <creator/widgets/filearea.h>

#include "gluoncreatorsettings.h"
#include "dialogs/configdialog.h"
#include "intro/dockeroverlay.h"

using namespace GluonCreator;

class MainWindow::Private
{
    public:
        bool modified;
        QString fileName;
        KRecentFilesAction* recentFiles;

        FileArea* mainArea;
        QDeclarativeView* qmlOverlay;
};

MainWindow::MainWindow( const QString& fileName, QWidget* parent, Qt::WindowFlags flags )
    : KParts::MainWindow( parent, flags ), d( new Private )
{
    kapp->setActiveWindow(this);
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

    DockManager::instance()->setDocksEnabled( false );
    DockManager::instance()->setDocksLocked( GluonCreator::Settings::lockLayout() );

    loadView();

    if( fileName.isEmpty() )
    {
        showWelcomeDialog();
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

QString MainWindow::selectDirectory()
{
    return QFileDialog::getExistingDirectory( this, i18n( "Selection location of project" ) );
}

void MainWindow::openProject( const KUrl& url )
{
    openProject( url.path() );
}

void MainWindow::loadView()
{
    qmlRegisterType< DockerOverlay >( "Gluon.Creator.Introduction", 1, 0, "DockerOverlay" );

    d->qmlOverlay = new QDeclarativeView( this );

    KDeclarative kdeclarative;
    kdeclarative.setDeclarativeEngine( d->qmlOverlay->engine() );
    kdeclarative.initialize();
    kdeclarative.setupBindings();

    d->qmlOverlay->setStyleSheet( "background: transparent" );
    d->qmlOverlay->setResizeMode( QDeclarativeView::SizeRootObjectToView );
    d->qmlOverlay->setGeometry( rect() );

    //TODO: These should really not be context properties. Need to create a proper import plugin for it though, which needs Qt5 due to MainWindow essentially being a singleton.

    d->qmlOverlay->rootContext()->setContextProperty( "mainWindow", this );


    QStringList recentFiles;
    KUrl::List recentUrls = d->recentFiles->urls();
    foreach( const KUrl& url, recentUrls )
    {
        recentFiles.append( url.directory() );
    }

    d->qmlOverlay->rootContext()->setContextProperty( "recentFiles", recentFiles );
}

void MainWindow::openProject( const QString& fileName )
{
    if( d->qmlOverlay->isVisible() )
        d->qmlOverlay->hide();

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
    connect( HistoryManager::instance(), SIGNAL(historyChanged()), SLOT(historyChanged()) );
}

void MainWindow::openRecentProject( int index )
{
    openProject( d->recentFiles->urls().at( index ) );
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
    connect( newProject, SIGNAL(triggered(bool)), SLOT(showWelcomeDialog()) );
    newProject->setShortcut( KShortcut( "Ctrl+N" ) );

    KAction* openProject = new KAction( KIcon( "document-open" ), i18n( "Open Project..." ), actionCollection() );
    actionCollection()->addAction( "project_open", openProject );
    connect( openProject, SIGNAL(triggered(bool)), SLOT(showOpenProjectDialog()) );
    openProject->setShortcut( KShortcut( "Ctrl+O" ) );

    KAction* saveProject = new KAction( KIcon( "document-save" ), i18n( "Save Project" ), actionCollection() );
    actionCollection()->addAction( "project_save", saveProject );
    connect( saveProject, SIGNAL(triggered(bool)), SLOT(saveProject()) );
    saveProject->setShortcut( KShortcut( "Ctrl+S" ) );

    KAction* saveProjectAs = new KAction( KIcon( "document-save-as" ), i18n( "Save Project As..." ), actionCollection() );
    actionCollection()->addAction( "project_save_as", saveProjectAs );
    connect( saveProjectAs, SIGNAL(triggered(bool)), SLOT(saveProjectAs()) );

    KStandardAction::quit( this, SLOT(close()), actionCollection() );
    KStandardAction::preferences( this, SLOT(showPreferences()), actionCollection() );

    KAction* undo = KStandardAction::undo( HistoryManager::instance(), SLOT(undo()), actionCollection() );
    connect( HistoryManager::instance(), SIGNAL(canUndoChanged(bool)), undo, SLOT(setEnabled(bool)) );

    KAction* redo = KStandardAction::redo( HistoryManager::instance(), SLOT(redo()), actionCollection() );
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

void MainWindow::showOpenProjectDialog()
{
    QString fileName = QFileDialog::getOpenFileName( this, i18n( "Open Project" ), QString(), "Gluon Projects (*.gluonproject)" );

    if( !fileName.isEmpty() )
        openProject( fileName );
}

void MainWindow::partChanged( KParts::Part* part )
{
    createGUI( part );

    if( part == FileManager::instance()->part( "view" ) )
    {
        QTimer::singleShot( 100, GluonEngine::Game::instance(), SLOT(drawAll()) );
    }

    //Disable or change shortcuts for actions we want to handle globally.
    QAction* action = part->action( "file_save" );
    if( action )
        action->setShortcut( QKeySequence( "Ctrl+Shift+S" ) );

    action = part->action( "edit_undo" );
    if( action )
        action->setShortcut( QKeySequence() );

    action = part->action( "edit_redo" );
    if( action )
        action->setShortcut( QKeySequence() );

    QList<QAction*> actions = menuBar()->actions();
    foreach( QAction * action, actions )
    {
        if( action->menu() )
        {
            if( action->menu()->actions().count() == 0 )
            {
                action->setVisible( false );
            }
            else
            {
                action->setVisible( true );

                // Glorious-hack-of-the-year: Remove the undo and redo actions from
                // the menu since we handle those globally and do not want to display
                // duplicate actions.
                //
                // This is done after the part has been merged to prevent us either
                // needing to hack the XML or writing a whole bunch of code to add the
                // actions manually. In a way, it is the least of three evils.
                QAction* undoAction = part->action( "edit_undo" );
                QAction* redoAction = part->action( "edit_redo" );

                if( undoAction || redoAction )
                {
                    QList< QAction* > menuActions = action->menu()->actions();
                    foreach( QAction* menuAction, menuActions )
                    {
                        if( menuAction == redoAction )
                            action->menu()->removeAction( menuAction );

                        if( menuAction == undoAction )
                            action->menu()->removeAction( menuAction );
                    }
                }
            }
        }
    }
}

void MainWindow::closeQmlOverlay()
{
    d->qmlOverlay->hide();
}

void MainWindow::createProject( const QString& projectName, const QString& location )
{
    Q_ASSERT( !projectName.isEmpty() );
    Q_ASSERT( !location.isEmpty() );

    QScopedPointer<GluonEngine::GameProject> project( new GluonEngine::GameProject( GluonEngine::Game::instance() ) );
    if( project.isNull() )
    {
        return;
    }

    project->setName( projectName );

    GluonCore::GluonObject* scenesFolder = new GluonCore::GluonObject( "Scenes" );

    GluonEngine::Scene* root = new GluonEngine::Scene( project.data() );
    root->setGameProject( project.data() );
    root->setName( i18n( "New Scene" ) );
    root->savableDirty = true;

    scenesFolder->addChild( root );
    project->setEntryPoint( root );
    project->addChild( scenesFolder );

    GluonEngine::GameObject* camera = new GluonEngine::GameObject( root );
    camera->setName( i18n( "Camera" ) );
    camera->setPosition( 0.0f, 0.0f, 50.0f );
    root->sceneContents()->addChild( camera );

    GluonCore::GluonObject* cameraController =
        GluonCore::GluonObjectFactory::instance()->instantiateObjectByName( "GluonEngine::CameraControllerComponent" );
    cameraController->setName( "CameraController" );
    camera->addComponent( qobject_cast<GluonEngine::Component*>( cameraController ) );

    GluonEngine::GameObject* sprite = new GluonEngine::GameObject( root );
    sprite->setName( i18n( "Sprite" ) );
    sprite->setScale( 10.f, 10.f, 0.f );
    root->sceneContents()->addChild( sprite );

    GluonCore::GluonObject* spriteComponent =
        GluonCore::GluonObjectFactory::instance()->instantiateObjectByName( "GluonEngine::SpriteRendererComponent" );
    spriteComponent->setName( "SpriteRenderer" );
    sprite->addComponent( qobject_cast<GluonEngine::Component*>( spriteComponent ) );

    project->addChild( new GluonCore::GluonObject( "Assets" ) );
    project->addChild( new GluonCore::GluonObject( "Prefabs" ) );

    KUrl locationUrl = KUrl::fromLocalFile( location );
    QString gameBundleDir = GluonEngine::Asset::fullyQualifiedFileName( project.data(), QFileInfo( GluonEngine::projectSuffix ).completeSuffix() );
    locationUrl.addPath( gameBundleDir );
    project->setDirname( locationUrl );
    locationUrl.addPath( GluonEngine::projectFilename );
    project->setFilename( locationUrl );

    KUrl currentLocation = KUrl::fromLocalFile( location );
    currentLocation.addPath( gameBundleDir );
    QDir dir = QDir( location );
    dir.mkpath( gameBundleDir );
    QDir::setCurrent( currentLocation.toLocalFile() );
    project->saveToFile();

    openProject( locationUrl );
}

void MainWindow::showWelcomeDialog()
{
    d->qmlOverlay->show();
    QMetaObject::invokeMethod( this, "switchQmlSource", Qt::QueuedConnection, Q_ARG( QString, "dialogs/WelcomeDialog.qml" ) );
}

void MainWindow::showIntroduction()
{
    d->qmlOverlay->show();
    QMetaObject::invokeMethod( this, "switchQmlSource", Qt::QueuedConnection, Q_ARG( QString, "intro/Introduction.qml" ) );
}

void MainWindow::switchQmlSource( const QString& source )
{
    d->qmlOverlay->setSource( QUrl::fromLocalFile( KGlobal::dirs()->locate( "appdata", source ) ) );
}
