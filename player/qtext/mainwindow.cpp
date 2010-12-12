/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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
#include "actionsdialog.h"

#include <core/debughelper.h>
#include <engine/game.h>
#include <engine/gameproject.h>
#include <engine/scene.h>
#include <graphics/renderwidget.h>
#include <player/models/gamesmodel.h>

#include <QtGui/QFileDialog>
#include <QtGui/QStatusBar>
#include <QtGui/QApplication>
#include <QtGui/QListView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QPushButton>
#include <QLabel>
#include <QTimer>

using namespace GluonPlayer;

class MainWindow::MainWindowPrivate
{
    public:
        GluonEngine::GameProject* project;
        GluonGraphics::RenderWidget* widget;

        QAbstractItemModel* model;

        QString title;
        QString fileName;

        int msecElapsed;
        int frameCount;
};

GluonPlayer::MainWindow::MainWindow( int argc, char** argv, QWidget* parent, Qt::WindowFlags flags )
    : QMainWindow( parent, flags )
    , d( new MainWindowPrivate )
    , settings( new QSettings )
{
    d->msecElapsed = 0;
    d->frameCount = 0;

    if( argc > 1 )
    {
        d->fileName = argv[1];
        QTimer::singleShot( 0, this, SLOT( openProject() ) );
    }
    else
    {
        // QWidget* base = new QWidget( this );
        // QVBoxLayout* layout = new QVBoxLayout();
        // base->setLayout( layout );
        /* setCentralWidget( base ); */

        // QLabel* header = new QLabel( tr( "Please select a Project" ), base );
        // header->setAlignment( Qt::AlignCenter );
        // QFont font;
        // font.setBold( true );
        // header->setFont( font );
        // layout->addWidget( header );

        // QListView* view = new QListView( base );
        // layout->addWidget( view );
        // d->model = new GamesModel( view );
        // view->setModel( d->model );
        // connect( view, SIGNAL( activated( QModelIndex ) ), SLOT( activated( QModelIndex ) ) );

        // QPushButton* button = new QPushButton( tr( "Open other project..." ), base );
        // layout->addWidget( button );
        // connect( button, SIGNAL( clicked( bool ) ), SLOT( openClicked( bool ) ) );
    }

    setupUi();

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    loadActions();

    resize( 500, 500 );
}

void MainWindow::changeEvent( QEvent* event )
{
    QMainWindow::changeEvent( event );
    switch( event->type() )
    {
        case QEvent::LanguageChange:
            retranslateUi();
            break;
        default:
            break;
    }
}

void MainWindow::setupUi()
{
    if( objectName().isEmpty() )
        setObjectName( QString::fromUtf8( "MainWindow" ) );

    centralWidget = new QWidget( this );
    centralWidget->setObjectName( QString::fromUtf8( "centralWidget" ) );


    menuBar = new QMenuBar( this );
    menuBar->setObjectName( QString::fromUtf8( "menuBar" ) );
    menuBar->setGeometry( QRect( 0, 0, 1290, 20 ) );
    setMenuBar( menuBar );
    mainToolBar = new QToolBar( this );
    mainToolBar->setObjectName( QString::fromUtf8( "mainToolBar" ) );
    addToolBar( Qt::TopToolBarArea, mainToolBar );
    statusBar = new QStatusBar( this );
    statusBar->setObjectName( QString::fromUtf8( "statusBar" ) );
    setStatusBar( statusBar );

    setWindowTitle( "QPatternDB" );
    setWindowIcon( QIcon( ":/images/icon.bmp" ) );
    setWindowIconText( "QPatternDB application logo" );

    loginForm = new LoginForm;

    // stackedWidget = new QStackedWidget;

    // stackedWidget->addWidget(loginForm);

    // mainGridLayout = new QGridLayout(centralWidget);
    // mainGridLayout->setObjectName(QString::fromUtf8("mainGridLayout"));

    // mainGridLayout->addWidget(stackedWidget, 0, 0);
    // setLayout(mainGridLayout);

    setCentralWidget( loginForm );
    // setCentralWidget(centralWidget);
    // retranslateUi();

    return;
}

void MainWindow::retranslateUi()
{
    setWindowTitle( QApplication::translate( "MainWindow", "MainWindow", 0,
                    QApplication::UnicodeUTF8 ) );
    return;
}

void MainWindow::activated( QModelIndex index )
{
    if( index.isValid() )
    {
        openProject( d->model->data( index ).toString() );
    }
}

void MainWindow::openClicked( bool toggled )
{
    Q_UNUSED( toggled )

    QString fileName = QFileDialog::getOpenFileName( this, tr( "Select a Project" ), QString(), QString( "*.gluon|Gluon Project Files" ) );
    if( !fileName.isEmpty() )
        openProject( fileName );
}

void MainWindow::openProject( const QString& fileName )
{
    QString file = fileName;
    if( file.isEmpty() )
        file = d->fileName;

    d->widget = new GluonGraphics::RenderWidget( this );
    setCentralWidget( d->widget );
    connect( GluonEngine::Game::instance(), SIGNAL( painted( int ) ), d->widget, SLOT( updateGL() ) );
    connect( GluonEngine::Game::instance(), SIGNAL( painted( int ) ), SLOT( countFrames( int ) ) );
    connect( GluonEngine::Game::instance(), SIGNAL( updated( int ) ), SLOT( updateTitle( int ) ) );

    QTimer::singleShot( 100, this, SLOT( startGame() ) );

    d->fileName = file;
}

void MainWindow::startGame()
{
    GluonCore::GluonObjectFactory::instance()->loadPlugins();

    d->project = new GluonEngine::GameProject();
    d->project->loadFromFile( QUrl( d->fileName ) );

    setWindowFilePath( d->fileName );
    d->title = windowTitle();

    GluonEngine::Game::instance()->setGameProject( d->project );
    GluonEngine::Game::instance()->setCurrentScene( d->project->entryPoint() );

    GluonEngine::Game::instance()->runGame();
}

void MainWindow::closeEvent( QCloseEvent* event )
{
    GluonEngine::Game::instance()->stopGame();
    QWidget::closeEvent( event );
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

void MainWindow::countFrames( int time )
{
    Q_UNUSED( time )
    d->frameCount++;
}

void MainWindow::createActions()
{
    // File related actions
    openGameAct = new QAction( QIcon( ":/images/open.png" ), tr( "&Open a game..." ), this );
    openGameAct->setShortcuts( QKeySequence::Open );
    openGameAct->setStatusTip( tr( "Open a game" ) );
    openGameAct->setEnabled( false );
    connect( openGameAct, SIGNAL( triggered() ), SLOT( mOpenGame() ) );

    quitAct = new QAction( QIcon( ":/images/quit.png" ), tr( "&Quit" ), this );
    quitAct->setShortcut( QKeySequence( Qt::CTRL + Qt::Key_Q ) );
    quitAct->setStatusTip( tr( "Exit the application" ) );
    connect( quitAct, SIGNAL( triggered() ), SLOT( close() ) );


    // View menu related actions
    showToolBarAct = new QAction( tr( "Show &ToolBar" ), this );
    showToolBarAct->setStatusTip( tr( "Toggle the view state of the ToolBar" ) );
    showToolBarAct->setCheckable( true );
    showToolBarAct->setChecked( true );
    connect( showToolBarAct, SIGNAL( triggered( bool ) ), SLOT( mShowToolBar( bool ) ) );

    showStatusBarAct = new QAction( tr( "Show St&atusBar" ), this );
    showStatusBarAct->setStatusTip( tr( "Toggle the view state of the StatusBar" ) );
    showStatusBarAct->setCheckable( true );
    showStatusBarAct->setChecked( true );
    connect( showStatusBarAct, SIGNAL( triggered( bool ) ), SLOT( mShowStatusBar( bool ) ) );


    // Community menu related actions
    loginLogoutAct = new QAction( tr( "Login/Logout" ), this );
    loginLogoutAct->setStatusTip( tr( "Login/Logout" ) );
    loginLogoutAct->setCheckable( true );
    loginLogoutAct->setChecked( true );
    connect( loginLogoutAct, SIGNAL( triggered( bool ) ), SLOT( mLoginLogout( bool ) ) );

    homeAct = new QAction( tr( "Home view" ), this );
    homeAct->setStatusTip( tr( "Go to the Home view" ) );
    connect( homeAct, SIGNAL( triggered() ), SLOT( mHome() ) );

    detailsAct = new QAction( tr( "Details view" ), this );
    detailsAct->setStatusTip( tr( "Go to the Detail view" ) );
    connect( detailsAct, SIGNAL( triggered() ), SLOT( mDetails() ) );

    registrationAct = new QAction( tr( "Registration view" ), this );
    registrationAct->setStatusTip( tr( "Go to the Registration view" ) );
    connect( registrationAct, SIGNAL( triggered() ), SLOT( mRegistration() ) );

    forgottenPasswordAct = new QAction( tr( "Forgotten Password Action" ), this );
    forgottenPasswordAct->setStatusTip( tr( "Go to the Forgotten Password Page" ) );
    connect( forgottenPasswordAct, SIGNAL( triggered() ), SLOT( mForgottenPassword() ) );


    // Settings menu related actions
    configureToolBarAct = new QAction( tr( "Configure Tool&bar..." ), this );
    configureToolBarAct->setStatusTip( tr( "Configure the toolbar of the application" ) );
    connect( configureToolBarAct, SIGNAL( triggered() ), SLOT( mConfigureToolBar() ) );

    configureShortcutsAct = new QAction( tr( "Configure S&hortcuts..." ), this );
    configureShortcutsAct->setStatusTip( tr( "Configure the shortcuts of the actions" ) );
    connect( configureShortcutsAct, SIGNAL( triggered() ), SLOT( mConfigureShortcuts() ) );


    // Help menu related actions
    aboutAct = new QAction( tr( "&About" ), this );
    aboutAct->setStatusTip( tr( "Show the extended Qt Player About box" ) );
    connect( aboutAct, SIGNAL( triggered() ), SLOT( mAbout() ) );

    aboutQtAct = new QAction( tr( "About &Qt" ), this );
    aboutQtAct->setStatusTip( tr( "Show the Qt library's About box" ) );
    connect( aboutQtAct, SIGNAL( triggered() ), qApp, SLOT( aboutQt() ) );
}

void MainWindow::createMenus()
{
    // File related menu
    fileMenu = menuBar->addMenu( tr( "&File" ) );
    fileMenu->addAction( openGameAct );
    fileMenu->addSeparator();
    fileMenu->addAction( quitAct );

    // View related menu
    viewMenu = menuBar->addMenu( tr( "&View" ) );
    viewMenu->addAction( showToolBarAct );
    viewMenu->addAction( showStatusBarAct );

    // Community related menu
    communityMenu = menuBar->addMenu( tr( "&Community" ) );
    communityMenu->addAction( loginLogoutAct );
    communityMenu->addAction( homeAct );
    communityMenu->addAction( detailsAct );
    communityMenu->addAction( registrationAct );
    communityMenu->addAction( forgottenPasswordAct );

    // Settings related menu
    settingsMenu = menuBar->addMenu( tr( "&Settings" ) );
    settingsMenu->addAction( configureShortcutsAct );
    settingsMenu->addAction( configureToolBarAct );

    // Help related menu
    helpMenu = menuBar->addMenu( tr( "&Help" ) );
    helpMenu->addAction( aboutAct );
    helpMenu->addAction( aboutQtAct );
}

void MainWindow::createToolBars()
{
    // File related toolbar
    mainToolBar->addAction( openGameAct );

    // Settings related toolbar
    mainToolBar->addAction( loginLogoutAct );
    mainToolBar->addAction( homeAct );
    mainToolBar->addAction( detailsAct );
    mainToolBar->addAction( registrationAct );
    mainToolBar->addAction( forgottenPasswordAct );

}

void MainWindow::createStatusBar()
{
    statusBar->showMessage( tr( "Ready" ) );
}

void MainWindow::mOpenGame()
{
}

void MainWindow::mShowToolBar( bool checked )
{
    mainToolBar->setVisible( checked );
}

void MainWindow::mShowStatusBar( bool checked )
{
    statusBar->setVisible( checked );
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

void MainWindow::mConfigureToolBar()
{
}

void MainWindow::mConfigureShortcuts()
{
    ActionsDialog actionsDialog( m_actions, this );
    actionsDialog.exec();
}

void MainWindow::mAbout()
{
    QMessageBox::about( this, tr( "<b>Gluon Extended Qt Player</b>" ), \
                        tr( "This is an extended Qt Player application for Gluon games." ) );
}

void MainWindow::loadActions()
{

    qint32 cntr = 0;
    QList<QAction*> actions;
    actions = findChildren<QAction*>();
    foreach( QAction * action, actions )
    {
        if( !action->isSeparator() && !action->text().isEmpty() )
        {
            m_actions.append( action );
        }
        else
        {
            ++cntr;
        }
    }

    cntr = 0;

    settings->beginGroup( "Action" );
    foreach( QAction * action, m_actions )
    {
        QString accelText = settings->value( action->text() ).toString();
        if( !accelText.isEmpty() )
            m_actions[cntr]->setShortcut( QKeySequence( accelText ) );
        ++cntr;
    }
    settings->endGroup();
}


#include "mainwindow.moc"
