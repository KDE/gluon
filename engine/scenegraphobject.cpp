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
{
    this->parent = 0;
    this->groupname = QString( "" );
    this->member = new GluonEngine::GameObject( 0 );
    this->children.clear();
    this->childrengroup.clear();
    this->level = 0;
    this->grouphead = false;
    this->diff = 0;
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
    GluonEngine::TagObject *tags = GluonEngine::Game::instance()->gameProject()->getTagObject();
    if( this->member->name().compare( tags->getBaseName( this->member->name() ) ) == 0 )
        this->isBase = true;
    else
        this->isBase = false;
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
                    int typem = GluonCore::GluonObjectFactory::instance()->objectTypeIDs().value( componentm->metaObject()->className() );
                    GluonEngine::Component* componento = object->getMember()->findComponentByType( typem );
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
    return this->isBase;
}

GluonEngine::SceneGraphObject* SceneGraphObject::getRefObject()
{
    return this->refObject;
}

void SceneGraphObject::setRefObject( GluonEngine::SceneGraphObject* object )
{
    this->refObject = object;
}

void SceneGraphObject::modifyMember()
{
    this->modifiedMember = new GluonEngine::GameObject();
    this->modifiedMember->setName( getMember()->name() );
    GluonEngine::SceneGraphObject* parentobject = getParent();
    if( parentobject != 0 )
    {
        this->modifiedMember->setParentGameObject( parentobject->getModifiedMember() );
        this->modifiedMember->parentGameObject()->addChild( this->modifiedMember );
    }
    if( this->diff == 0 )
        return;
    for( int i = 0; i < getMember()->metaObject()->propertyCount(); i++ )
    {
        QMetaProperty property1 = getMember()->metaObject()->property( i );
        int index = getRefObject()->getMember()->metaObject()->indexOfProperty( property1.name() );
        if( index == -1 )
            this->modifiedMember->setProperty( property1.name(), property1.read( getMember() ) );
        else
        {
            QMetaProperty property2 = getRefObject()->getMember()->metaObject()->property( index );
            if( property2.read( getRefObject()->getMember() ) != property1.read( getMember() ) )
                this->modifiedMember->setProperty( property1.name(), property1.read( getMember() ) );
        }
    }
    for( int i = 0; i < getMember()->components().count(); i++ )
    {
        GluonEngine::Component* componentm = getMember()->components().at( i );
        GluonEngine::Component* componento = getRefObject()->getMember()->findComponent( componentm->fullyQualifiedName().split("/").last() );
        if( componento == 0 )
            return;
        else
            qDebug() << componento->fullyQualifiedName();
    }
}

GluonEngine::GameObject* SceneGraphObject::getModifiedMember()
{
    return this->modifiedMember;
}

GluonEngine::SceneGraphObject* SceneGraphObject::getParent()
{
    if( this->parent == 0 )
        return 0;
    if( this->parent->isGroupHead() )
        return this->parent->getParent();
    else
        return this->parent;
}


#include "scenegraphobject.moc"