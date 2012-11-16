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

#include "world.h"

#include <QVector3D>
#include <QMatrix4x4>

#include "entity.h"
#include "camera.h"

using namespace GluonGraphics;

class World::Private
{
    public:
        void sortEntities();

        Camera* activeCamera;

        QList< Entity* > entities;

        static bool compareEntityZDepth( Entity* first, Entity* second );
};

World::World( QObject* parent ) : d( new Private )
{

}

World::~World()
{
    delete d;
}

void World::addEntity(Entity* entity)
{
    if( !entity )
        return;

    entity->setWorld( this );
    d->entities.append( entity );
}

Entity* World::entity( int index ) const
{
    if( index < 0 || index >= d->entities.size() )
        return 0;

    return d->entities.at( index );
}

int World::entityIndex( Entity* entity ) const
{
    return d->entities.indexOf( entity );
}

void World::destroyEntity(int index )
{
    destroyEntity( entity( index ) );
}

void World::destroyEntity(Entity* entity)
{
    if( entity )
        d->entities.removeOne( entity );

    entity->deleteLater();
}

void World::render()
{
    d->sortEntities();

    const int count = d->entities.count();
    for( int i = 0; i < count; ++i )
    {
        d->entities[i]->render();
    }
}

Camera* World::activeCamera() const
{
    return d->activeCamera;
}

void World::setActiveCamera( Camera* cam )
{
    d->activeCamera = cam;
}

void World::Private::sortEntities()
{
    qStableSort(entities.begin(), entities.end(), Private::compareEntityZDepth);
}

bool World::Private::compareEntityZDepth( Entity* first, Entity* second )
{
    QVector3D posFirst;
    QVector3D posSecond;

    posFirst = posFirst * first->transform();
    posSecond = posSecond * second->transform();

    return posFirst.z() < posSecond.z();
}

#include "world.moc"
