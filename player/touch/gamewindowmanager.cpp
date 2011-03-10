/*****************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Laszlo Papp <djszapi@archlinux.us>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *****************************************************************************/

#include "gamewindowmanager.h"

#include "input/inputmanager.h"

#include "engine/scene.h"

#include <QtCore/QTimer>
#include <QtCore/QDebug>
#include <QtGui/QApplication>

using namespace GluonQMLPlayer;

class GameWindowManager::GameWindowManagerPrivate
{
    public:
        GameWindowManagerPrivate() {}

        GluonGraphics::RenderWidget* widget;

        QString title;
        QString fileName;

        int msecElapsed;
        int frameCount;
};

GameWindowManager::GameWindowManager(const QString& /* filename */)
    : QObject()
    , d( new GameWindowManagerPrivate )
    , m_project( new GluonEngine::GameProject )
{
}

GameWindowManager::GameWindowManager(GluonGraphics::RenderWidget* renderWidget, QGraphicsView* view,
                                    GluonPlayer::GameItemsModel* gameItemsModel, const QString& /* filename */ )
    : QObject()
    , d( new GameWindowManagerPrivate )
    , m_project( new GluonEngine::GameProject )
    , m_view(view)
    , m_gameItemsModel(gameItemsModel)
{
    d->widget = renderWidget;
}

GameWindowManager::~GameWindowManager ( )
{
}

bool GameWindowManager::isViewportGLWidget( )
{
    return qobject_cast<QGLWidget*>(m_view);
}

void GameWindowManager::startGame( )
{
    GluonCore::GluonObjectFactory::instance()->loadPlugins();

    m_project->loadFromFile( m_gameFileName );

    GluonEngine::Game::instance()->setGameProject( m_project );
    GluonEngine::Game::instance()->setCurrentScene( m_project->entryPoint() );

    GluonEngine::Game::instance()->runGame();
    QApplication::instance()->exit();
}

void GameWindowManager::pauseGame()
{
    GluonEngine::Game::instance()->setPause( true );
    // stateChanged( "paused" );
}

void GameWindowManager::stopGame()
{
    GluonEngine::Game::instance()->stopGame();
}

void GameWindowManager::setProject( int index )
{
    m_gameFileName = m_gameItemsModel->index(index).data(GluonPlayer::GameItemsModel::ProjectFileNameRole).toString();
    openProject();
}

int GameWindowManager::availableGamesCount( ) const
{
    return m_gameItemsModel->rowCount();
}

void GameWindowManager::buildCommentsModel( int index )
{
    QString gameID = m_gameItemsModel->index(index).data(GluonPlayer::GameItemsModel::IDRole).toString();
    if( gameID.isEmpty() )
    {
        return;
    }

    m_commentsModel = new GluonPlayer::CommentItemsModel( gameID );
}

void GameWindowManager::setProject( const QModelIndex& index )
{
    m_gameFileName = index.data(GluonPlayer::GameItemsModel::ProjectFileNameRole).toString();
    openProject();
}

void GameWindowManager::openProject()
{
    if( m_gameFileName.isEmpty() )
    {
        return;
    }

    connect( GluonEngine::Game::instance(), SIGNAL( painted( int ) ), d->widget, SLOT( updateGL() ) );
    connect( GluonEngine::Game::instance(), SIGNAL( painted( int ) ), SLOT( countFrames( int ) ) );
    connect( GluonEngine::Game::instance(), SIGNAL( updated( int ) ), SLOT( updateTitle( int ) ) );

    GluonInput::InputManager::instance()->setFilteredObject(d->widget);
    QTimer::singleShot( 1000, this, SLOT( startGame() ) );
}

void GameWindowManager::activated( QModelIndex index )
{
    if( index.isValid() )
    {
    }
}

void GameWindowManager::updateTitle( int msec )
{
    d->msecElapsed += msec;

    static int fps = 0;
    if( d->msecElapsed > 1000 )
    {
        fps = d->frameCount;
        d->frameCount = 0;
        d->msecElapsed = 0;
    }
}

void GameWindowManager::countFrames( int /* time */ )
{
    d->frameCount++;
}

GluonPlayer::GameItemsModel* GameWindowManager::gameItemsModel() const
{
    return m_gameItemsModel;
}

void GameWindowManager::setGameItemsModel(GluonPlayer::GameItemsModel* gameItemsModel)
{
    m_gameItemsModel = gameItemsModel;
}

#include "gamewindowmanager.moc"
