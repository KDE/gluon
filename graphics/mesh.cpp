/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010-2012 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "mesh.h"

#include "meshdata.h"

#include "core/debughelper.h"

using namespace GluonGraphics;

class Mesh::Private
{
    public:
        Private() : meshData( 0 ) { }

        MeshData* meshData;
};

Mesh::Mesh( QObject* parent )
    : QObject( parent ), d( new Private )
{
}

Mesh::~Mesh()
{
    delete d->meshData;
    delete d;
}

void Mesh::update()
{
    //Intentionally empty
}

bool
Mesh::isInitialized() const
{
    return d->meshData != 0;
}

void Mesh::render( Shader* shader )
{
    if( d->meshData )
        d->meshData->render( shader );
}

MeshData* Mesh::meshData()
{
    return d->meshData;
}

void Mesh::setMeshData( MeshData* data )
{
    if( d->meshData && data != d->meshData )
        delete d->meshData;

    d->meshData = data;
}

 
