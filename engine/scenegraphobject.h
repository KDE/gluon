#ifndef GLUON_ENGINE_SCENEGRAPHOBJECT_H
#define GLUON_ENGINE_SCENEGRAPHOBJECT_H

#include <QObject>
#include <QList>
#include <engine/gameobject.h>
#include "gluon_engine_export.h"

namespace GluonEngine
{
    /**
     * A single entry in a scene graph. This contains all the information necessary for
     * further searching from within the scene graph. 
     */
    class GLUON_ENGINE_EXPORT SceneGraphObject: public QObject
    {
        Q_OBJECT
	/**
	 * Parent of this group/object
	 */
	SceneGraphObject *parent;
	/**
	 * A group of objects, that come under the same level of hierarchy,
	 * grouped by similar scripts/names
	 */
	QString groupname;
	/**
	 * This is the main object/group we target at this level
	 * Can be used, to perform same operation/set property for all 
	 * objects that fall under this group
	 */
	GluonCore::GluonObject *member;
	/**
	 * Children of the present 'member', each individual objects
	 */
	QList<SceneGraphObject*> children;
	/**
	 * Children that fall to groups
	 */
	QList<SceneGraphObject*> childrengroup;
	/**
	 * The hash formed, based on number of children, group
	 */
	long hash;
	/**
	 * The level at which the object falls, to track groups properly
	 * Maybe used for further functions, to perform operations at a given level
	 */
	int level;
	
    public:
        Q_INVOKABLE  SceneGraphObject();
        ~SceneGraphObject();
	
	/**
	 * To set the parent of the member object
	 */
	Q_INVOKABLE void setParent( SceneGraphObject* );
        /**
         * To set the member object
         */
        Q_INVOKABLE void setMember( GluonEngine::GameObject *object );
        /**
         * To get the member objects
         */
        Q_INVOKABLE GluonCore::GluonObject* getMember();
	/**
	 * To set the group names
	 */
	Q_INVOKABLE void setGroupName( QString );
	/**
	 * Add children to object, at this level
	 */
	Q_INVOKABLE void addChildren( QList<SceneGraphObject*> );
        /**
         * Get the children
         */
        Q_INVOKABLE QList<SceneGraphObject*> getChildren();
	/**
	 * Add a group of children
	 */
	Q_INVOKABLE void addChildrenGroup( QList<SceneGraphObject*> );
	/**
	 * Called, to set the hash
	 */
	Q_INVOKABLE void setHash( long );
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
    };
}

Q_DECLARE_METATYPE( GluonEngine::SceneGraphObject* )
#endif