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

#ifndef GLUON_ENGINE_SCENE_H
#define GLUON_ENGINE_SCENE_H

#include "asset.h"
#include "savable.h"

namespace GluonEngine
{
    class GameObject;
    class ScenePrivate;

    /**
     * \brief The second level in the GameObject hierarchy
     *
     * The representation of scenes in a game as found in GluonEngine based games.
     * It is simply an Asset which provides a tree of GameObjects and Components which
     * comprise a scene in the game. Examples of what would be a scene are things
     * such as an intro, a menu, a level in a game. An example of something you would
     * not normally use a Scene for is an in-game menu; for this you would use a
     * Prefab.
     *
     * \note To get the current scene in a game, see the Game::currentScene property
     */
    class GLUON_ENGINE_EXPORT Scene : public Asset, public GluonEngine::Savable
    {
            Q_OBJECT
            Q_INTERFACES( GluonEngine::Asset )
            GLUON_OBJECT( GluonEngine::Scene )

            Q_CLASSINFO( "org.gluon.icon", "image-svg+xml" )

        public:
            Q_INVOKABLE Scene( QObject* parent = 0 );
            virtual ~Scene();

            /**
             * Set the file for this scene, extending with support for checking for dirtiness
             * (that is, to ensure data is not lost upon resetting the scene's filename)
             *
             * @param   newFile     The new file for the scene
             */
            virtual void setFile( const QUrl& newFile );

            /**
             * Set the new name of the scene.
             *
             * @param   newName     The new name to be set for the scene
             */
            virtual void setName( const QString& newName );

            /**
             * Write the contents of this scene to a device.
             *
             * Reimplemented from Savable::writeContents()
             */
            virtual void writeContents(QIODevice* device);

            /**
             * Return a reference to the scene tree itself (meaning the GluonObject hierarchy
             * which makes up the scene)
             */
            Q_INVOKABLE GluonEngine::GameObject* sceneContents();

            virtual QList< QAction* > actions();

        public Q_SLOTS:
            /**
             * If the scene's content is loaded, reload it from disk. Otherwise do nothing.
             */
            virtual void resetScene();

            /**
             *  Set this scene to the entry point of the current project.
             */
            void setEntryPoint( );

        protected:
            virtual void populateMetaInfo( GluonCore::MetaInfo* info );

        private:
            ScenePrivate* d;
    };
}

Q_DECLARE_METATYPE( GluonEngine::Scene* )

#endif // GLUON_ENGINE_SCENE_H
