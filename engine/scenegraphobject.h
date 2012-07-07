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

#include <QObject>
#include <QList>

#include "gameobject.h"
#include "gluon_engine_export.h"
#include "game.h"

namespace GluonEngine
{
    /**
     * A single entry in a scene graph. This contains all the information necessary for
     * further searching and operations from within the scene graph. 
     */
    class GLUON_ENGINE_EXPORT SceneGraphObject: public QObject
    {
        Q_OBJECT
	/**
	 * Parent of this group/object
	 */
	SceneGraphObject *parent;
        /**
         * If this object is to be a template for other objects
         */
        bool isBase;
	/**
	 * A group of objects, that come under the same level of hierarchy,
	 * grouped by similar scripts/names
	 */
	QString groupname;
        /**
         * This sets the object as group parent. If true, it doesn't hold
         * any member object, and only holds its children
         */
        bool grouphead;
	/**
	 * This is the main object/group we target at this level
	 * Can be used, to perform same operation/set property for all 
	 * objects that fall under this group
	 */
	GluonEngine::GameObject *member;
	/**
	 * Children of the present 'member', each individual objects
	 */
	QList<SceneGraphObject*> children;
	/**
	 * Children that fall to groups
	 */
	QList<SceneGraphObject*> childrengroup;
	/**
	 * The level at which the object falls, to track groups properly
	 * Maybe used for further functions, to perform operations at a given level
	 */
	int level;
        /**
         * A reference to the object this is a clone of/resembles most
         */
        GluonEngine::SceneGraphObject* refObject;
        /**
         * This object is a copy of the GameObject, but has only the
         * properties that are to be written. This is to ensure that
         * the actual GameObject that's used is kept as is.
         */
        GluonEngine::GameObject* modifiedMember;
	
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
        Q_INVOKABLE void setMember( GluonEngine::GameObject *object );
        /**
         * To get the member object
         */
        Q_INVOKABLE GluonEngine::GameObject* getMember();
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
        Q_INVOKABLE QList<SceneGraphObject*> getChildren();
	/**
	 * Add a group of children
	 */
	Q_INVOKABLE void addChildrenGroup( QList<SceneGraphObject*> );
	/**
	 * Set the level of hierarchy, for easy access and further operations
	 */
	Q_INVOKABLE void setLevel( int );
	/**
	 * Returns the number of children(excluding those under a group
	 */
	Q_INVOKABLE int childCount();
	/**
	 * Returns the number of groups of children
	 */
	Q_INVOKABLE int groupCount();
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
        Q_INVOKABLE QString getGroupName();
        /**
         * Get level
         */
        Q_INVOKABLE int getLevel();
        /**
         * Compare two objects by their properties,level and type
         */
        Q_INVOKABLE int compare( GluonEngine::SceneGraphObject* object );
        /**
         * To check if this object is a template/base
         */
        Q_INVOKABLE bool checkIsBase();
        /**
         * Set the reference object
         */
        Q_INVOKABLE void setRefObject( GluonEngine::SceneGraphObject* object );
        /**
         * Get the reference object
         */
        Q_INVOKABLE GluonEngine::SceneGraphObject* getRefObject();
        /**
         * This function is used to modify the GameObject that's contained,
         * to contain only the minimum number of required properties.
         * In essence, it creates a copy of the object that can be retrieved using
         * getModifiedMember()
         */
        Q_INVOKABLE void modifyMember();
        /**
         * Returns the modified Game Object of the member
         */
        Q_INVOKABLE GluonEngine::GameObject* getModifiedMember();
        /**
         * Returns the parent SceneGraphObject
         */
        Q_INVOKABLE GluonEngine::SceneGraphObject* getParent();
    };
}

Q_DECLARE_METATYPE( GluonEngine::SceneGraphObject* )
#endif