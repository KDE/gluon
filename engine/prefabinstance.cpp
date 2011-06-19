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

#include "prefabinstance.h"
#include "component.h"
#include <QMetaProperty>
#include "prefabinstancechild.h"

REGISTER_OBJECTTYPE( GluonEngine, PrefabInstance )

using namespace GluonEngine;

class PrefabInstance::Private
{
    public:
        Private()
            : prefabLink( 0 )
        {
        }

        Prefab* prefabLink;
};

PrefabInstance::PrefabInstance( QObject* parent )
    : d( new Private )
{

}

PrefabInstance::PrefabInstance( const PrefabInstance& other )
    : d( new Private() )
{
    *d = *other.d;
}

PrefabInstance::~PrefabInstance()
{
    if( d->prefabLink )
        d->prefabLink->removeInstance( this );

    delete( d );
}

Prefab* PrefabInstance::prefabLink() const
{
    return d->prefabLink;
}

void PrefabInstance::setPrefabLink( Prefab* newPrefab )
{
    // First, set up the new prefab linkage
    if( d->prefabLink )
        d->prefabLink->removeInstance( this );
    d->prefabLink = newPrefab;
    if( d->prefabLink )
    {
        d->prefabLink->addInstance( this );

        // Then (if the new prefab is valid, and we are not loading the containing scene from disk)
        // remove the old children, and clone from the new prefab
        if( isInitialized() )
        {
            rebuildInstance();
        }
    }
}

void PrefabInstance::revertChanges()
{
    rebuildInstance();
}

void PrefabInstance::storeChanges() const
{
    // Tell the Prefab to read information from this PrefabInstance
    prefabLink()->updateFromInstance(this);
}

void PrefabInstance::rebuildInstance()
{
    // Clear all children out
    qDeleteAll(children());

    Prefab::cloneObjectProperties(d->prefabLink->gameObject(), this);

    // Clone all the GameObject children
    const int childCount = d->prefabLink->gameObject()->childCount();
    if( childCount > 0 )
    {
        for( int i = 0; i < childCount; ++i )
        {
            GameObject* childGobj = d->prefabLink->gameObject()->childGameObject(i);
            // Clone this GameObject as a PrefabInstanceChild...
            PrefabInstanceChild* newChild = new PrefabInstanceChild(this);
            newChild->cloneFromGameObject(childGobj);
        }
    }

    // Clone all the Components
    foreach( Component* cmp, d->prefabLink->gameObject()->components() )
    {
        Prefab::cloneObjectProperties( cmp, cmp->clone( this ) );
    }
}

void PrefabInstance::setName(const QString& newName)
{
    Q_UNUSED(newName);
}

void PrefabInstance::addChild(GluonCore::GluonObject* child)
{
    connect(child, SIGNAL(nameChanged(const QString&, const QString&)), this, SLOT(childNameChanged(const QString&, const QString&)));
    GluonEngine::GameObject::addChild(child);
}

void PrefabInstance::addChildAt(GluonCore::GluonObject* child, int position)
{
    connect(child, SIGNAL(nameChanged(const QString&, const QString&)), this, SLOT(childNameChanged(const QString&, const QString&)));
    GluonCore::GluonObject::addChildAt(child, position);
}

bool PrefabInstance::removeChild(GluonCore::GluonObject* child)
{
    disconnect(child, SIGNAL(nameChanged(const QString&, const QString&)), this, SLOT(childNameChanged(const QString&, const QString&)));
    return GluonEngine::GameObject::removeChild(child);
}

void PrefabInstance::addComponent(Component* addThis)
{
    connect(addThis, SIGNAL(nameChanged(const QString&, const QString&)), this, SLOT(childNameChanged(const QString&, const QString&)));
    GluonEngine::GameObject::addComponent(addThis);
}

bool PrefabInstance::removeComponent(Component* removeThis)
{
    connect(removeThis, SIGNAL(nameChanged(const QString&, const QString&)), this, SLOT(childNameChanged(const QString&, const QString&)));
    return GluonEngine::GameObject::removeComponent(removeThis);
}

void PrefabInstance::childNameChanged(const QString& oldName, const QString& newName)
{
    // This ensures that children (in particular this means Components) don't get renamed in instances
    GluonCore::GluonObject* from = qobject_cast<GluonCore::GluonObject*>( sender() );
    if(from && oldName != newName)
        from->setName(oldName);
}

#include "prefabinstance.moc"
