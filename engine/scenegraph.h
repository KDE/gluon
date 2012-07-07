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

#ifndef GLUON_ENGINE_SCENEGRAPH_H
#define GLUON_ENGINE_SCENEGRAPH_H

#include "gameobject.h"
#include "tagobject.h"
#include "gluon_engine_export.h"
#include "scenegraphobject.h"

namespace GluonEngine
{
    class SceneGraphPrivate;
    class GLUON_ENGINE_EXPORT SceneGraph
    {
        /**
         * Initialization helper
         */
        void initHelper( bool ref );
        /**
         * Find the group/child from name
         */
        void findChild( QString name );
        void findChild( SceneGraphObject *object, QString name );
        /**
         * Get base/template object
         */
        void getBaseObject( GluonEngine::SceneGraphObject *object );

    public:
        Q_INVOKABLE SceneGraph( bool ref = false );
        SceneGraph( GluonEngine::GameObject* parent, bool ref = false );
        ~SceneGraph();

        /**
         * Get the root of the scene graph
         */
        Q_INVOKABLE SceneGraphObject* getRoot();

        /**
         * Populate the scene graph with all the scene contents
         */
        Q_INVOKABLE void populate( SceneGraphObject *object, int level );
        /**
         * For testing; print the scene graph
         */
        Q_INVOKABLE void debugprint( SceneGraphObject *object, int level );
        /**
         * Display the scene graph
         */
        Q_INVOKABLE void debugprint( SceneGraphObject *object );
        /**
         * Compare two scene graphs
         */
        Q_INVOKABLE void compare();
        /**
         * Compare graphs, with a root object passed
         */
         Q_INVOKABLE void compare( GluonEngine::SceneGraphObject* object );
         /**
          * Convert the scenegraph into a writable scene
          */
         Q_INVOKABLE GluonCore::GluonObject* toScene();

    private:
        SceneGraphPrivate* p;
    };
}
#endif