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

#ifndef GLUON_ENGINE_SCENEGRAPHOBJECT_H
#define GLUON_ENGINE_SCENEGRAPHOBJECT_H

#include <QList>

#include "gameobject.h"
#include "gluon_engine_export.h"
#include "game.h"

namespace GluonEngine
{
    class SceneGraphObjectPrivate;
    /**
     * A single entry in a scene graph. This contains all the information necessary for
     * further searching and operations from within the scene graph. 
     */
    class GLUON_ENGINE_EXPORT SceneGraphObject
    {
        public:
            Q_INVOKABLE  SceneGraphObject();
            ~SceneGraphObject();
            /**
            * This value is 2 if not compared ( not present in other graph ),
            * 1 if it differs from the similar object in the other graph and 0 otherwise.
            */
            int diff;
            /**
            * To set the parent of the member object
            */
            Q_INVOKABLE void setParent( SceneGraphObject* );
            /**
            * To set the member object
            */
            Q_INVOKABLE void setGameObject( GluonEngine::GameObject *object );
            /**
            * To get the member object
            */
            Q_INVOKABLE GluonEngine::GameObject* gameObject();
            /**
            * To set the group names
            */
            Q_INVOKABLE void setGroupName( QString );
            /**
            * Add children to object, at this level
            */
            Q_INVOKABLE void addChildren( QList<SceneGraphObject*> );
            Q_INVOKABLE void addChild( SceneGraphObject* child );
            /**
            * Get the children
            */
            Q_INVOKABLE QList<SceneGraphObject*> children();
            /**
            * Set the level of hierarchy, for easy access and further operations
            */
            Q_INVOKABLE void setLevel( int );
            /**
            * Returns the number of children(excluding those under a group
            */
            Q_INVOKABLE int childCount();
            /**
            * Set object as grouphead
            */
            Q_INVOKABLE void setGroupHead( bool value );
            /**
            * Check if the object is a grouphead
            */
            Q_INVOKABLE bool isGroupHead();
            /**
            * Get the group name
            */
            Q_INVOKABLE QString groupName();
            /**
            * Get level
            */
            Q_INVOKABLE int level();
            /**
            * Compare two objects by their properties,level and type
            */
            Q_INVOKABLE int compare( GluonEngine::SceneGraphObject* object );
            /**
            * To check if this object is a template/base
            */
            Q_INVOKABLE bool isBase();
            /**
            * Set the reference object
            */
            Q_INVOKABLE void setRefObject( GluonEngine::SceneGraphObject* object );
            /**
            * Get the reference object
            */
            Q_INVOKABLE GluonEngine::SceneGraphObject* refObject();
            /**
            * This function is used to modify the GameObject that's contained,
            * to contain only the minimum number of required properties.
            * In essence, it creates a copy of the object that can be retrieved using
            * getModifiedMember()
            */
            Q_INVOKABLE void modifyGameObject();
            /**
             * This function builds a gameobject from a partial save.
             */
            Q_INVOKABLE void buildGameObject();
            /**
            * Returns the modified Game Object of the member
            */
            Q_INVOKABLE GluonEngine::GameObject* modifiedGameObject();
            /**
            * Returns the parent SceneGraphObject
            */
            Q_INVOKABLE GluonEngine::SceneGraphObject* parent();

        private:
            SceneGraphObjectPrivate* p;
    };
}

#endif