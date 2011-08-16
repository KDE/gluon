/*****************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Laszlo Papp <lpapp@kde.org>
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

#include "lib/models/achievementsmodel.h"
#include "lib/models/gameviewitem.h"
#include "lib/models/gameitemsmodel.h"
#include "lib/models/commentitemsmodel.h"
#include "lib/authentication.h"

#include <input/inputmanager.h>
#include <engine/scene.h>
#include <graphics/renderwidget.h>

#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative>
#include <QtGui/QGraphicsObject>
#include <QtGui/QApplication>
#include <QtGui/QStackedWidget>
#include <QtCore/QTimer>
#include <QtCore/QDebug>

using namespace GluonQMLPlayer;

class GameWindowManager::GameWindowManagerPrivate
{
    public:
        GameWindowManagerPrivate()
            : stackedWidget(new QStackedWidget(0))
            , achievementsModel(0)
            , gameItemsModel(new GluonPlayer::GameItemsModel())
            , commentItemsModel(0)
            , auth(0)
            , declarativeView(new QDeclarativeView(stackedWidget))
            , renderWidget(new GluonGraphics::RenderWidget(stackedWidget))
            , ctxt(0)
        {
        }

        ~GameWindowManagerPrivate()
        {
            delete stackedWidget;
            delete achievementsModel;
            delete gameItemsModel;
            delete commentItemsModel;
        }

        QString title;
        QString fileName;

        int msecElapsed;
        int frameCount;

        QStackedWidget* stackedWidget;
        GluonPlayer::AchievementsModel* achievementsModel;
        GluonPlayer::GameItemsModel* gameItemsModel;
        GluonPlayer::CommentItemsModel* commentItemsModel;
        GluonPlayer::Authentication* auth;

        QDeclarativeView* declarativeView;
        GluonGraphics::RenderWidget* renderWidget;
        QDeclarativeContext* ctxt;
        QObject* rootObj;
        QObject* login;
};

GameWindowManager::GameWindowManager( const QString& /* filename */ )
    : QObject()
    , d( new GameWindowManagerPrivate )
{
    d->auth = GluonPlayer::Authentication::instance();
    d->renderWidget->initializeGL();

    d->ctxt = d->declarativeView->rootContext();
    d->ctxt->setContextProperty( "authentication", d->auth );
    d->ctxt->setContextProperty( "achievementsModel", d->achievementsModel );
    d->ctxt->setContextProperty( "gameItemsModel", d->gameItemsModel );
    d->ctxt->setContextProperty( "commentItemsModel", d->commentItemsModel );
    d->ctxt->setContextProperty( "gameWindowManager", this );

    // Note QML enum handling is more or less bonkers at the moment
    // It should be removed after the QML enum support is not that flaky
    qmlRegisterUncreatableType<GluonPlayer::GameViewItem>( "GluonPlayerGameViewItem", 1, 0, "GameViewItem", QString( "Support the Status enumeration" ) );

    d->declarativeView->setSource( QUrl( "qrc:/main.qml" ) );

    d->rootObj = d->declarativeView->rootObject();
    d->login = d->rootObj->findChild<QObject*>( "login" );
    QObject::connect( d->auth, SIGNAL( initialized() ), d->login, SLOT( providerSet() ) );

    d->stackedWidget->addWidget( d->declarativeView );
    d->stackedWidget->addWidget( d->renderWidget );
    d->stackedWidget->setCurrentIndex( 0 );
    connect( QApplication::instance(), SIGNAL( lastWindowClosed() ), GluonEngine::Game::instance(), SLOT( stopGame() ) );
}

GameWindowManager::~GameWindowManager( )
{
    delete d;
}

bool GameWindowManager::isViewportGLWidget( )
{
    return qobject_cast<QGLWidget*>( d->declarativeView );
}

void GameWindowManager::startGame( )
{
    GluonCore::GluonObjectFactory::instance()->loadPlugins();

    m_project = new GluonEngine::GameProject();
    m_project->loadFromFile( m_gameFileName );

    GluonEngine::Game::instance()->setGameProject( m_project );
    GluonEngine::Game::instance()->setCurrentScene( m_project->entryPoint() );

    d->stackedWidget->setCurrentWidget( d->renderWidget );
    d->renderWidget->setFocus();
    GluonEngine::Game::instance()->runGame();
    d->stackedWidget->setCurrentWidget( d->declarativeView );
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
    m_gameFileName = d->gameItemsModel->index( index ).data( GluonPlayer::GameItemsModel::ProjectFileNameRole ).toString();
    openProject();
}

int GameWindowManager::availableGamesCount( ) const
{
    return d->gameItemsModel->rowCount();
}

void GameWindowManager::buildCommentsModel( int index )
{
    QString gameID = d->gameItemsModel->index( index ).data( GluonPlayer::GameItemsModel::IDRole ).toString();
    if( gameID.isEmpty() )
    {
        return;
    }

    d->commentItemsModel = new GluonPlayer::CommentItemsModel( gameID );
}

void GameWindowManager::setProject( const QModelIndex& index )
{
    m_gameFileName = index.data( GluonPlayer::GameItemsModel::ProjectFileNameRole ).toString();
    openProject();
}

void GameWindowManager::openProject()
{
    if( m_gameFileName.isEmpty() )
    {
        return;
    }

    connect( GluonEngine::Game::instance(), SIGNAL( painted( int ) ), d->renderWidget, SLOT( updateGL() ) );
    connect( GluonEngine::Game::instance(), SIGNAL( painted( int ) ), SLOT( countFrames( int ) ) );
    connect( GluonEngine::Game::instance(), SIGNAL( updated( int ) ), SLOT( updateTitle( int ) ) );

    GluonInput::InputManager::instance()->setFilteredObject( d->renderWidget );
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

    if( d->msecElapsed > 1000 )
    {
        // static int fps = d->frameCount;
        d->frameCount = 0;
        d->msecElapsed = 0;
    }
}

void GameWindowManager::countFrames( int /* time */ )
{
    d->frameCount++;
}

GluonPlayer::AchievementsModel* GameWindowManager::achievementsModel() const
{
    return d->achievementsModel;
}

void GameWindowManager::setAchievementsModel( GluonPlayer::AchievementsModel* achievementsModel )
{
    d->achievementsModel = achievementsModel;
}

GluonPlayer::GameItemsModel* GameWindowManager::gameItemsModel() const
{
    return d->gameItemsModel;
}

void GameWindowManager::setGameItemsModel( GluonPlayer::GameItemsModel* gameItemsModel )
{
    d->gameItemsModel = gameItemsModel;
}

GluonPlayer::CommentItemsModel* GameWindowManager::commentItemsModel() const
{
    return d->commentItemsModel;
}

void GameWindowManager::setCommentItemsModel( GluonPlayer::CommentItemsModel* commentItemsModel )
{
    d->commentItemsModel = commentItemsModel;
}

void GameWindowManager::show()
{
    d->stackedWidget->show();
}

#include "gamewindowmanager.moc"
