/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (C) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

#include "game.h"
#include "gameprivate.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QThread>
#include <QtCore/QTime>
#include <QtCore/QTimer>

#include <core/directoryprovider.h>
#include <core/log.h>

#include "scene.h"
#include "gameobject.h"
#include "gameproject.h"
#include "achievementsmanager.h"

using namespace GluonEngine;

GLUON_DEFINE_SINGLETON( Game )

class I : public QThread
{
    public:
        static void sleep( unsigned long secs )
        {
            QThread::sleep( secs );
        }
        static void msleep( unsigned long msecs )
        {
            QThread::msleep( msecs );
        }
        static void usleep( unsigned long usecs )
        {
            QThread::usleep( usecs );
        }
};

Game::Game( QObject* parent )
    : GluonCore::Singleton< GluonEngine::Game >( parent ), d( new GamePrivate( this ) )
{
    qsrand( QTime( 0, 0, 0 ).secsTo( QTime::currentTime() ) );
}

Game::~Game()
{
    if( d->gameRunning )
        stopGame();
}

int
Game::getCurrentTick()
{
    return d->time.elapsed();
}

void
Game::runGameFixedUpdate( int updatesPerSecond, int maxFrameSkip )
{
    // Bail out if we're not fed a level to work with!
    if( !d->currentScene )
    {
        ERROR() << "There is no scene to run!";
        return;
    }

    //Clean any traces of existing objects.
    stopAll();
    cleanupAll();;

    int millisecondsPerUpdate = 1000 / updatesPerSecond;
    DEBUG() << "Running the game using fixed update at " << updatesPerSecond << " updates per second (" << millisecondsPerUpdate << "ms per update, max frame skip " << maxFrameSkip << ")";

    int nextTick = 0, loops = 0;
    int timeLapse = 0;
    d->time.start();

    d->gameRunning = true;

    initializeAll();
    // First allow everybody to initialize themselves properly
    startAll();
    while( d->gameRunning )
    {
        // Don't block everything...
        QCoreApplication::processEvents();

        if( d->newScene != 0 )
            d->performSceneChange();

        // Only update every updatesPerSecond times per second, but draw the scene as often as we can force it to
        loops = 0;
        while( getCurrentTick() > nextTick && loops < maxFrameSkip )
        {
            if( !d->gamePaused )
            {
                updateAll( millisecondsPerUpdate );
            }
            nextTick += millisecondsPerUpdate;
            loops++;
        }

        timeLapse = ( getCurrentTick() + millisecondsPerUpdate - nextTick ) / millisecondsPerUpdate;
        drawAll( timeLapse );
    }
    stopAll();

    cleanupAll();
}

void
Game::runGameFixedTimestep( int framesPerSecond )
{
    // Bail out if we're not fed a level to work with!
    if( !d->currentScene )
    {
        ERROR() << "There is no scene to run!";
        return;
    }

    int millisecondsPerUpdate = 1000 / framesPerSecond;
    DEBUG() << "Running the game using fixed timestep at " << framesPerSecond << " frames per second (meaning " << millisecondsPerUpdate << " milliseconds between each update and draw)";

    int remainingSleep = 0;
    int nextTick = 0;
    d->time.start();

    d->gameRunning = true;

    initializeAll();
    // First allow everybody to initialize themselves properly
    startAll();
    while( d->gameRunning )
    {
        // Don't block everything...
        QCoreApplication::processEvents();

        // Update the current level
        if( !d->gamePaused )
        {
            updateAll( millisecondsPerUpdate );
        }
        // Do drawing
        drawAll();

        nextTick += millisecondsPerUpdate;
        remainingSleep = nextTick - this->getCurrentTick();
        if( remainingSleep > 0 )
        {
            DEBUG() << "Sleeping for " << remainingSleep << " milliseconds";
            I::msleep( remainingSleep );
        }
        else
        {
            // Oh buggery, we're falling behind... can we fix this in a generic manner? Or do we just allow for falling behind...
            DEBUG() << "Gameloop has fallen behind by " << remainingSleep << " milliseconds";
        }
    }
    stopAll();

    cleanupAll();
}

void Game::stopGame()
{
    DEBUG() << "Stopping gameloop";

    d->gameRunning = false;
}

void Game::setPause( bool pause )
{
    if( pause )
    {
        DEBUG() << "Pausing gameloop";
    }
    else
    {
        DEBUG() << "Un-pausing gameloop";
    }

    d->gamePaused = pause;
}

void Game::initializeAll()
{
    if(!d->gameProject)
    {
        ERROR() << "You are attempting to initialize all objects in the game, but there is no game project loaded.";
    }
    d->currentScene->sceneContents()->initialize();
    emit initialized();
}

void Game::startAll()
{
    d->currentScene->sceneContents()->start();
    emit started();
}

void Game::drawAll( int time )
{
    d->currentScene->sceneContents()->draw( time );
    emit painted( time );
}

void Game::updateAll( int time )
{
    d->currentScene->sceneContents()->update( time );
    emit updated( time );
}

void Game::stopAll()
{
    d->currentScene->sceneContents()->stop();
    emit stopped();
}

void Game::cleanupAll()
{
    d->currentScene->sceneContents()->cleanup();
    // Save the achievements in an extra file for the player application
    AchievementsManager achievementsManager;
    achievementsManager.readFromProject(d->gameProject->achievements());
    QString saveDirectory = GluonCore::DirectoryProvider::instance()->userDirectory("data");
    saveDirectory.append( '/' + d->gameProject->userName() + '/' + d->gameProject->name() );
    achievementsManager.save(saveDirectory);
    emit cleaned();
}

float Game::random()
{
    return qrand() / float( RAND_MAX );
}

/******************************************************************************
 * Property Getter-setters
 *****************************************************************************/

Scene*
Game::currentScene() const
{
    return d->currentScene;
}

bool Game::isRunning() const
{
    return d->gameRunning;
}

bool Game::isPaused() const
{
    return d->gamePaused;
}

void
Game::setCurrentScene( Scene* newCurrentScene )
{
    d->newScene = newCurrentScene;
    if( !d->gameRunning )
    {
        d->performSceneChange();
    }
}

void Game::setCurrentScene( const QString& sceneName )
{
    Scene* scene = qobject_cast< GluonEngine::Scene* >( gameProject()->findGlobalItemByName( sceneName ) );
    if( scene )
        setCurrentScene( scene );
}

void Game::resetCurrentScene()
{
    if( d->currentScene )
    {
        QTimer::singleShot( 0, d->currentScene, SLOT(resetScene()) );
    }
}

GluonEngine::GameProject*
Game::gameProject() const
{
    return d->gameProject;
}

void
Game::setGameProject( GluonEngine::GameProject* newGameProject )
{
    if( d->gameProject )
    {
        if( d->currentScene )
        {
            stopAll();
            cleanupAll();
        }
    }

    d->gameProject = newGameProject;

    if( !d->gameProject )
        return;

    if( !d->gameProject->entryPoint() )
    {
        WARNING() << "Entry point invalid, attempting to salvage";
        Scene* scene = GamePrivate::findSceneInChildren( d->gameProject );
        if( scene )
        {
            d->gameProject->setEntryPoint( scene );
            NOTICE() << "Entry point salvaged by resetting to first Scene in project - " << scene->fullyQualifiedName();
        }
    }

    if( d->gameProject->entryPoint() )
    {
        DEBUG() << "Set the gameproject to " << d->gameProject->name() << " with the entry point " << d->gameProject->entryPoint()->name();
    }
    else
    {
        CRITICAL() << "Somehow we have got here with no entrypoint... This is very, very wrong!";
        return;
    }

    d->currentScene = d->gameProject->entryPoint();
    emit currentProjectChanged( d->gameProject );
    emit currentSceneChanged( d->currentScene );
}

GameObject* Game::getFromScene( const QString& name )
{
    return d->currentScene->sceneContents()->childGameObject( name );
}

GameObject* Game::clone( GameObject* obj )
{
    if( obj )
    {
        GameObject* objClone = qobject_cast<GameObject*>( obj->clone() );
        QList<const GluonCore::GluonObject*> objects = d->listAllChildren( objClone );
        foreach( const GluonCore::GluonObject * child, objects )
        {
            connect( child, SIGNAL(showDebug(QString,GluonCore::DebugType)), SIGNAL(showDebug(QString,GluonCore::DebugType)) );
        }
        return objClone;
    }

    return 0;
}

 
