/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "gameobjectprivate.h"


using namespace GluonEngine;

GameObjectPrivate::GameObjectPrivate()
    : enabled( true )
    , position( QVector3D() )
    , scale( QVector3D( 1, 1, 1 ) )
    , orientation( QQuaternion( 1, 0, 0, 0 ) )
    , transform( QMatrix4x4() )
    , transformInvalidated( true )
    , parentGameObject( 0 )
{
}

GameObjectPrivate::GameObjectPrivate( const GameObjectPrivate& other )
    : description( other.description )
    , enabled( other.enabled )
    , position( other.position )
    , scale( other.scale )
    , orientation( other.orientation )
    , transform( QMatrix4x4() )
    , transformInvalidated( true )
    , parentGameObject( other.parentGameObject )
{
}

GameObjectPrivate::~GameObjectPrivate()
{
}
