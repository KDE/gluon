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

#include "scenegraphobject.h"
#include "scenegraphobjectprivate.h"

#include "game.h"
#include "gameproject.h"
#include "tagobject.h"
#include "component.h"

#include <core/gluonobject.h>
#include <core/gluonobjectfactory.h>

#include <QMetaProperty>
#include <QDebug>

using namespace GluonEngine;

SceneGraphObject::SceneGraphObject()
    : p( new SceneGraphObjectPrivate( this ) )
{
}


SceneGraphObject::~SceneGraphObject()
{
}

void SceneGraphObject::setParent( SceneGraphObject* parent )
{
    p->parent = parent;
}

void SceneGraphObject::addChildren( QList< SceneGraphObject* > children )
{
    p->children.append( children );
}

void SceneGraphObject::addChild( SceneGraphObject* child )
{
    p->children.append( child );
}


void SceneGraphObject::setMember( GluonEngine::GameObject* object )
{
    p->member = object;
    GluonEngine::TagObject *tags = GluonEngine::Game::instance()->gameProject()->getTagObject();
    if( p->member->name().compare( tags->getBaseName( p->member->name() ) ) == 0 )
        p->isBase = true;
    else
        p->isBase = false;
}

void SceneGraphObject::setGroupName( QString groupname )
{
    p->groupname = groupname;
}


void SceneGraphObject::setLevel( int level )
{
    p->level = level;
}

int SceneGraphObject::childCount()
{
    return p->children.length();
}

GluonEngine::GameObject* SceneGraphObject::getMember()
{
    if( !p->grouphead )
        return p->member;
    return 0;
}

QList< SceneGraphObject* > SceneGraphObject::getChildren()
{
    return p->children;
}

void SceneGraphObject::setGroupHead( bool value )
{
    p->grouphead = value;
}

bool GluonEngine::SceneGraphObject::isGroupHead()
{
    return p->grouphead;
}

QString SceneGraphObject::getGroupName()
{
    return p->groupname;
}

int SceneGraphObject::getLevel()
{
    return p->level;
}

int SceneGraphObject::compare( SceneGraphObject* object )
{
    /*
     * 0 = Perfect match
     * 1 = Levels, type match
     * 2 = Type match
     * 3 = Mismatch
     */
    if( isGroupHead() ^ object->isGroupHead() )
        return 3;
    if( isGroupHead() )
    {
        if( getLevel() == object->getLevel() )
        {
            if( getGroupName().compare( object->getGroupName() ) != 0 )
                return 1;
        }
        else
            return 2;
    }
    else
    {
        GluonEngine::TagObject *tags = GluonEngine::Game::instance()->gameProject()->getTagObject();
        QString name1 = tags->getBaseName( getMember()->name() );
        QString name2 = tags->getBaseName( object->getMember()->name() );
        if( tags->getTags( name1 ).compare( tags->getTags( name2 ) ) != 0 )
            return 3;
        else
        {
            if( getLevel() != object->getLevel() )
                return 2;
            else
            {
                for( int i = 0; i < getMember()->metaObject()->propertyCount(); i++ )
                {
                    QMetaProperty property1 = getMember()->metaObject()->property( i );
                    int index = object->getMember()->metaObject()->indexOfProperty( property1.name() );
                    if( index == -1 )
                        return 1;
                    QMetaProperty property2 = object->getMember()->metaObject()->property( index );
                    if( property1.read( getMember() ) != property2.read( object->getMember() ) )
                        return 1;
                }
                QList<QByteArray> dynamicProperties = getMember()->dynamicPropertyNames();
                foreach( const QByteArray& name, dynamicProperties )
                {
                    if( object->getMember()->property( name ).isValid() )
                    {
                        if( getMember()->property( name ).isValid() != object->getMember()->property( name ).isValid() )
                            return 1;
                    }
                    else
                        return 1;
                }
                for( int i = 0; i < getMember()->components().count(); i++ )
                {
                    GluonEngine::Component* componentm = getMember()->components().at( i );
                    GluonEngine::Component* componento = getRefObject()->getMember()->findComponent( componentm->fullyQualifiedName().split("/").last() );
                    if( componento == 0 )
                        return 1;
                }
            }
        }
    }
    return 0;
}

bool SceneGraphObject::checkIsBase()
{
    return p->isBase;
}

GluonEngine::SceneGraphObject* SceneGraphObject::getRefObject()
{
    return p->refobject;
}

void SceneGraphObject::setRefObject( GluonEngine::SceneGraphObject* object )
{
    p->refobject = object;
}

void SceneGraphObject::modifyMember()
{
    p->modifiedmember = new GluonEngine::GameObject();
    p->modifiedmember->setName( getMember()->name() );
    GluonEngine::SceneGraphObject* parentobject = getParent();
    if( parentobject != 0 )
    {
        p->modifiedmember->setParentGameObject( parentobject->getModifiedMember() );
        p->modifiedmember->parentGameObject()->addChild( p->modifiedmember );
    }
    if( diff == 0 )
        return;
    for( int i = 0; i < getMember()->metaObject()->propertyCount(); i++ )
    {
        QMetaProperty property1 = getMember()->metaObject()->property( i );
        int index = getRefObject()->getMember()->metaObject()->indexOfProperty( property1.name() );
        if( index == -1 )
            p->modifiedmember->setProperty( property1.name(), property1.read( getMember() ) );
        else
        {
            QMetaProperty property2 = getRefObject()->getMember()->metaObject()->property( index );
            if( property2.read( getRefObject()->getMember() ) != property1.read( getMember() ) )
                p->modifiedmember->setProperty( property1.name(), property1.read( getMember() ) );
        }
    }
    for( int i = 0; i < getMember()->components().count(); i++ )
    {
        GluonEngine::Component* componentm = getMember()->components().at( i );
        GluonEngine::Component* componento = getRefObject()->getMember()->findComponent( componentm->fullyQualifiedName().split("/").last() );
        if( componento == 0 )
            p->modifiedmember->addComponent( componentm );
        else
        {
            int typem = GluonCore::GluonObjectFactory::instance()->objectTypeIDs().value( componentm->fullyQualifiedName() );
            int typeo = GluonCore::GluonObjectFactory::instance()->objectTypeIDs().value( componento->fullyQualifiedName() );
            if( typem != typeo )
                p->modifiedmember->addComponent( componentm );
        }
    }
}

GluonEngine::GameObject* SceneGraphObject::getModifiedMember()
{
    return p->modifiedmember;
}

GluonEngine::SceneGraphObject* SceneGraphObject::getParent()
{
    if( p->parent == 0 )
        return 0;
    if( p->parent->isGroupHead() )
        return p->parent->getParent();
    else
        return p->parent;
}


#include "scenegraphobject.moc"