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
#include "gameproject/gameobject.h"
#include "gameproject/gameproject.h"
#include "debughelper.h"

#include <QtCore/QThread>
#include <QtCore/QTime>
#include <QtCore/QDebug>

using namespace Gluon;

template<> GLUON_EXPORT Game *KSingleton<Game>::m_instance = 0;

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
    // Bail out if we're not fed a level to work with!
    if(!d->currentScene)
        return;

    int millisecondsPerUpdate = 1000 / updatesPerSecond;

    int nextTick = 0, loops = 0;
    int timeLapse = 0;
    d->time.start();

    d->gameRunning = true;

    while(d->gameRunning)
    {
        // Only update every updatesPerSecond times per second, but draw the scene as often as we can force it to

        loops = 0;
        while(getCurrentTick() > nextTick && loops < maxFrameSkip)
        {
            d->currentScene->update(millisecondsPerUpdate);
            nextTick += millisecondsPerUpdate;
            loops++;
        }

        timeLapse = (getCurrentTick() + millisecondsPerUpdate - nextTick) / millisecondsPerUpdate;
        d->currentScene->draw(timeLapse);
    }
}

void
Game::runGameFixedTimestep(int framesPerSecond)
{
    DEBUG_FUNC_NAME
    DEBUG_TEXT(QString("Running the game using fixed timestep at %1 frames per second").arg(framesPerSecond));
    // Bail out if we're not fed a level to work with!
    if(!d->currentScene)
    {
        DEBUG_TEXT(QString("There is no scene to run!"));
        return;
    }

    int millisecondsPerUpdate = 1000 / framesPerSecond;

    int remainingSleep = 0;
    int nextTick = 0;
    d->time.start();

    d->gameRunning = true;

    while(d->gameRunning)
    {
        // Update the current level
        d->currentScene->update(millisecondsPerUpdate);
        // Do drawing
        d->currentScene->draw();

        nextTick += millisecondsPerUpdate;
        remainingSleep = nextTick - this->getCurrentTick();
        if(remainingSleep > 0)
        {
            I::msleep(remainingSleep);
        }
        else
        {
            // Oh buggery, we're falling behind... can we fix this in a generic manner? Or do we just allow for falling behind...
            qDebug() << tr("Gameloop has fallen behind by %1 milliseconds").arg(QString(remainingSleep));
        }
    }
}

/******************************************************************************
 * Property Getter-setters
 *****************************************************************************/

GameObject *
Game::currentScene() const
{
    return d->currentScene;
}
void
Game::setCurrentScene(GameObject * newCurrentScene)
{
    d->currentScene = newCurrentScene;
    emit currentSceneChanged(newCurrentScene);
}

GameProject *
Game::gameProject() const
{
    return d->gameProject;
}
void
Game::setGameProject(GameProject * newGameProject)
{
    DEBUG_FUNC_NAME
    d->gameProject = newGameProject;
    
    if(!gameProject()->entryPoint())
    {
        DEBUG_TEXT(QString("Entry point invalid, attempting to salvage"))
        foreach(QObject * obj, newGameProject->children())
        {
            GameObject *gameObj = qobject_cast<GameObject*>(obj);
            if(gameObj)
            {
                newGameProject->setEntryPoint(gameObj);
                DEBUG_TEXT(QString("Entry point salvaged by resetting to first game object in project"))
                break;
            }
        }
    }

    if(newGameProject->entryPoint())
    {
        DEBUG_TEXT(QString("Setting the gameproject to %1 with the entry point %2").arg(newGameProject->name()).arg(newGameProject->entryPoint()->name()))
    }
    else
    {
        DEBUG_TEXT(QString("Somehow we have got here with no entrypoint... This is very, very wrong!"))
    }
    
    setCurrentScene(newGameProject->entryPoint());
    emit currentProjectChanged(newGameProject);
}


#include "game.moc"