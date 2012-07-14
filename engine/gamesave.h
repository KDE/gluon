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
    /**
     * For saving and loading game states, by serializing the 
     * current scene.
     */
    class GLUON_ENGINE_EXPORT GameSave : public GluonCore::GluonObject
    {
        Q_OBJECT
        GLUON_OBJECT( GluonEngine::GameSave )
        public:
            Q_INVOKABLE GameSave();
            ~GameSave();

            /**
            * Save the Game's engine state to a file.
            */
            Q_INVOKABLE void save();
            /**
            * Load a state from a file.
            */
            Q_INVOKABLE void load();
            /**
            * Save a minimal persistence file.
            */
            Q_INVOKABLE void partialSave();
            /**
            * Load from a minimal persistence file.
            */
            Q_INVOKABLE void partialLoad();
    };
}

Q_DECLARE_METATYPE( GluonEngine::GameSave* )
#endif
