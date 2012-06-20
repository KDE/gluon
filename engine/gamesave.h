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
    class Scene;
    class GamePrivate;
    class Game;

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

        Q_INVOKABLE void save();
        Q_INVOKABLE void load();
        Q_INVOKABLE void scenegraph();

        /**
         * Print the current contents of the scene, along with their properties.
         */
	Q_INVOKABLE void debugPrint(QObject *);
    };
}

Q_DECLARE_METATYPE( GluonEngine::GameSave* )
#endif
