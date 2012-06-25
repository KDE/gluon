#include "scenegraphobject.h"

#include "game.h"
#include "gameproject.h"
#include "tagobject.h"

#include <core/gluonobject.h>
#include <QMetaProperty>

using namespace GluonEngine;

SceneGraphObject::SceneGraphObject()
{
    this->parent = 0;
    this->groupname = QString( "" );
    this->member = new GluonEngine::GameObject( 0 );
    this->children.clear();
    this->childrengroup.clear();
    this->level = 0;
    this->grouphead = false;
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

void SceneGraphObject::addChild( SceneGraphObject* child )
{
    this->children.append( child );
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

GluonEngine::GameObject* SceneGraphObject::getMember()
{
    if( !this->grouphead )
        return this->member;
    return 0;
}

QList< SceneGraphObject* > SceneGraphObject::getChildren()
{
    return this->children;
}

void SceneGraphObject::setGroupHead( bool value )
{
    this->grouphead = value;
}

bool GluonEngine::SceneGraphObject::isGroupHead()
{
    return this->grouphead;
}

QString SceneGraphObject::getGroupName()
{
    return this->groupname;
}

int SceneGraphObject::getLevel()
{
    return this->level;
}

int SceneGraphObject::compare( SceneGraphObject* object )
{
    /*
     * 0 = Perfect match
     * 1 = Levels, type match
     * 2 = Type match
     * 3 = Mismatch
     */
    if( this->isGroupHead() ^ object->isGroupHead() )
        return 3;
    if( this->isGroupHead() )
    {
        if( this->getLevel() == object->getLevel() )
        {
            if( this->getGroupName().compare( object->getGroupName() ) != 0 )
                return 1;
        }
        else
            return 2;
    }
    else
    {
        GluonEngine::TagObject *tags = GluonEngine::Game::instance()->gameProject()->getTagObject();
        QString name1 = tags->getBaseName( this->getMember()->name() );
        QString name2 = tags->getBaseName( object->getMember()->name() );
        if( tags->getTags( name1 ).compare( tags->getTags( name2 ) ) != 0 )
            return 3;
        else
        {
            if( this->getLevel() != object->getLevel() )
                return 2;
            else
                for( int i = 0; i < this->getMember()->metaObject()->propertyCount(); i++ )
                {
                    QMetaProperty property = this->getMember()->metaObject()->property( i );
                    if( property.read( object->getMember() ) != property.read( this->getMember() ) )
                        return 1;
                }
        }
    }
    return 0;
}



#include "scenegraphobject.moc"