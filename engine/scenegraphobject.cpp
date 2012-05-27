#include "scenegraphobject.h"

#include <core/gluonobject.h>

using namespace GluonEngine;

REGISTER_OBJECTTYPE( GluonEngine, SceneGraphObject )

SceneGraphObject::SceneGraphObject()
{
    this->parent = 0;
    this->group_name = "";
    this->member = new GluonCore::GluonObject( 0 );
    this->children.clear();
    this->childrenGroup.clear();
}

SceneGraphObject::SceneGraphObject( SceneGraphObject* parent, QString group_name, GluonCore::GluonObject* member, 
				   QList< GluonCore::GluonObject* > children, QList< SceneGraphObject* > childrenGroup )
{
    this->parent = parent;
    this->group_name = group_name;
    this->member = member;
    this->children = children;
    this->childrenGroup = childrenGroup;
}

SceneGraphObject::~SceneGraphObject()
{
}

void SceneGraphObject::setGroupName( QString group_name )
{
    this->group_name = group_name;
}

void SceneGraphObject::setParent( SceneGraphObject* parent )
{
    this->parent = parent;
}

void SceneGraphObject::addChildren( QList< GluonCore::GluonObject* > children )
{
    this->children.append( children );
}

void SceneGraphObject::addChildrenGroup( QList< SceneGraphObject* > childrenGroup )
{
    this->childrenGroup.append( childrenGroup );
}

void SceneGraphObject::setHash( long int hash )
{
    this->hash = hash;
}

int SceneGraphObject::childCount()
{
    return this->children.length();
}

int SceneGraphObject::groupCount()
{
    return this->childrenGroup.length();
}

#include "scenegraphobject.moc"