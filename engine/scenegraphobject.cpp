#include "scenegraphobject.h"

#include <core/gluonobject.h>

using namespace GluonEngine;

SceneGraphObject::SceneGraphObject()
{
    this->parent = 0;
    this->groupname = "";
    this->member = new GluonCore::GluonObject( 0 );
    this->children.clear();
    this->childrengroup.clear();
    this->level = 0;
}


SceneGraphObject::~SceneGraphObject()
{
}

void SceneGraphObject::setParent( SceneGraphObject* parent )
{
    this->parent = parent;
}

void SceneGraphObject::addChildren( QList< SceneGraphObject* > children )
{
    this->children.append( children );
}

void SceneGraphObject::addChildrenGroup( QList< SceneGraphObject* > childrengroup )
{
    this->childrengroup.append( childrengroup );
}

void SceneGraphObject::setMember( GluonEngine::GameObject* object )
{
    this->member = object;
}

void SceneGraphObject::setHash( long int hash )
{
    this->hash = hash;
}

void SceneGraphObject::setGroupName( QString groupname )
{
    this->groupname = groupname;
}


void SceneGraphObject::setLevel( int level )
{
    this->level = level;
}

int SceneGraphObject::childCount()
{
    return this->children.length() + this->childrengroup.length();
}

int SceneGraphObject::groupCount()
{
    return this->childrengroup.length();
}

GluonCore::GluonObject* SceneGraphObject::getMember()
{
    return this->member;
}

QList< SceneGraphObject* > SceneGraphObject::getChildren()
{
    return this->children;
}


#include "scenegraphobject.moc"