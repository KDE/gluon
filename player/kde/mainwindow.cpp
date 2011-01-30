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

#include "input/inputmanager.h"

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

#include <QtGui/QStatusBar>
#include <QtGui/QListView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>
#include <QtCore/QTimer>

using namespace GluonPlayer;

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
    : KMainWindow()
    , d( new MainWindowPrivate )
{
    d->msecElapsed = 0;
    d->frameCount = 0;

    if( !filename.isEmpty() )
    {
        d->fileName = filename;
        QTimer::singleShot( 0, this, SLOT( openProject() ) );
    }
    else
    {
        QWidget* base = new QWidget( this );
        QVBoxLayout* layout = new QVBoxLayout();
        base->setLayout( layout );
        setCentralWidget( base );

        QLabel* header = new QLabel( i18n( "Please select a Project" ), base );
        header->setAlignment( Qt::AlignCenter );
        QFont font;
        font.setBold( true );
        header->setFont( font );
        layout->addWidget( header );

        QListView* view = new QListView( base );
        layout->addWidget( view );
        d->model = new GamesModel( view );
        view->setModel( d->model );
        connect( view, SIGNAL( activated( QModelIndex ) ), SLOT( activated( QModelIndex ) ) );

        KPushButton* button = new KPushButton( i18n( "Open other project..." ), base );
        layout->addWidget( button );
        connect( button, SIGNAL( clicked( bool ) ), SLOT( openClicked( bool ) ) );
    }
    resize( 500, 500 );
}

MainWindow::~MainWindow ( )
{
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

    QString fileName = KFileDialog::getOpenFileName( KUrl() , i18n( "Select a Project" ), this, QString( "*.gluon|Gluon Project Files" ) );
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
