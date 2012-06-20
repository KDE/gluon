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

#include <QObject>
#include <engine/gameobject.h>
#include <engine/tagobject.h>
#include "gluon_engine_export.h"
#include "scenegraphobject.h"

namespace GluonEngine
{
    class GLUON_ENGINE_EXPORT SceneGraph: public QObject
    {
        Q_OBJECT
	GluonEngine::SceneGraphObject* root;
        GluonEngine::TagObject *tags;

    public:
        Q_INVOKABLE SceneGraph();
        SceneGraph( GluonEngine::GameObject* parent );
        ~SceneGraph();

        Q_INVOKABLE SceneGraphObject* getRoot();

        /**
         * Populate the scene graph with all the scene contents
         */
        Q_INVOKABLE void populate( SceneGraphObject *object, int level );
        /**
         * For testing; print the scene graph
         */
        Q_INVOKABLE void debugprint( SceneGraphObject *object, int level );
        Q_INVOKABLE void debugprint( SceneGraphObject *object );
    };
}

Q_DECLARE_METATYPE( GluonEngine::SceneGraph* )
#endif