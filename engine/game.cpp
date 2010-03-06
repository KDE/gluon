/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "game.h"
#include "gameprivate.h"
#include "scene.h"
#include "gameobject.h"
#include "gameproject.h"

#include "core/debughelper.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QThread>
#include <QtCore/QTime>
#include <QtCore/QDebug>

using namespace GluonEngine;

template<> GLUON_ENGINE_EXPORT Game *GluonCore::Singleton<Game>::m_instance = 0;

Game::Game(QObject * parent)
{
    Q_UNUSED(parent);
    d = new GamePrivate;
}

Game::~Game()
{
}

int
Game::getCurrentTick()
{
    return d->time.elapsed();
}

void
Game::runGameFixedUpdate(int updatesPerSecond, int maxFrameSkip)
{
    DEBUG_FUNC_NAME
    // Bail out if we're not fed a level to work with!
    if(!d->currentScene)
    {
        DEBUG_TEXT(QString("There is no scene to run!"));
        return;
    }

    int millisecondsPerUpdate = 1000 / updatesPerSecond;
    DEBUG_TEXT(QString("Running the game using fixed update at %1 updates per second (meaning %2 milliseconds between each update, and drawing as often as possible, with a maximum of %3 frames skipped before forcing a draw)").arg(updatesPerSecond).arg(millisecondsPerUpdate).arg(maxFrameSkip));

    int nextTick = 0, loops = 0;
    int timeLapse = 0;
    d->time.start();

    d->gameRunning = true;

    // First allow everybody to initialize themselves properly
    d->currentScene->startAll();
    while(d->gameRunning)
    {
        // Don't block everything...
        QCoreApplication::processEvents();

        // Only update every updatesPerSecond times per second, but draw the scene as often as we can force it to

        loops = 0;
        while(getCurrentTick() > nextTick && loops < maxFrameSkip)
        {
            if(!d->gamePaused)
            {
                d->currentScene->updateAll(millisecondsPerUpdate);
                emit updated();
            }
            nextTick += millisecondsPerUpdate;
            loops++;
        }

        timeLapse = (getCurrentTick() + millisecondsPerUpdate - nextTick) / millisecondsPerUpdate;
        d->currentScene->drawAll(timeLapse);
        emit painted();
    }
    d->currentScene->stopAll();
}

void
Game::runGameFixedTimestep(int framesPerSecond)
{
    DEBUG_FUNC_NAME
    // Bail out if we're not fed a level to work with!
    if(!d->currentScene)
    {
        DEBUG_TEXT(QString("There is no scene to run!"));
        return;
    }

    int millisecondsPerUpdate = 1000 / framesPerSecond;
    DEBUG_TEXT(QString("Running the game using fixed timestep at %1 frames per second (meaning %2 milliseconds between each update and draw)").arg(framesPerSecond).arg(millisecondsPerUpdate));

    int remainingSleep = 0;
    int nextTick = 0;
    d->time.start();

    d->gameRunning = true;

    // First allow everybody to initialize themselves properly
    d->currentScene->startAll();
    while(d->gameRunning)
    {
        // Don't block everything...
        QCoreApplication::processEvents();

        // Update the current level
        if(!d->gamePaused)
        {
            d->currentScene->updateAll(millisecondsPerUpdate);
            emit updated();
        }
        // Do drawing
        d->currentScene->drawAll();
        emit painted();

        nextTick += millisecondsPerUpdate;
        remainingSleep = nextTick - this->getCurrentTick();
        if(remainingSleep > 0)
        {
            DEBUG_TEXT(QString("Sleeping for %1 milliseconds").arg(remainingSleep))
            I::msleep(remainingSleep);
        }
        else
        {
            // Oh buggery, we're falling behind... can we fix this in a generic manner? Or do we just allow for falling behind...
            DEBUG_TEXT(tr("Gameloop has fallen behind by %1 milliseconds").arg(remainingSleep))
        }
    }
    d->currentScene->stopAll();
}

void Game::stopGame()
{
    DEBUG_BLOCK
    DEBUG_TEXT(QString("Stopping gameloop"))

    d->gameRunning = false;
}

void Game::setPause(bool pause)
{
    DEBUG_BLOCK
    if(pause)
    { DEBUG_TEXT(QString("Pausing gameloop")) }
    else
    { DEBUG_TEXT(QString("Un-pausing gameloop")) }

    d->gamePaused = pause;
}

void Game::drawAll()
{
    d->currentScene->drawAll(1);
    emit painted();
}

void Game::updateAll()
{
    d->currentScene->updateAll(10);
    emit updated();
}

/******************************************************************************
 * Property Getter-setters
 *****************************************************************************/

Scene *
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
Game::setCurrentScene(Scene * newCurrentScene)
{
    if(d->currentScene) {
        d->currentScene->stopAll();
    }

    d->currentScene = newCurrentScene;
    emit currentSceneChanged(newCurrentScene);
}

void Game::setCurrentScene(const QString& sceneName)
{
    Scene* scene = qobject_cast< GluonEngine::Scene* >(gameProject()->findItemByName(sceneName));
    if(scene)
        setCurrentScene(scene);
}

GluonEngine::GameProject *
Game::gameProject() const
{
    return d->gameProject;
}
void
Game::setGameProject(GluonEngine::GameProject * newGameProject)
{
    DEBUG_FUNC_NAME
    d->gameProject = newGameProject;

    if(!gameProject()->entryPoint())
    {
        DEBUG_TEXT(QString("Entry point invalid, attempting to salvage"))
        Scene *scene = GamePrivate::findSceneInChildren(newGameProject);
        if(scene)
        {
            gameProject()->setEntryPoint(scene);
            DEBUG_TEXT(QString("Entry point salvaged by resetting to first Scene in project - %1").arg(scene->fullyQualifiedName()))
        }
    }

    if(gameProject()->entryPoint())
    {
        DEBUG_TEXT(QString("Set the gameproject to %1 with the entry point %2").arg(gameProject()->name()).arg(gameProject()->entryPoint()->name()))
    }
    else
    {
        DEBUG_TEXT(QString("Somehow we have got here with no entrypoint... This is very, very wrong!"))
    }

    setCurrentScene(qobject_cast<Scene*>(newGameProject->entryPoint()));
    emit currentProjectChanged(newGameProject);
}


#include "game.moc"
