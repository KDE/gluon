#ifndef GLUON_ENGINE_SCENEGRAPHOBJECT_H
#define GLUON_ENGINE_SCENEGRAPHOBJECT_H

#include <QObject>
#include <QList>
#include <core/gluonobject.h>
#include "gluon_engine_export.h"

namespace GluonEngine
{
    /*
     * A single entry in a scene graph. This contains all the information necessary for
     * further searching from within the scene graph. 
     */
    class GLUON_ENGINE_EXPORT SceneGraphObject : public GluonCore::GluonObject
    {
        Q_OBJECT
        GLUON_OBJECT( GluonEngine::SceneGraphObject )
	
	/*
	 * Parent of this group/object
	 */
	SceneGraphObject *parent;
	/*
	 * A group of objects, that come under the same level of hierarchy,
	 * grouped by similar scripts/names
	 */
	QString groupName;
	/*
	 * This is the main object/group we target at this level
	 * Can be used, to perform same operation/set property for all 
	 * objects that fall under this group
	 */
	GluonCore::GluonObject *member;
	/*
	 * Children of the present 'member', each individual objects
	 */
	QList<GluonObject*> children;
	/*
	 * Children that fall to groups
	 */
	QList<SceneGraphObject*> childrenGroup;
	/*
	 * The hash formed, based on number of children, group
	 */
	long hash;
	/*
	 * The level at which the object falls, to track groups properly
	 * Maybe used for further functions, to perform operations at a given level
	 */
	int level;
	
    public:
        Q_INVOKABLE  SceneGraphObject();
        Q_INVOKABLE SceneGraphObject( SceneGraphObject*, QString, GluonCore::GluonObject*, QList<GluonObject*>, QList<SceneGraphObject*> );
        ~SceneGraphObject();
	
	/*
	 * To set the parent of the member object
	 */
	Q_INVOKABLE void setParent( SceneGraphObject* );
	/*
	 * To set the group names
	 */
	Q_INVOKABLE void setGroupName( QString );
	/*
	 * Add children to object, at this level
	 */
	Q_INVOKABLE void addChildren( QList<GluonObject*> );
	/*
	 * Add a group of children
	 */
	Q_INVOKABLE void addChildrenGroup( QList<SceneGraphObject*> );
	/*
	 * Called, to set the hash
	 */
	Q_INVOKABLE void setHash( long );
	/*
	 * Set the level of hierarchy, for easy access and further operations
	 */
	Q_INVOKABLE void setLevel( int );
	/*
	 * Returns the number of children(excluding those under a group
	 */
	Q_INVOKABLE int childCount();
	/*
	 * Returns the number of groups of children
	 */
	Q_INVOKABLE int groupCount();
    };
}

Q_DECLARE_METATYPE( GluonEngine::SceneGraphObject* )
#endif