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
            * This value is 2 if not compared ( not present in the reference graph ),
            * 1 if it differs from the similar object in the other graph and 0 if it's a perfect match.
            */
            int diff;
            /**
            * Sets the parent of the current object
            */
            Q_INVOKABLE void setParent( SceneGraphObject* parent );
            /**
            * This sets the GameObject contained within, as:
            * @param: object
            */
            Q_INVOKABLE void setGameObject( GluonEngine::GameObject *object );
            /**
            * Returns the GameObject that's contained within this SceneGraphObject
            */
            Q_INVOKABLE GluonEngine::GameObject* gameObject();
            /**
            * Sets the name of the group the object belongs to, if any
            */
            Q_INVOKABLE void setGroupName( QString groupname );
            /**
            * Add children to object, at this level
            */
            Q_INVOKABLE void addChildren( QList<SceneGraphObject*> );
            /**
             * Add a child to the object
             */
            Q_INVOKABLE void addChild( SceneGraphObject* child );
            /**
            * Returns the children of the object
            */
            Q_INVOKABLE QList<SceneGraphObject*> children();
            /**
            * Set the level of hierarchy, for easy access and further operations
            */
            Q_INVOKABLE void setLevel( int );
            /**
            * Returns the number of children of the object
            */
            Q_INVOKABLE int childCount();
            /**
            * Make the object, the head of a group
            */
            Q_INVOKABLE void setGroupHead( bool value );
            /**
            * Check if the object is the head of a group
            */
            Q_INVOKABLE bool isGroupHead();
            /**
            * Returns the name of the group the object belongs to
            */
            Q_INVOKABLE QString groupName();
            /**
            * Get level of the object in the hierarchy of the graph ( height )
            */
            Q_INVOKABLE int level();
            /**
            * Compare two objects by their properties,level and type
            */
            Q_INVOKABLE int compare( GluonEngine::SceneGraphObject* object );
            /**
            * To check if this object is a template/base object.
            * In other words, it forms as a reference for other objects.
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
            * modifiedGameObject()
            */
            Q_INVOKABLE void modifyGameObject();
            /**
             * This function builds a gameobject from a partial save. It adds properties and
             * components that are necessary for the scene.
             */
            Q_INVOKABLE void buildGameObject();
            /**
            * Returns the modified GameObject of the contained GameObject
            */
            Q_INVOKABLE GluonEngine::GameObject* modifiedGameObject();
            /**
            * Returns the parent SceneGraphObject
            */
            Q_INVOKABLE GluonEngine::SceneGraphObject* parent();
            /**
             * Use this method to check if a QVariant is the '0' equivalent.
             * eg: "" for QString, 0 for int, <> for lists
             */
            Q_INVOKABLE bool isIdentity( QVariant var );

        private:
            SceneGraphObjectPrivate* p;
            /**
             * Use this function to set properties of one component onto another.
             */
            void copyComponentProperties( GluonEngine::Component* copy, GluonEngine::Component* original );
    };
}

#endif