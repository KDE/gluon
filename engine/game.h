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

#ifndef GLUON_ENGINE_GAME_H
#define GLUON_ENGINE_GAME_H

#include "gluon_engine_export.h"

#include <QtCore/QObject>
#include <QtCore/QSharedData>
#include <QtCore/QThread>

#include <core/singleton.h>

namespace GluonEngine
{
    class GameObject;
    class Scene;
    class GamePrivate;
    class GameProject;

    class I : public QThread
    {
        public:
            static void sleep(unsigned long secs)
            {
                QThread::sleep(secs);
            }
            static void msleep(unsigned long msecs)
            {
                QThread::msleep(msecs);
            }
            static void usleep(unsigned long usecs)
            {
                QThread::usleep(usecs);
            }
    };

    class GLUON_ENGINE_EXPORT Game : public GluonCore::Singleton<Game>
    {
            Q_OBJECT
            Q_PROPERTY(Scene* currentScene READ currentScene WRITE setCurrentScene)
            //TODO Fix this once moc doesn't choke on namespaces anymore
            //Q_PROPERTY(GluonCore::GameProject* gameProject READ gameProject WRITE setGameProject)

        public:
            int getCurrentTick();
            Scene * currentScene() const;

            GluonEngine::GameProject * gameProject() const;

            Q_INVOKABLE bool isRunning() const;
            Q_INVOKABLE bool isPaused() const;
            
            /**
             * Retrieve an object from the current scene.
             *
             * @param name The name of the object
             */
            Q_INVOKABLE GluonEngine::GameObject* getFromScene(const QString &name);
            
            Q_INVOKABLE GluonEngine::GameObject* clone(GluonEngine::GameObject *obj);

            //TODO Implement
            //Q_INVOKABLE GameObject* spawn(const QString& prefabName);
            

        public slots:
            void setGameProject(GluonEngine::GameProject * newGameProject);

            void setCurrentScene(Scene * newCurrentScene);
            void setCurrentScene(const QString& sceneName);
            
            /**
             * Resets the current scene to its initial conditions
             */
            void resetCurrentScene();

            void runGame()
            {
                this->runGameFixedUpdate();
            }
            /**
             * Run the game at full framerate (with an optional maximum number of skipped frames), but with a fixed game update rate, defaulting to 25 updates per second
             * @param   int updatesPerSecond    The number of updates per second
             * @param   int maxFrameSkip The maximum number of frames that you're allowed to skip before forcing a redraw
             */
            void runGameFixedUpdate(int updatesPerSecond = 25, int maxFrameSkip = 5);

            /**
             * Run the game using a fixed time between each update
             * @param   int framesPerSecond The number of frames per second that the game will attempt to keep up with
             */
            void runGameFixedTimestep(int framesPerSecond = 25);

            void stopGame();

            void setPause(bool pause);
            
            /**
             * Initialize all objects in the current scene.
             */
            void initializeAll();
            /**
             * Start all objects in the current scene.
             */
            void startAll();
            /**
             * Draw all items in the current scene.
             */
            void drawAll(int time = 1);
            /**
             * Update all items in the current scene.
             */
            void updateAll(int time = 10);
            /**
             * Stop all objects in the current scene.
             */
            void stopAll();
            /**
             * Cleanup all objects in the current scene.
             */
            void cleanupAll();

        signals:
            void showDebug(const QString& debugText);
            void currentSceneChanged(GluonEngine::Scene*);
            void currentProjectChanged(GluonEngine::GameProject*);

            void updated(int);
            void painted(int);

        private:
            friend class GluonCore::Singleton<Game>;

            Game(QObject * parent = 0);
            ~Game();
            Q_DISABLE_COPY(Game)

            QSharedDataPointer<GamePrivate> d;
    };
}

#endif // GLUON_ENGINE_GAME_H
