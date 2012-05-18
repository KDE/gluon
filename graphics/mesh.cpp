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

#include "materialinstance.h"
#include "vertexbuffer.h"
#include "vertexattribute.h"
#include "math.h"

using namespace GluonGraphics;

class Mesh::Private
{
    public:
        Private() : buffer(0), material(0)
        {
        }

        VertexBuffer* buffer;
        MaterialInstance* material;
};

Mesh::Mesh( QObject* parent )
    : QObject( parent ), d( new Private )
{
    d->buffer = new VertexBuffer( VertexBuffer::BM_STATIC_DRAW, this );
}

Mesh::~Mesh()
{
    delete d->buffer;
    delete d;
}

void
Mesh::setVertexBuffer( VertexBuffer* buffer )
{
    if( d->buffer )
    {
        delete d->buffer;
    }

    d->buffer = buffer;

    if( buffer )
    {
        buffer->setParent( this );
        if( !buffer->isInitialized() )
        {
            buffer->initialize();
        }
    }
}

void Mesh::update()
{
    //Intentionally empty
}

void
Mesh::render( MaterialInstance* material, VertexBuffer::RenderMode mode )
{
    d->buffer->render( mode, material );
}

bool
Mesh::isInitialized() const
{
    return d->buffer && d->buffer->isInitialized();
}

VertexBuffer*
Mesh::vertexBuffer() const
{
    return d->buffer;
}

#include "mesh.moc"
