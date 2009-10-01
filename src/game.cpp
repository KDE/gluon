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

#include <QThread>
#include <QTime>
#include <QDebug>

using namespace Gluon;

Game::Game(QObject * parent)
{
    d = new GamePrivate;
}

Game::Game(const Game &other, QObject * parent)
    : QObject(parent)
    , d(other.d)
{
}

Game::~Game()
{
}

void
Game::setCurrentLevel(GameObject * newCurrentLevel)
{
    d->currentLevel = newCurrentLevel;
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
    if(!d->currentLevel)
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
            d->currentLevel->Update(millisecondsPerUpdate);
            nextTick += millisecondsPerUpdate;
            loops++;
        }
        
        timeLapse = (getCurrentTick() + millisecondsPerUpdate - nextTick) / millisecondsPerUpdate;
        d->currentLevel->Draw(timeLapse);
    }
}

void
Game::runGameFixedTimestep(int framesPerSecond)
{
    // Bail out if we're not fed a level to work with!
    if(!d->currentLevel)
        return;
    
    int millisecondsPerUpdate = 1000 / framesPerSecond;
    
    int remainingSleep = 0;
    int nextTick = 0;
    d->time.start();
    
    d->gameRunning = true;
    
    while(d->gameRunning)
    {
        // Update the current level
        d->currentLevel->Update(millisecondsPerUpdate);
        // Do drawing
        d->currentLevel->Draw();
        
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

#include "game.moc"