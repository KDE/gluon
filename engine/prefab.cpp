/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

#include "prefab.h"
#include "prefabprivate.h"
#include "prefabinstance.h"
#include <core/gdlhandler.h>

#include <QtCore/QMetaProperty>

REGISTER_OBJECTTYPE( GluonEngine, Prefab )

using namespace GluonEngine;

Prefab::Prefab( QObject* parent )
    : Asset( parent )
    , d( new PrefabPrivate )
{
}

Prefab::Prefab( const Prefab& other, QObject* parent )
    : Asset( parent )
    , d( new PrefabPrivate() )
{
    *d = *other.d;
}

Prefab::~Prefab()
{
    delete( d );
}

QString Prefab::contentsToGDL()
{
    return GluonCore::GDLHandler::instance()->toGDL( gameObject() );
}

PrefabInstance* Prefab::createInstance( GameObject* attachTo )
{
    PrefabInstance* instance = createInstance();
    if( instance )
    {
        attachTo->addChild( instance );
    }
    return instance;
}

PrefabInstance* Prefab::createInstance()
{
    PrefabInstance* instance = 0;
    if( d->gameObject )
    {
        instance = new PrefabInstance();
        instance->initialize();
        instance->setPrefabLink( this );
    }
    return instance;
}

const QList< PrefabInstance* > Prefab::instances() const
{
    return d->instances;
}

bool Prefab::addInstance( GluonEngine::PrefabInstance* addThis )
{
    if( addThis && !d->instances.contains( addThis ) )
    {
        d->instances.append( addThis );
        return true;
    }
    return false;
}

bool Prefab::removeInstance( GluonEngine::PrefabInstance* removeThis )
{
    return d->instances.removeOne( removeThis );
}

GameObject* Prefab::gameObject() const
{
    return d->gameObject;
}

void Prefab::setGameObject( GameObject* newGameObject )
{
    // Grab the parent of the GameObject...
    GameObject* oldParent = newGameObject->parentGameObject();
    int position = oldParent->children().indexOf(newGameObject);

    // Remove GameObject from parent, reparent to this
    oldParent->removeChild(newGameObject);
    addChild(newGameObject);

    // Replace the GameObject in-line with a prefab instance
    d->gameObject = newGameObject;
    oldParent->addChildAt(createInstance(), position);

    // Re-create all the instances
    foreach(PrefabInstance* instance, d->instances )
    {
        instance->rebuildInstance();
    }
}

int Prefab::additionalCacheSize() const
{
    return d->additionalCacheSize;
}

void Prefab::setAdditionalCacheSize(int newAdditionalCacheSize)
{
    d->additionalCacheSize = newAdditionalCacheSize;
}

int Prefab::preCacheSize() const
{
    return d->preCacheSize;
}

void Prefab::setPreCacheSize(int newPreCacheSize)
{
    d->preCacheSize = newPreCacheSize;
}

void Prefab::updateFromInstance(const GluonEngine::PrefabInstance* updateFrom)
{
    // TODO implement :P
    d->updateChildrenFromOther(d->gameObject, updateFrom);
}

void Prefab::cloneObjectProperties(const QObject* cloneFrom, QObject* setPropertiesOn)
{
    // Clear out all the existing dynamic properties (to ensure we're actually clean)
    QList<QByteArray> propertyNames = setPropertiesOn->dynamicPropertyNames();
    foreach( const QByteArray & propName, propertyNames )
    {
        setPropertiesOn->setProperty( propName, QVariant() );
    }

    // Clone the property values from the passed GameObject
    propertyNames = cloneFrom->dynamicPropertyNames();
    foreach( const QByteArray & propName, propertyNames )
    {
        setPropertiesOn->setProperty( propName, cloneFrom->property( propName ) );
    }

    const QMetaObject* metaobject = cloneFrom->metaObject();
    int count = metaobject->propertyCount();
    for( int i = 0; i < count; ++i )
    {
        QMetaProperty metaproperty = metaobject->property( i );
        const QString theName( metaproperty.name() );
        if( theName == "objectName" || !metaproperty.isWritable() )
            continue;
        setPropertiesOn->setProperty( theName.toUtf8(), cloneFrom->property( theName.toUtf8() ) );
    }
}

#include "prefab.moc"
