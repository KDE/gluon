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

REGISTER_OBJECTTYPE( GluonEngine, PrefabInstance )

using namespace GluonEngine;

class PrefabInstance::Private
{
public:
    Private()
        : prefabLink(0)
    {
    }
    
    Prefab* prefabLink;
};

PrefabInstance::PrefabInstance()
    : d( new Private )
{

}

PrefabInstance::PrefabInstance(const PrefabInstance& other)
    : d( other.d )
{

}

PrefabInstance::~PrefabInstance()
{
    if(d->prefabLink)
        d->prefabLink->removeInstance(this);

    delete(d);
}

Prefab* PrefabInstance::prefabLink() const
{
    return d->prefabLink;
}

void PrefabInstance::setPrefabLink(Prefab* newPrefab)
{
    if(d->prefabLink)
        d->prefabLink->removeInstance(this);
    d->prefabLink = newPrefab;
    d->prefabLink->addInstance(this);
}

#include "prefabinstance.moc"
