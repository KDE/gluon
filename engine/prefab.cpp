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

PrefabInstance* Prefab::createInstance() const
{

}

GameObject* Prefab::gameObject() const
{

}

void Prefab::setGameObject(GameObject* newGameObject)
{

}

#include "prefab.moc"
