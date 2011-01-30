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

REGISTER_OBJECTTYPE( GluonEngine, Prefab )

using namespace GluonEngine;

Prefab::Prefab( QObject* parent )
    : Asset( parent )
    , d( new PrefabPrivate )
{
}

Prefab::Prefab( const Prefab& other, QObject* parent )
    : Asset( parent )
    , d( other.d )
{
}

Prefab::~Prefab()
{
    delete(d);
}

PrefabInstance* Prefab::createInstance(GameObject* attachTo) const
{
    PrefabInstance* instance = createInstance();
    if(instance)
    {
        attachTo->addChild(instance);
    }
    return instance;
}

PrefabInstance* Prefab::createInstance() const
{
    PrefabInstance* instance = 0;
    if(d->gameObject)
    {
        instance = new PrefabInstance();
        instance->setPrefabLink(this);
    }
    return instance;
}

const QList< PrefabInstance* > Prefab::instances() const
{
    return d->instances;
}

bool Prefab::addInstance(const GluonEngine::PrefabInstance* addThis)
{
    if(addThis && !d->instances.contains(addThis))
    {
        d->instances.append(addThis);
        return true;
    }
    return false;
}

bool Prefab::removeInstance(const GluonEngine::PrefabInstance* removeThis)
{
    return d->instances.removeOne(removeThis);
}

GameObject* Prefab::gameObject() const
{
    return 0;
}

void Prefab::setGameObject(GameObject* newGameObject)
{

}

#include "prefab.moc"
