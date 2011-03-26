/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2010 Laszlo Papp <djszapi@archlinux.us>
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

#include <input/inputmanager.h>

#include <engine/game.h>
#include <engine/gameproject.h>
#include <engine/scene.h>
#include <graphics/renderwidget.h>
#include <core/gluon_global.h>

#include <QtGui/QFileDialog>
#include <QtGui/QStatusBar>
#include <QtGui/QApplication>
#include <QtGui/QVBoxLayout>
#include <QtGui/QPushButton>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtCore/QTimer>

using namespace GluonPlayer;

class MainWindow::MainWindowPrivate
{
    public:
        GluonEngine::GameProject* project;
        GluonGraphics::RenderWidget* widget;
        QListWidget *listWidget;

        QString title;
        QString fileName;

        int msecElapsed;
        int frameCount;
};

GluonPlayer::MainWindow::MainWindow( int argc, char** argv, QWidget* parent, Qt::WindowFlags flags )
    : QMainWindow( parent, flags )
    , d( new MainWindowPrivate )
{
    d->msecElapsed = 0;
    d->frameCount = 0;

    if( argc > 1 )
    {
        QFileInfo fi = QFileInfo( argv[1] );
        if( fi.isRelative() )
            d->fileName = fi.canonicalFilePath();
        else
            d->fileName = argv[1];
        QTimer::singleShot( 0, this, SLOT( openProject() ) );
    }
    else
    {
        QWidget* base = new QWidget( this );
        QVBoxLayout* layout = new QVBoxLayout();
        base->setLayout( layout );
        setCentralWidget( base );

        QLabel* header = new QLabel( tr( "Please select a Project" ), base );
        header->setAlignment( Qt::AlignCenter );
        QFont font;
        font.setBold( true );
        header->setFont( font );
        layout->addWidget( header );

        d->listWidget = new QListWidget( base );
        layout->addWidget( d->listWidget );
        connect( d->listWidget, SIGNAL( activated( QModelIndex ) ), SLOT( activated( QModelIndex ) ) );

        QPushButton* button = new QPushButton( tr( "Open other project..." ), base );
        layout->addWidget( button );
        connect( button, SIGNAL( clicked( bool ) ), SLOT( openClicked( bool ) ) );
    }
    resize( 500, 500 );
    loadGamesList();
}

MainWindow::~MainWindow()
{
    delete d;
}

void MainWindow::activated( QModelIndex index )
{
    if( index.isValid() )
    {
        openProject( d->listWidget->currentItem()->text() );
    }
}

void MainWindow::openClicked( bool toggled )
{
    Q_UNUSED( toggled )

    QString fileName = QFileDialog::getOpenFileName( this, tr( "Select a Project" ), QString(), QString( "*%1|Gluon Project Files" ).arg( GluonEngine::projectFilename ) );
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

    GluonInput::InputManager::instance()->setFilteredObject(d->widget);
    QTimer::singleShot( 100, this, SLOT( startGame() ) );

    d->fileName = file;
}

void MainWindow::startGame()
{
    GluonCore::GluonObjectFactory::instance()->loadPlugins();

    d->project = new GluonEngine::GameProject();
    d->project->loadFromFile( d->fileName );

    setWindowFilePath( d->fileName );
    d->title = windowTitle();

    GluonEngine::Game::instance()->setGameProject( d->project );
    GluonEngine::Game::instance()->setCurrentScene( d->project->entryPoint() );

    d->widget->setFocus();
    GluonEngine::Game::instance()->runGame();

    QApplication::instance()->exit();
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

void MainWindow::loadGamesList()
{
    QDir m_dir;
    m_dir.cd( GluonCore::Global::dataDirectory() + "/gluon/games" );
    QStringList gameDirNameList = m_dir.entryList( QStringList() << QString("*" + GluonEngine::projectSuffix), QDir::Dirs | QDir::NoDotAndDotDot );
    foreach( const QString& gameDirName, gameDirNameList)
    {
        QDir gameDir = m_dir;
        gameDir.cd( gameDirName );
        QStringList gluonProjectFiles = gameDir.entryList( QStringList( GluonEngine::projectFilename ) );
        if( !gluonProjectFiles.isEmpty() )
        {
            QString projectFileName = gameDir.absoluteFilePath( gluonProjectFiles.at( 0 ) );
            GluonEngine::GameProject project;
            project.loadFromFile( projectFileName );
            d->listWidget->addItem(projectFileName);
        }
    }
}

#include "mainwindow.moc"
