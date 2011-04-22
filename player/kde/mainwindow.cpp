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

#include <input/inputmanager.h>

#include <engine/game.h>
#include <engine/gameproject.h>
#include <engine/scene.h>
#include <graphics/renderwidget.h>
#include <core/gluon_global.h>

#include <KDE/KPushButton>
#include <KDE/KFileDialog>
#include <KDE/KUrl>
#include <KDE/KLocalizedString>

#include <QtGui/QStatusBar>
#include <QtGui/QListWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QApplication>
#include <QtCore/QTimer>

using namespace GluonPlayer;

class MainWindow::MainWindowPrivate
{
    public:
        MainWindowPrivate() {}

        GluonEngine::GameProject* project;
        GluonGraphics::RenderWidget* widget;

        KRecentFilesAction* recentFiles;

        QListWidget* listWidget;

        QString title;
        QString fileName;

        int msecElapsed;
        int frameCount;
};

MainWindow::MainWindow( const QString& filename )
    : KMainWindow()
    , d( new MainWindowPrivate )
{
    d->msecElapsed = 0;
    d->frameCount = 0;

    if( !filename.isEmpty() )
    {
        QFileInfo fi = QFileInfo( filename );
        if( fi.isRelative() )
            d->fileName = fi.canonicalFilePath();
        else
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

        d->listWidget = new QListWidget( base );
        layout->addWidget( d->listWidget );
        connect( d->listWidget, SIGNAL( activated( QModelIndex ) ), SLOT( activated( QModelIndex ) ) );

        KPushButton* button = new KPushButton( i18n( "Open other project..." ), base );
        layout->addWidget( button );
        connect( button, SIGNAL( clicked( bool ) ), SLOT( openClicked( bool ) ) );
        loadGamesList();
    }
    resize( 500, 500 );
}

MainWindow::~MainWindow( )
{
}

void MainWindow::activated( QModelIndex index )
{
    if( index.isValid() )
    {
        openProject( d->listWidget->currentItem()->text() );
    }
}

void MainWindow::openClicked( bool /* toggled */ )
{
    QString fileName = KFileDialog::getOpenFileName( KUrl() , i18n( "Select a Project" ), this, QString( "*%1|Gluon Project Files" ).arg( GluonEngine::projectFilename ) );
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

    GluonInput::InputManager::instance()->setFilteredObject( d->widget );
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

void MainWindow::countFrames( int /* time */ )
{
    d->frameCount++;
}

void MainWindow::loadGamesList()
{
    QDir m_dir;
    m_dir.cd( GluonCore::Global::dataDirectory() + "/gluon/games" );
    QStringList gameDirNameList = m_dir.entryList( QStringList() << QString( '*' + GluonEngine::projectSuffix ), QDir::Dirs | QDir::NoDotAndDotDot );
    foreach( const QString & gameDirName, gameDirNameList )
    {
        QDir gameDir = m_dir;
        gameDir.cd( gameDirName );
        QStringList gluonProjectFiles = gameDir.entryList( QStringList( GluonEngine::projectFilename ) );
        if( !gluonProjectFiles.isEmpty() )
        {
            QString projectFileName = gameDir.absoluteFilePath( gluonProjectFiles.at( 0 ) );
            GluonEngine::GameProject project;
            project.loadFromFile( projectFileName );
            d->listWidget->addItem( projectFileName );
        }
    }
}

