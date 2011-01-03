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

#include <QtGui/QMatrix4x4>
#include <QtGui/QColor>

#include "math.h"
#include "glheaders.h"

using namespace GluonGraphics;

class Mesh::MeshPrivate
{
    public:
        MeshPrivate()
        {
            buffer = 0;
            vertexLoc = -1;
            colorLoc = -1;
            uvLoc = -1;
            vertexCount = 0;
        }

        MaterialInstance* material;

        GLuint buffer;
        int colorOffset;
        int uvOffset;

        int vertexLoc;
        int colorLoc;
        int uvLoc;

        int vertexCount;
};

Mesh::Mesh( QObject* parent )
    : QObject( parent ),
      d( new MeshPrivate )
{

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

#ifdef __GNUC__
#warning Todo: Move vertex buffer related stuff to a VertexBuffer class.
#endif

    QVector<float> vertices;
    vertices << -1.f << -1.f << 0.f;
    vertices << -1.f <<  1.f << 0.f;
    vertices <<  1.f <<  1.f << 0.f;

    vertices << -1.f << -1.f << 0.f;
    vertices <<  1.f <<  1.f << 0.f;
    vertices <<  1.f << -1.f << 0.f;

    QVector<float> colors;
    colors << 1.f << 1.f << 1.f << 1.f;
    colors << 1.f << 1.f << 1.f << 1.f;
    colors << 1.f << 1.f << 1.f << 1.f;

    colors << 1.f << 1.f << 1.f << 1.f;
    colors << 1.f << 1.f << 1.f << 1.f;
    colors << 1.f << 1.f << 1.f << 1.f;

    QVector<float> uvs;
    uvs << 0.f << 0.f;
    uvs << 0.f << 1.f;
    uvs << 1.f << 1.f;

    uvs << 0.f << 0.f;
    uvs << 1.f << 1.f;
    uvs << 1.f << 0.f;

    createBuffer( vertices, colors, uvs );
}

void
Mesh::render( MaterialInstance* material )
{
    renderBuffer( GL_TRIANGLES, d->vertexCount, material );
}

bool
Mesh::isLoaded()
{
    return d->buffer != 0;
}

void
Mesh::createBuffer( const QVector<float>& vertices, const QVector<float>& colors, const QVector<float>& uvs )
{
    glGenBuffers( 1, &d->buffer );
    glBindBuffer( GL_ARRAY_BUFFER, d->buffer );
    glBufferData( GL_ARRAY_BUFFER, ( vertices.size() * 4 ) + ( colors.size() * 4 ) + ( uvs.size() * 4 ), 0, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, vertices.size() * 4, vertices.data() );
    d->colorOffset = vertices.size() * 4;
    glBufferSubData( GL_ARRAY_BUFFER, d->colorOffset, colors.size() * 4, colors.data() );
    d->uvOffset = d->colorOffset + colors.size() * 4;
    glBufferSubData( GL_ARRAY_BUFFER, d->uvOffset, uvs.size() * 4, uvs.data() );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    d->vertexCount = vertices.size();
}

void
Mesh::renderBuffer( uint mode, int count, MaterialInstance* material )
{
    if( d->buffer == 0 )
        return;

    if( d->vertexLoc == -1 )
        d->vertexLoc = material->attributeLocation( "vertex" );

    if( d->colorLoc == -1 )
        d->colorLoc = material->attributeLocation( "color" );

    if( d->uvLoc == -1 )
        d->uvLoc = material->attributeLocation( "uv0" );

    glBindBuffer( GL_ARRAY_BUFFER, d->buffer );
    glVertexAttribPointer( d->vertexLoc, 3, GL_FLOAT, 0, 0, 0 );
    glVertexAttribPointer( d->colorLoc, 4, GL_FLOAT, 0, 0, ( void* )( d->colorOffset ) );
    glVertexAttribPointer( d->uvLoc, 2, GL_FLOAT, 0, 0, ( void* )( d->uvOffset ) );

    glEnableVertexAttribArray( d->vertexLoc );
    glEnableVertexAttribArray( d->colorLoc );
    glEnableVertexAttribArray( d->uvLoc );

    glDrawArrays( mode, 0, count );

    glDisableVertexAttribArray( d->vertexLoc );
    glDisableVertexAttribArray( d->colorLoc );
    glDisableVertexAttribArray( d->uvLoc );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

#include "mesh.moc"
