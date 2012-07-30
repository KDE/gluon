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
#include <QVariant>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QQuaternion>

using namespace GluonEngine;

SceneGraphObject::SceneGraphObject()
    : p( new SceneGraphObjectPrivate( this ) )
{
}


SceneGraphObject::~SceneGraphObject()
{
    delete p;
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


void SceneGraphObject::setGameObject( GluonEngine::GameObject* object )
{
    p->gameobject = object;
    GluonEngine::TagObject *tags = GluonEngine::Game::instance()->gameProject()->tagObject();
    if( p->gameobject->name().compare( tags->baseName( p->gameobject->name() ) ) == 0 )
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

GluonEngine::GameObject* SceneGraphObject::gameObject()
{
    if( !p->grouphead )
        return p->gameobject;
    return 0;
}

QList< SceneGraphObject* > SceneGraphObject::children()
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

QString SceneGraphObject::groupName()
{
    return p->groupname;
}

int SceneGraphObject::level()
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
        if( level() == object->level() )
        {
            if( groupName().compare( object->groupName() ) != 0 )
                return 1;
        }
        else
            return 2;
    }
    else
    {
        GluonEngine::TagObject *tags = GluonEngine::Game::instance()->gameProject()->tagObject();
        QString name1 = tags->baseName( gameObject()->name() );
        QString name2 = tags->baseName( object->gameObject()->name() );
        if( tags->tags( name1 ).compare( tags->tags( name2 ) ) != 0 )
            return 3;
        else
        {
            if( level() != object->level() )
                return 2;
            else
            {
                for( int i = 0; i < gameObject()->metaObject()->propertyCount(); i++ )
                {
                    QMetaProperty property1 = gameObject()->metaObject()->property( i );
                    int index = object->gameObject()->metaObject()->indexOfProperty( property1.name() );
                    if( index == -1 )
                        return 1;
                    QMetaProperty property2 = object->gameObject()->metaObject()->property( index );
                    if( property1.read( gameObject() ) != property2.read( object->gameObject() ) )
                        return 1;
                }
                QList<QByteArray> dynamicProperties = gameObject()->dynamicPropertyNames();
                foreach( const QByteArray& name, dynamicProperties )
                {
                    if( object->gameObject()->property( name ).isValid() )
                    {
                        if( gameObject()->property( name ) != object->gameObject()->property( name ) )
                            return 1;
                    }
                    else
                        return 1;
                }
                for( int i = 0; i < gameObject()->components().count(); i++ )
                {
                    GluonEngine::Component* componentm = gameObject()->components().at( i );
                    GluonEngine::Component* componento = refObject()->gameObject()->findComponent( componentm->name() );
                    if( componento == 0 )
                        return 1;
                }
            }
        }
    }
    return 0;
}

bool SceneGraphObject::isBase()
{
    return p->isBase;
}

GluonEngine::SceneGraphObject* SceneGraphObject::refObject()
{
    return p->refobject;
}

void SceneGraphObject::setRefObject( GluonEngine::SceneGraphObject* object )
{
    p->refobject = object;
}

void SceneGraphObject::modifyGameObject()
{
    p->modifiedgameobject = new GluonEngine::GameObject();
    p->modifiedgameobject->setName( gameObject()->name() );
    GluonEngine::SceneGraphObject* parentobject = parent();
    if( parentobject != 0 )
    {
        p->modifiedgameobject->setParentGameObject( parentobject->modifiedGameObject() );
        p->modifiedgameobject->parentGameObject()->addChild( p->modifiedgameobject );
    }
    if( diff == 0 )
        return;
    for( int i = 0; i < gameObject()->metaObject()->propertyCount(); i++ )
    {
        QMetaProperty property1 = gameObject()->metaObject()->property( i );
        int index = refObject()->gameObject()->metaObject()->indexOfProperty( property1.name() );
        QMetaProperty property2 = refObject()->gameObject()->metaObject()->property( index );
        if( property2.read( refObject()->gameObject() ) != property1.read( gameObject() ) )
                p->modifiedgameobject->setProperty( property1.name(), property1.read( gameObject() ) );
    }
    foreach( const QByteArray& prop, refObject()->gameObject()->dynamicPropertyNames() )
    {
        if( gameObject()->property( prop ) == QVariant::Invalid )
            gameObject()->setProperty( prop, refObject()->gameObject()->property( prop ) );
    }
    for( int i = 0; i < gameObject()->components().count(); i++ )
    {
        GluonEngine::Component* componentm = gameObject()->components().at( i );
        GluonEngine::Component* componento = refObject()->gameObject()->findComponent( componentm->name() );
        if( componento == 0 )
        {
            GluonEngine::Component* newcomponent = qobject_cast< GluonEngine::Component* >
                                ( GluonCore::GluonObjectFactory::instance()->instantiateObjectByName( componento->metaObject()->className() ) );
            copyComponentProperties( newcomponent, componento );
            p->modifiedgameobject->addComponent( newcomponent );
        }
        else
        {
            int typem = GluonCore::GluonObjectFactory::instance()->objectTypeIDs().value( componentm->name() );
            int typeo = GluonCore::GluonObjectFactory::instance()->objectTypeIDs().value( componento->name() );
            if( typem != typeo )
            {
                GluonEngine::Component* newcomponent = qobject_cast< GluonEngine::Component* >
                                ( GluonCore::GluonObjectFactory::instance()->instantiateObjectByName( componento->metaObject()->className() ) );
                copyComponentProperties( newcomponent, componento );
                p->modifiedgameobject->addComponent( newcomponent );
            }
        }
    }
}

GluonEngine::GameObject* SceneGraphObject::modifiedGameObject()
{
    return p->modifiedgameobject;
}

GluonEngine::SceneGraphObject* SceneGraphObject::parent()
{
    if( p->parent == 0 )
        return 0;
    if( p->parent->isGroupHead() )
        return p->parent->parent();
    else
        return p->parent;
}

void SceneGraphObject::buildGameObject()
{
    for( int i = 0; i < refObject()->gameObject()->metaObject()->propertyCount(); i++ )
    {
        QMetaProperty property = refObject()->gameObject()->metaObject()->property( i );
        int index = gameObject()->metaObject()->indexOfProperty( property.name() );
        QMetaProperty propertym = gameObject()->metaObject()->property( index );
        if( isIdentity( propertym.read( gameObject() ) ) )
            gameObject()->setProperty( property.name(), property.read( refObject()->gameObject() ) );
    }
    foreach( const QByteArray& prop, refObject()->gameObject()->dynamicPropertyNames() )
    {
        if( gameObject()->property( prop ) == QVariant::Invalid )
            gameObject()->setProperty( prop, refObject()->gameObject()->property( prop ) );
        else
        {
            if( isIdentity( gameObject()->property( prop ) ) )
                gameObject()->setProperty( prop, refObject()->gameObject()->property( prop ) );
        }
    }
    for( int i = 0; i < refObject()->gameObject()->components().count(); i++ )
    {
        GluonEngine::Component* componento = refObject()->gameObject()->components().at( i );
        GluonEngine::Component* newcomponent = qobject_cast< GluonEngine::Component* >
                                ( GluonCore::GluonObjectFactory::instance()->instantiateObjectByName( componento->metaObject()->className() ) );
        copyComponentProperties( newcomponent, componento );
        gameObject()->addComponent( newcomponent );
    }
}

bool SceneGraphObject::isIdentity( QVariant var )
{
    switch( var.type() )
    {
        case QVariant::Bool:
        {
            return true;
            break;
        }
        case QVariant::Int:
        {
            if( var.toInt() == 0 )
                return true;
            break;
        }
        case QVariant::UInt:
        {
            if( var.toUInt() == 0 )
                return true;
            break;
        }
        case QVariant::LongLong:
        {
            if( var.toLongLong() == 0 )
                return true;
            break;
        }
        case 137: //float
        case QVariant::Double:
        {
            if( var.toFloat() == float( 0 ) )
                return true;
            break;
        }
        case QVariant::String:
        {
            if( var.toString().isEmpty() || var.toString().isNull() )
                return true;
            break;
        }
        case QVariant::Url:
        {
            if( var.toUrl().isEmpty() )
                return true;
            break;
        }
        case QVariant::Vector2D:
        {
            QVector2D v = var.value<QVector2D>();
            if( v.isNull() )
                return true;
            break;
        }
        case QVariant::Vector3D:
        {
            QVector3D v = var.value<QVector3D>();
            if( v.isNull() )
                return true;
            break;
        }
        case QVariant::Vector4D:
        {
            QVector4D v = var.value<QVector4D>();
            if( v.isNull() )
                return true;
            break;
        }
        case QVariant::Quaternion:
        {
            QQuaternion v = var.value< QQuaternion >();
            if( v.isNull() || v.isIdentity() )
                return true;
            break;
        }
        case QVariant::SizeF:
        {
            if( var.toSizeF().isNull() )
                return true;
            break;
        }
        case QVariant::List:
        {
            if( var.toList().isEmpty() )
                return true;
            break;
        }
        default:
            return false;
    }
    return false;
}

void SceneGraphObject::copyComponentProperties( GluonEngine::Component* copy, GluonEngine::Component* original )
{
    for( int i = 0; i < original->metaObject()->propertyCount(); i++ )
    {
        QMetaProperty property = original->metaObject()->property( i );
        copy->setProperty( property.name(), property.read( original ) );
    }
    foreach( const QByteArray& prop, original->dynamicPropertyNames() )
    {
        copy->setProperty( prop, original->property( prop ) );
    }
}

#include "scenegraphobject.moc"