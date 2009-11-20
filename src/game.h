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

#ifndef GLUON_GAME_H
#define GLUON_GAME_H

#include "gluon_export.h"

#include <QtCore/QObject>
#include <QtCore/QSharedData>
#include <QtCore/QThread>
#include <common/ksingleton.h>

namespace Gluon
{
    class GameProject;
    class GameObject;
    class GamePrivate;
    
    class I : public QThread
    {
        public:
            static void sleep(unsigned long secs) {
                QThread::sleep(secs);
            }
            static void msleep(unsigned long msecs) {
                QThread::msleep(msecs);
            }
            static void usleep(unsigned long usecs) {
                QThread::usleep(usecs);
            }
    };
    
    class GLUON_EXPORT Game : public KSingleton<Game>
    {
        Q_OBJECT
        Q_PROPERTY(GameObject* currentScene READ currentScene WRITE setCurrentScene)
        Q_PROPERTY(GameProject* gameProject READ gameProject WRITE setGameProject)
        
        public:
            GameObject * currentScene() const;
            void setCurrentScene(GameObject * newCurrentScene);
            
            GameProject * gameProject() const;
            void setGameProject(GameProject * newGameProject);
            
            void runGame() { this->runGameFixedUpdate(); }
            /**
             * Run the game at full framerate (with an optional maximum number of skipped frames), but with a fixed game update rate, defaulting to 25 updates per second
             * @param   int updatesPerSecond    The number of updates per second
             * @param   int maxFrameSkip The maximum number of frames that you're allowed to skip before forcing a redraw
             */
            void runGameFixedUpdate(int updatesPerSecond = 25, int maxFramesPerSeconds = 5);
            
            /**
             * Run the game using a fixed time between each update
             * @param   int framesPerSecond The number of frames per second that the game will attempt to keep up with
             */
            void runGameFixedTimestep(int framesPerSecond = 25);
            
            int getCurrentTick();

        signals:
            void currentSceneChanged(GameObject*);
            void currentProjectChanged(GameProject*);
            
        private:
            friend class KSingleton<Game>;
            
            Game(QObject * parent = 0);
            ~Game();
            
            QSharedDataPointer<GamePrivate> d;
    };
}

#endif // GLUON_GAME_H
