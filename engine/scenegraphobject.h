#ifndef GLUON_ENGINE_SCENEGRAPHOBJECT_H
#define GLUON_ENGINE_SCENEGRAPHOBJECT_H

#include <QObject>
#include <QList>
#include <core/gluonobject.h>
#include "gluon_engine_export.h"

namespace GluonEngine
{
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
	QString group_name;
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
        SceneGraphObject();
	SceneGraphObject( SceneGraphObject*, QString, GluonCore::GluonObject*, QList<GluonObject*>, QList<SceneGraphObject*> );
        ~SceneGraphObject();
	
	/*
	 * To set the parent of the member object
	 */
	void setParent( SceneGraphObject* );
	/*
	 * To set the group names
	 */
	void setGroupName( QString );
	/*
	 * Add children to object, at this level
	 */
	void addChildren( QList<GluonObject*> );
	/*
	 * Add a group of children
	 */
	void addChildrenGroup( QList<SceneGraphObject*> );
	/*
	 * Called, to set the hash
	 */
	void setHash( long );
	/*
	 * Set the level
	 */
	void setLevel( int );
	/*
	 * Returns the number of children(excluding those under a group
	 */
	int childCount();
	/*
	 * Returns the number of groups of children
	 */
	int groupCount();
    };
}

Q_DECLARE_METATYPE( GluonEngine::SceneGraphObject* )
#endif