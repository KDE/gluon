/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2012 Vinay S Rao <sr.vinay@gmail.com>
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

#ifndef GLUON_ENGINE_GAMESAVE_H
#define GLUON_ENGINE_GAMESAVE_H

#include <core/gluonobject.h>
#include "gluon_engine_export.h"

namespace GluonEngine
{
    class GameObject;
    class GameSavePrivate;

    /**
     * For saving and loading game states, by serializing the 
     * current scene.
     */
    class GLUON_ENGINE_EXPORT GameSave : public GluonCore::GluonObject
    {
        Q_OBJECT
        public:
            Q_INVOKABLE GameSave( QObject *parent );
            ~GameSave();

            /**
            * Save the Game's engine state to a file.
            */
            void save();

            /**
            * Load a state from a file.
            */
            void load();

            /**
            * Save a minimal persistence file.
            */
            void partialSave();

            /**
            * Load from a minimal persistence file.
            */
            void partialLoad();

            /**
             * Serialize all the components of a given object and of all its children.
             * @param: object is the game object whose components are to be serialized.
             */
            void serializeComponents( GluonEngine::GameObject* object );

            /**
             * Restore all the components of a given object and of all its children to a saved state.
             * @param: object is the game object whose components are to be restored.
             */
            void restoreComponents( GluonEngine::GameObject* object );
            
            /**
             * Returns the most recent save's directory ( the full path )
             */
            QString latestSave();
            
        private:
            GameSavePrivate *g;
    };
}

Q_DECLARE_METATYPE( GluonEngine::GameSave* )
#endif
