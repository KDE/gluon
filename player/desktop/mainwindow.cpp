/*****************************************************************************
 * This file is part of the Gluon Development Platform                       *
 * Copyright (c) 2011 Laszlo Papp <lpapp@kde.org>                     *
 *                                                                           *
 * This program is free software; you can redistribute it and/or modify      *
 * it under the terms of the GNU General Public License as published by      *
 * the Free Software Foundation; either version 2 of the License, or         *
 * (at your option) any later version.                                       *
 *                                                                           *
 * This program is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 * GNU General Public License for more details.                              *
 *                                                                           *
 * You should have received a copy of the GNU General Public License along   *
 * with this program; if not, write to the Free Software Foundation, Inc.,   *
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.               *
 *****************************************************************************/

#include "mainwindow.h"

#include "lib/models/gameitemsmodel.h"

#include <input/inputmanager.h>

#include <engine/game.h>
#include <engine/gameproject.h>
#include <engine/scene.h>
#include <engine/gamesave.h>
#include <graphics/renderwidget.h>

#include <KDE/KPushButton>
#include <KDE/KFileDialog>
#include <KDE/KUrl>
#include <KDE/KLocalizedString>
#include <KDE/KMenuBar>
#include <KDE/KToolBar>
#include <KDE/KStatusBar>
#include <KDE/KAction>
#include <KDE/KActionCollection>
#include <KDE/KStandardAction>
#include <KDE/KConfig>
#include <KDE/KShortcutsDialog>
#include <KDE/KEditToolBar>

#include <QtGui/QStatusBar>
#include <QtGui/QListView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>
#include <QtCore/QTimer>
#include <QtCore/QDebug>

using namespace GluonKDEPlayer;

class MainWindow::MainWindowPrivate
{
    public:
        MainWindowPrivate() : msecElapsed( 0 ), frameCount( 0 ) {}
        ~MainWindowPrivate() {}

        GluonGraphics::RenderWidget* widget;

        QString title;
        QString fileName;

        int msecElapsed;
        int frameCount;
};

MainWindow::MainWindow( const QString& /* filename */ )
    : KXmlGuiWindow()
    , d( new MainWindowPrivate )
    , m_gamesOverlay( new GamesOverlay( this ) )
    , m_layout( new QGridLayout )
    , m_project( new GluonEngine::GameProject )
{
    setCentralWidget( m_gamesOverlay );
    setupActions();
    setupGUI();
    showGames();

    stateChanged( "initial" );
}

MainWindow::~MainWindow( )
{
}

void MainWindow::setupActions()
{
    KStandardAction::quit( this, SLOT(close()), actionCollection() );
    KStandardAction::showMenubar( menuBar(), SLOT(setVisible(bool)), actionCollection() );
    KStandardAction::showStatusbar( statusBar(), SLOT(setVisible(bool)), actionCollection() );
    setStandardToolBarMenuEnabled( true );
    createStandardStatusBarAction();

    KStandardAction::keyBindings( this, SLOT(optionsConfigureKeys()), actionCollection() ); // options_configure_keybinding
    KStandardAction::configureToolbars( this, SLOT(optionsConfigureToolbars()), actionCollection() ); // options_configure_toolbars

    m_recentFiles = KStandardAction::openRecent( this, SLOT(openProject(KUrl)), actionCollection() );
    // d->recentFiles->loadEntries( KGlobal::config()->group( "Recent Files" ) );

    KAction* login = new KAction( KIcon( "im-user" ), i18n( "Login" ), actionCollection() );
    actionCollection()->addAction( "community_login", login );
    connect( login, SIGNAL(triggered(bool)), SLOT(mLogin()) );

    KAction* logout = new KAction( KIcon( "media-playback-start" ), i18n( "Logout" ), actionCollection() );
    actionCollection()->addAction( "community_logout", logout );
    connect( logout, SIGNAL(triggered(bool)), SLOT(mLogout()) );

    KAction* details = new KAction( KIcon( "media-playback-start" ), i18n( "Details" ), actionCollection() );
    actionCollection()->addAction( "community_details", details );
    connect( details, SIGNAL(triggered(bool)), SLOT(mDetails()) );

    KAction* registration = new KAction( KIcon( "list-add-user" ), i18n( "Registration" ), actionCollection() );
    actionCollection()->addAction( "community_registration", registration );
    connect( registration, SIGNAL(triggered(bool)), SLOT(mRegistration()) );

    KAction* forgottenPassword = new KAction( KIcon( "help-hint" ), i18n( "Forgotten password" ), actionCollection() );
    actionCollection()->addAction( "community_forgotten_password", forgottenPassword );
    connect( forgottenPassword, SIGNAL(triggered(bool)), SLOT(mForgottenPassword()) );

    KAction* play = new KAction( KIcon( "media-playback-start" ), i18n( "Play Game" ), actionCollection() );
    actionCollection()->addAction( "game_play", play );
    connect( play, SIGNAL(triggered(bool)), SLOT(openProject()) );

    KAction* savegame = new KAction( KIcon( "document-save" ), i18n( "Save Game" ), actionCollection() );
    actionCollection()->addAction( "game_savegame", savegame );
    connect( savegame, SIGNAL(triggered(bool)), SLOT(saveGame()) );

    KAction* pause = new KAction( KIcon( "media-playback-pause" ), i18n( "Pause Game" ), actionCollection() );
    actionCollection()->addAction( "game_pause", pause );
    connect( pause, SIGNAL(triggered(bool)), SLOT(pauseGame()) );

    KAction* stop = new KAction( KIcon( "media-playback-stop" ), i18n( "Stop Game" ), actionCollection() );
    actionCollection()->addAction( "game_stop", stop );
    connect( stop, SIGNAL(triggered(bool)), SLOT(stopGame()) );

    KStandardAction::quit( kapp, SLOT(quit()), actionCollection() );
}

void MainWindow::startGame( )
{
    stateChanged( "playing" );

    GluonCore::GluonObjectFactory::instance()->loadPlugins();

    m_project->loadFromFile( m_projectFilePath );

    setWindowFilePath( m_projectFilePath );
    d->title = windowTitle();

    GluonEngine::Game::instance()->setGameProject( m_project );
    GluonEngine::Game::instance()->setCurrentScene( m_project->entryPoint() );

    d->widget->setFocus();

    // if( GluonEngine::Game::instance()->isRunning() )
    // {
    // GluonEngine::Game::instance()->setPause( false );
    // stateChanged( "paused", StateReverse );
    // }
    // else
    // {
    // stateChanged( "playing" );

    // QString currentSceneName = GluonEngine::Game::instance()->currentScene()->fullyQualifiedName();
    // saveProject();

    //Set the focus to the entire window, so that we do not accidentally trigger actions
    // setFocus();

    //Start the game loop
    //Note that this starts an infinite loop in Game
    GluonEngine::Game::instance()->runGame();

    //This happens after we exit the game loop
    stateChanged( "playing", StateReverse );
    QApplication::instance()->exit();
    //This happens after we exit the game loop
    // stateChanged( "playing", StateReverse );

    // openProject( d->fileName );
    // GluonEngine::Game::instance()->setCurrentScene( currentSceneName );
    // GluonEngine::Game::instance()->initializeAll();
    // }
}

void MainWindow::pauseGame()
{
    GluonEngine::Game::instance()->setPause( true );
    stateChanged( "paused" );
}

void MainWindow::saveGame()
{
    GluonEngine::GameSave *s = new GluonEngine::GameSave();
    s->save();
}

void MainWindow::stopGame()
{
    GluonEngine::Game::instance()->stopGame();
}

// void MainWindow::saveProperties(KConfigGroup &config)
// {
// if (!m_part)
// loadPart();

// m_part->saveProperties(config);
// config.writeEntry("docked", isHidden());
// }

// void MainWindow::readProperties(const KConfigGroup & config)
// {
// if (!m_part)
// loadPart();
// m_part->readProperties(config);
// setVisible( !Settings::showTrayIcon() || !config.readEntry("docked", false) );
// }

// TODO: move to part?
void MainWindow::optionsConfigureKeys()
{
    KShortcutsDialog dlg( KShortcutsEditor::AllActions,
                          KShortcutsEditor::LetterShortcutsAllowed, this );

    dlg.addCollection( actionCollection() );
    // if (m_part)
    // dlg.addCollection(m_part->actionCollection());

    dlg.configure();
}

// TODO: move to part?
void MainWindow::optionsConfigureToolbars()
{
    // saveMainWindowSettings(KGlobal::config().data()->group( autoSaveGroup()) );
    // KEditToolBar dlg(factory());
    // connect(&dlg, SIGNAL(newToolBarConfig()),
    // this, SLOT(applyNewToolbarConfig()));
    // dlg.exec();
}

void MainWindow::mLogin( )
{
}

void MainWindow::mLogout( )
{
}

void MainWindow::mHome()
{
}

void MainWindow::mDetails()
{
}

void MainWindow::mRegistration()
{
}

void MainWindow::mForgottenPassword()
{
}

void MainWindow::closeEvent( QCloseEvent* event )
{
    GluonEngine::Game::instance()->stopGame();
    QWidget::closeEvent( event );
}

void MainWindow::showGames()
{
    m_gamesOverlay->setGeometry( geometry() );
    connect( m_gamesOverlay, SIGNAL(gameToPlaySelected(QModelIndex)), SLOT(setProject(QModelIndex)) );
}

void MainWindow::setProject( const QModelIndex& index )
{
    m_projectFilePath = index.data( GluonPlayer::GameItemsModel::ProjectFilePathRole ).toString();
    m_gamesOverlay->hide();
    openProject();
}

void MainWindow::openProject()
{
    if( GluonEngine::Game::instance()->isRunning() )
    {
        GluonEngine::Game::instance()->setPause( false );
        stateChanged( "paused", StateReverse );
        return;
    }

    if( m_projectFilePath.isEmpty() )
    {
        return;
    }

    d->widget = new GluonGraphics::RenderWidget( this );
    setCentralWidget( d->widget );

    connect( GluonEngine::Game::instance(), SIGNAL(painted(int)), d->widget, SLOT(updateGL()) );
    connect( GluonEngine::Game::instance(), SIGNAL(painted(int)), SLOT(countFrames(int)) );
    connect( GluonEngine::Game::instance(), SIGNAL(updated(int)), SLOT(updateTitle(int)) );

    GluonInput::InputManager::instance()->setFilteredObject( d->widget );
    QTimer::singleShot( 1000, this, SLOT(startGame()) );
}

void MainWindow::activated( QModelIndex index )
{
    if( index.isValid() )
    {
    }
}

void MainWindow::updateTitle( int msec )
{
    d->msecElapsed += msec;

    static int fps = 0;
    if( d->msecElapsed > 1000 )
    {
        fps = d->frameCount;
        d->frameCount = 0;
        d->msecElapsed = 0;
    }

    setWindowTitle( d->title + QString( " (%1 FPS)" ).arg( fps ) );
}

void MainWindow::countFrames( int /* time */ )
{
    d->frameCount++;
}

