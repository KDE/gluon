/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2012 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "entity.h"

#include "mesh.h"
#include "materialinstance.h"
#include "manager.h"
#include "world.h"

#include <QtGui/QMatrix4x4>
#include "camera.h"
#include "frustrum.h"

using namespace GluonGraphics;

REGISTER_OBJECTTYPE( GluonGraphics, Entity );

class Entity::Private
{
    public:
        Private() : world( 0 ), mesh( 0 ), materialInstance( 0 ) { }

        World* world;
        QMatrix4x4 transform;
        Mesh* mesh;
        MaterialInstance* materialInstance;
};

Entity::Entity( QObject* parent )
    : GluonObject( parent ), d( new Private )
{
}

Entity::~Entity()
{
    delete d;
}

World*
Entity::world() const
{
    return d->world;
}

QMatrix4x4
Entity::transform() const
{
    return d->transform;
}

Mesh*
Entity::mesh() const
{
    return d->mesh;
}

bool
Entity::hasMesh() const
{
    return d->mesh != 0;
}

MaterialInstance*
Entity::materialInstance() const
{
    return d->materialInstance;
}

bool
Entity::hasMaterialInstance() const
{
    return d->materialInstance != 0;
}

void
Entity::setWorld(World* world)
{
    d->world = world;
}

void
Entity::render()
{
    if( !d->mesh || !d->materialInstance )
        return;

    Camera* activeCam = d->world->activeCamera();
    if( !activeCam )
        return;

    // TODO: Implement view frustum culling. After all, that is what that damn class is for... ;)
    d->materialInstance->setProperty( "projectionMatrix", activeCam->frustrum()->projectionMatrix() );
    d->materialInstance->setProperty( "viewMatrix", activeCam->transform() );
    d->materialInstance->setProperty( "modelMatrix", d->transform );

    if( !d->materialInstance->bind() )
        return;

    d->mesh->render( d->materialInstance->shader() );
    d->materialInstance->release();
}

void
Entity::setTransform( const QMatrix4x4 transform )
{
    d->transform = transform;
}

void
Entity::setMesh( Mesh* mesh )
{
    d->mesh = mesh;
}

void
Entity::setMaterialInstance( MaterialInstance* instance )
{
    d->materialInstance = instance;
}

#include "entity.moc"
