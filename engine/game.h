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

#ifndef GLUON_ENGINE_GAME_H
#define GLUON_ENGINE_GAME_H

#include "gluon_engine_export.h"

#include <QtCore/QObject>
#include <QtCore/QSharedData>
#include <QtCore/QThread>

#include <core/singleton.h>

namespace GluonCore
{
    class GameProject;
}

namespace GluonEngine
{
    class Scene;
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

    class GLUON_ENGINE_EXPORT Game : public GluonCore::Singleton<Game>
    {
        Q_OBJECT
        Q_PROPERTY(Scene* currentScene READ currentScene WRITE setCurrentScene)
        //TODO Fix this once moc doesnt choke on namespaces anymore
        //Q_PROPERTY(GluonCore::GameProject* gameProject READ gameProject WRITE setGameProject)

        public:
            int getCurrentTick();
            Scene * currentScene() const;

            GluonCore::GameProject * gameProject() const;

        public slots:
            void setGameProject(GluonCore::GameProject * newGameProject);

            void setCurrentScene(Scene * newCurrentScene);

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

            void stopGame();

            void setPause(bool pause);

            /**
             * Update all items in the current scene.
             */
            void updateAll();

        signals:
            void currentSceneChanged(GluonEngine::Scene*);
            void currentProjectChanged(GluonCore::GameProject*);

            void updated();
            void painted();

        private:
            friend class GluonCore::Singleton<Game>;

            Game(QObject * parent = 0);
            ~Game();
            Q_DISABLE_COPY(Game)

            QSharedDataPointer<GamePrivate> d;
    };
}

#endif // GLUON_ENGINE_GAME_H
