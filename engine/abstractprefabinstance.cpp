/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Felix Rohrbach <fxrh@gmx.de>
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

#include "abstractprefabinstance.h"

#include "component.h"

using namespace GluonEngine;

REGISTER_OBJECTTYPE( GluonEngine, AbstractPrefabInstance )

class AbstractPrefabInstance::Private
{
    public:
        Private() : instantiationCompleted( false ), gameObjectChanged( false ) {}
        Private( const Private& other ) : instantiationCompleted( other.instantiationCompleted ) {}
        ~Private() {}

        bool instantiationCompleted;
        bool gameObjectChanged;
};

AbstractPrefabInstance::AbstractPrefabInstance( QObject* parent )
    : GameObject( parent )
    , d( new Private )
{

}

AbstractPrefabInstance::~AbstractPrefabInstance()
{
    delete d;
}

void AbstractPrefabInstance::addChild(GameObject* child)
{
    connect(child, SIGNAL(nameChanged(QString,QString)), this, SLOT(childNameChanged(QString,QString)));
    AbstractPrefabInstance* instance = qobject_cast<AbstractPrefabInstance*>( child );
    if( instance )
    {
        connect( instance, SIGNAL(instanceChanged()), this, SLOT(gameObjectChanged()) );
        connect( this, SIGNAL(instanceReverted()), instance, SLOT(parentReverted()) );
        connect( this, SIGNAL(instanceStored()), instance, SLOT(parentStored()) );
    }
    GluonEngine::GameObject::addChild(child);
}

void AbstractPrefabInstance::addChild(GluonCore::GluonObject* child)
{
    connect(child, SIGNAL(nameChanged(QString,QString)), this, SLOT(childNameChanged(QString,QString)));
    AbstractPrefabInstance* instance = qobject_cast<AbstractPrefabInstance*>( child );
    if( instance )
    {
        connect( instance, SIGNAL(instanceChanged()), this, SLOT(gameObjectChanged()) );
        connect( this, SIGNAL(instanceReverted()), instance, SLOT(parentReverted()) );
        connect( this, SIGNAL(instanceStored()), instance, SLOT(parentStored()) );
    }
    GluonEngine::GameObject::addChild(child);
}

void AbstractPrefabInstance::addChildAt(GluonCore::GluonObject* child, int position)
{
    connect(child, SIGNAL(nameChanged(QString,QString)), this, SLOT(childNameChanged(QString,QString)));
    AbstractPrefabInstance* instance = qobject_cast<AbstractPrefabInstance*>( child );
    if( instance )
    {
        connect( instance, SIGNAL(instanceChanged()), this, SLOT(gameObjectChanged()) );
        connect( this, SIGNAL(instanceReverted()), instance, SLOT(parentReverted()) );
        connect( this, SIGNAL(instanceStored()), instance, SLOT(parentStored()) );
    }
    GluonCore::GluonObject::addChildAt(child, position);
}

bool AbstractPrefabInstance::removeChild(GameObject* child)
{
    disconnect(child, SIGNAL(nameChanged(QString,QString)), this, SLOT(childNameChanged(QString,QString)));
    AbstractPrefabInstance* instance = qobject_cast<AbstractPrefabInstance*>( child );
    if( instance )
    {
        disconnect( instance, SIGNAL(instanceChanged()), this, SLOT(gameObjectChanged()) );
        disconnect( this, SIGNAL(instanceReverted()), instance, SLOT(parentReverted()) );
        disconnect( this, SIGNAL(instanceStored()), instance, SLOT(parentStored()) );
    }
    return GluonEngine::GameObject::removeChild(child);
}

bool AbstractPrefabInstance::removeChild(GluonCore::GluonObject* child)
{
    disconnect(child, SIGNAL(nameChanged(QString,QString)), this, SLOT(childNameChanged(QString,QString)));
    AbstractPrefabInstance* instance = qobject_cast<AbstractPrefabInstance*>( child );
    if( instance )
    {
        disconnect( instance, SIGNAL(instanceChanged()), this, SLOT(gameObjectChanged()) );
        disconnect( this, SIGNAL(instanceReverted()), instance, SLOT(parentReverted()) );
        disconnect( this, SIGNAL(instanceStored()), instance, SLOT(parentStored()) );
    }
    return GluonEngine::GameObject::removeChild(child);
}

void AbstractPrefabInstance::addComponent(Component* addThis)
{
    connect(addThis, SIGNAL(nameChanged(QString,QString)), this, SLOT(childNameChanged(QString,QString)));
    GluonEngine::GameObject::addComponent(addThis);
}

bool AbstractPrefabInstance::removeComponent(Component* removeThis)
{
    connect(removeThis, SIGNAL(nameChanged(QString,QString)), this, SLOT(childNameChanged(QString,QString)));
    return GluonEngine::GameObject::removeComponent(removeThis);
}

void AbstractPrefabInstance::storeChanges()
{
    d->gameObjectChanged = false;
    emit instanceStored();
}

void AbstractPrefabInstance::revertChanges()
{
    d->gameObjectChanged = false;
    emit instanceReverted();
}

void AbstractPrefabInstance::gameObjectChanged()
{
    d->gameObjectChanged = true;
    emit instanceChanged();
}

bool AbstractPrefabInstance::hasGameObjectChanged() const
{
    return d->gameObjectChanged;
}

void AbstractPrefabInstance::childNameChanged(const QString& oldName, const QString& newName)
{
    if(d->instantiationCompleted == false)
        return;
    if(oldName == newName)
        return;
    // TODO: Currently we can't say if the sender is already tracked by a prefab or if it's a new object
//     // This ensures that children (in particular this means Components) don't get renamed in instances
//     GluonCore::GluonObject* from = qobject_cast<GluonCore::GluonObject*>( sender() );
//     if(from)
//         from->setName(oldName);
}

void AbstractPrefabInstance::parentReverted()
{
    d->gameObjectChanged = false;
    emit instanceReverted();
}

void AbstractPrefabInstance::parentStored()
{
    d->gameObjectChanged = false;
    emit instanceStored();
}

bool AbstractPrefabInstance::isInstantiationCompleted() const
{
    return d->instantiationCompleted;
}

void AbstractPrefabInstance::setInstantiationCompleted(bool completed)
{
    d->instantiationCompleted = completed;
}

 
