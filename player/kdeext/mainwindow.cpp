/*****************************************************************************
 * This file is part of the Gluon Development Platform                       *
 * Copyright (c) 2011 Laszlo Papp <djszapi@archlinux.us>                     *
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

#include <core/debughelper.h>
#include <engine/game.h>
#include <engine/gameproject.h>
#include <engine/scene.h>
#include <graphics/renderwidget.h>
#include <player/models/gamesmodel.h>

#include <KPushButton>
#include <KFileDialog>
#include <KUrl>
#include <KLocalizedString>
#include <KMenuBar>
#include <KDE/KToolBar>
#include <KStatusBar>
#include <KAction>
#include <KActionCollection>
#include <KStandardAction>
#include <KConfig>
#include <KShortcutsDialog>
#include <KEditToolBar>

#include <QtGui/QStatusBar>
#include <QtGui/QListView>
#include <QtGui/QVBoxLayout>
#include <QLabel>
#include <QTimer>

using namespace GluonKDEExtPlayer;

class MainWindow::MainWindowPrivate
{
    public:
        MainWindowPrivate() {}

        GluonEngine::GameProject* project;
        GluonGraphics::RenderWidget* widget;

        KRecentFilesAction* recentFiles;

        QAbstractItemModel* model;

        QString title;
        QString fileName;

        int msecElapsed;
        int frameCount;
};

MainWindow::MainWindow(const QString& filename )
    : KXmlGuiWindow()
    , d( new MainWindowPrivate )
{
    textArea = new KTextEdit;
    setCentralWidget(textArea);
    setupActions();
}

MainWindow::~MainWindow ( )
{
}


void MainWindow::setupActions()
{
    KStandardAction::quit( this, SLOT( close() ), actionCollection() );
    KStandardAction::showMenubar( menuBar(), SLOT(setVisible(bool)), actionCollection());
    KStandardAction::showStatusbar( statusBar(), SLOT(setVisible(bool)), actionCollection());
    setStandardToolBarMenuEnabled(true);
    createStandardStatusBarAction();

    KStandardAction::keyBindings(this, SLOT(optionsConfigureKeys()), actionCollection()); // options_configure_keybinding
    KStandardAction::configureToolbars(this, SLOT(optionsConfigureToolbars()), actionCollection()); // options_configure_toolbars

    // d->recentFiles = KStandardAction::openRecent( this, SLOT( openProject( KUrl ) ), actionCollection() );
    // d->recentFiles->loadEntries( KGlobal::config()->group( "Recent Files" ) );

    KAction* play = new KAction( KIcon( "media-playback-start" ), i18n( "Play Game" ), actionCollection() );
    actionCollection()->addAction( "playGame", play );
    connect( play, SIGNAL( triggered( bool ) ), SLOT( playGame() ) );

    KAction* pause = new KAction( KIcon( "media-playback-pause" ), i18n( "Pause Game" ), actionCollection() );
    actionCollection()->addAction( "pauseGame", pause );
    connect( pause, SIGNAL( triggered( bool ) ), SLOT( pauseGame() ) );

    KAction* stop = new KAction( KIcon( "media-playback-stop" ), i18n( "Stop Game" ), actionCollection() );
    actionCollection()->addAction( "stopGame", stop );
    connect( stop, SIGNAL( triggered( bool ) ), SLOT( stopGame() ) );

    KStandardAction::quit(kapp, SLOT(quit()), actionCollection());
}

void MainWindow::playGame( )
{
    // if( GluonEngine::Game::instance()->isRunning() )
    // {
        // GluonEngine::Game::instance()->setPause( false );
        // stateChanged( "paused", StateReverse );
    // }
    // else
    // {
        // stateChanged( "playing" );

        // d->mainArea->setActiveTab( 0 );

        // QString currentSceneName = GluonEngine::Game::instance()->currentScene()->fullyQualifiedName();
        // saveProject();

        // //Set the focus to the entire window, so that we do not accidentally trigger actions
        // setFocus();

        // //Start the game loop
        // //Note that this starts an infinite loop in Game
        // GluonEngine::Game::instance()->runGame();

        // //This happens after we exit the game loop
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

    dlg.addCollection(actionCollection());
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

void MainWindow::mLoginLogout( bool checked )
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

