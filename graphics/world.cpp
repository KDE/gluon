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

#include "entity.h"

using namespace GluonGraphics;

class World::Private
{
    public:

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

}

Entity* World::entity(int id)
{
    return 0;
}

void World::destroyEntity(int id)
{

}

void World::destroyEntity(Entity* entity)
{

}

void World::render()
{

}

#include "world.moc"
