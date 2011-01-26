/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include <QtGui/QMatrix4x4>
#include <QtGui/QColor>

#include "math.h"

using namespace GluonGraphics;

class Mesh::MeshPrivate
{
    public:
        MeshPrivate()
        {
        }

        VertexBuffer* buffer;
        MaterialInstance* material;
};

Mesh::Mesh( QObject* parent )
    : QObject( parent ),
      d( new MeshPrivate )
{
    d->buffer = new VertexBuffer( this );
}

Mesh::~Mesh()
{
    delete d;
}

void
Mesh::load( const QString& filename )
{
    if( isLoaded() )
        return;

    VertexAttribute vertices( "vertex", 3);
    vertices << -1.f << -1.f << 0.f;
    vertices << -1.f <<  1.f << 0.f;
    vertices <<  1.f <<  1.f << 0.f;
    vertices <<  1.f << -1.f << 0.f;
    d->buffer->addAttribute( vertices );

    VertexAttribute colors("color", 4 );
    colors << 1.f << 1.f << 1.f << 1.f;
    colors << 1.f << 1.f << 1.f << 1.f;
    colors << 1.f << 1.f << 1.f << 1.f;
    colors << 1.f << 1.f << 1.f << 1.f;
    d->buffer->addAttribute( colors );

    VertexAttribute uvs( "uv0", 2 );
    uvs << 0.f << 0.f;
    uvs << 0.f << 1.f;
    uvs << 1.f << 1.f;
    uvs << 1.f << 0.f;
    d->buffer->addAttribute( uvs );

    QVector<uint> indices;
    indices << 0 << 1 << 2
            << 0 << 2 << 3;

    d->buffer->setIndices( indices );

    d->buffer->initialize();
}

void
Mesh::render( MaterialInstance* material, VertexBuffer::RenderMode mode )
{
    d->buffer->render( mode, material );
}

bool
Mesh::isLoaded() const
{
    return d->buffer->isInitialized();
}

VertexBuffer*
Mesh::vertexBuffer() const
{
    return d->buffer;
}

#include "mesh.moc"
