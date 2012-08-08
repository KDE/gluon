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
    /**
    * This contains the scene with additional functionalities,
    * and is represented as a graph.
    * compare() has to be called before the scene can be saved.
    * build() is called before the scene is loaded into memory.
    */
    class GLUON_ENGINE_EXPORT SceneGraph
    {
        /**
         * Find the group/child from name
         */
        void findChild( QString name );
        void findChild( SceneGraphObject *object, QString name );
        /**
         * Get base/template object
         */
        void baseObject( GluonEngine::SceneGraphObject *object );

    public:
        /**
         * Use this, when the graph is to be populated with existing contents on the screen.
         */
        Q_INVOKABLE SceneGraph( bool ref = false );
        /**
         * Use this, when the graph is to be populated with contents read from a file.
         */ 
        Q_INVOKABLE SceneGraph( GluonEngine::GameObject* parent, bool ref = false );
        ~SceneGraph();

        /**
         * Get the root of the scene graph
         */
        Q_INVOKABLE SceneGraphObject* root();

        /**
         * Populate the scene graph with all the scene contents
         */
        Q_INVOKABLE void populate( SceneGraphObject *object );
        /**
         * Set the reference graph explicitly
         * @param: pathtoref is the url from which the reference scene is built.
         */
        Q_INVOKABLE void setRefGraph( QUrl pathtoref );
        /**
         * Compare two scene graphs
         */
         Q_INVOKABLE void compare( GluonEngine::SceneGraphObject* object );
         /**
          * This builds the scene graph from a partial save, by setting properties
          * and adding missing components.
          * 
          * See also: compare()
          */
         Q_INVOKABLE void build( GluonEngine::SceneGraphObject* object );
         /**
          * Convert the scenegraph into a writable scene
          */
         Q_INVOKABLE GluonCore::GluonObject* toScene();
         /**
          * Returns a GameObject scene hierarchy for saving
          */
         Q_INVOKABLE GluonCore::GluonObject* forSave();
         /**
          * Returns a GameObject scene hierarchy for loading.
          * Steps to completed before calling this:
          * setRefGraph() : From a partial save, the Url to the scene it refers is read and passed.
          */
         Q_INVOKABLE GluonEngine::GameObject* forLoad();

    private:
        SceneGraphPrivate* p;
    };
}
#endif