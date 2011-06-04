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


#include "prefabprivate.h"

#include "engine/gameobject.h"

using namespace GluonEngine;

PrefabPrivate::PrefabPrivate()
    : gameObject( 0 )
    , preCacheSize( 0 )
    , additionalCacheSize( 0 )
{
}

PrefabPrivate::PrefabPrivate( const PrefabPrivate& other )
    : instances( other.instances )
    , gameObject( other.gameObject )
    , preCacheSize( 0 )
    , additionalCacheSize( 0 )
{
}

PrefabPrivate::~PrefabPrivate()
{
    delete( gameObject );
}

void PrefabPrivate::updateChildrenFromOther(QObject* updateThis, const QObject* updateFrom)
{
    // Go through all children recursively on "updateFrom" and...
    foreach(QObject* child, updateFrom->children())
    {
        
        // ...remove all removed objects on stored GameObject (ensure it has not just been moved)
        //    - remove object in same position on all linked instances
        // ...add all new objects to stored Gamebject (ensure it is not just a moved object)
        //    - add object in same position on all linked instances
        //    - reclone properties
    }
}
