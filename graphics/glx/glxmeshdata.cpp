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

#include "glxmeshdata.h"

#include <QVector>
#include <QList>
#include <QDebug>

#include <GL/gl.h>

#include <graphics/shader.h>

#include "glxbuffer.h"
#include "glxfunctions.h"

using namespace GluonGraphics::GLX;

struct VertexAttribute
{
    QString name;
    int index;
    int size;
    GLenum type;
    int offset;
    int length;
};

class GLXMeshData::Private
{
    public:
        GLXBuffer* vertexBuffer;
        GLXBuffer* indexBuffer;

        GLenum mode;

        QList< VertexAttribute > attributes;
};

GLXMeshData::GLXMeshData() : d( new Private )
{
    d->vertexBuffer = new GLXBuffer;
    d->vertexBuffer->initialize( GluonGraphics::Buffer::Vertex, GluonGraphics::Buffer::Static );
    d->indexBuffer = new GLXBuffer;
    d->indexBuffer->initialize( GluonGraphics::Buffer::Index, GluonGraphics::Buffer::Static );
}

GLXMeshData::~GLXMeshData()
{
    delete d->vertexBuffer;
    delete d->indexBuffer;
}

void GLXMeshData::setIndices( QVector< uint > indices )
{
    d->indexBuffer->setData( reinterpret_cast< void* >( indices.data() ), indices.size() * sizeof( uint ), 0 );
}

void GLXMeshData::render( Shader* shader )
{
    d->vertexBuffer->bind();
    d->indexBuffer->bind();

    for( QList< VertexAttribute >::iterator itr = d->attributes.begin(); itr != d->attributes.end(); ++itr )
    {
        VertexAttribute& attribute = *itr;
        if( shader->hasAttribute( attribute.name ) )
        {
            attribute.index = shader->attributeIndex( attribute.name );
            glVertexAttribPointer( attribute.index, attribute.size, attribute.type, false, 0, reinterpret_cast< void* >( attribute.offset ) );
            glEnableVertexAttribArray( attribute.index );
        }
    }

    glDrawElements( d->mode, primitiveCount(), GL_UNSIGNED_INT, 0 );

    Q_FOREACH( const VertexAttribute& attribute, d->attributes )
    {
        if( attribute.index != -1 )
            glDisableVertexAttribArray( attribute.index );
    }

    d->indexBuffer->release();
    d->vertexBuffer->release();
}

void GLXMeshData::setPrimitiveType( GluonGraphics::MeshData::PrimitiveType type )
{
    switch( type )
    {
        case PointType:
            d->mode = GL_POINTS;
            break;
        case LineType:
            d->mode = GL_LINES;
            break;
        case TriangleType:
            d->mode = GL_TRIANGLES;
            break;
        case TriangleStripType:
            d->mode = GL_TRIANGLE_STRIP;
            break;
        case TriangleFanType:
            d->mode = GL_TRIANGLE_FAN;
            break;
    }

    GluonGraphics::MeshData::setPrimitiveType( type );
}

void GLXMeshData::setPrimitiveCount(int count, int vertexSize, int indexSize )
{
    d->vertexBuffer->setSize( vertexSize );
    d->indexBuffer->setSize( indexSize );
    MeshData::setPrimitiveCount( count );
}

void GLXMeshData::setAttribute(const QString& name, QVariant::Type type, void* data, int size)
{
    VertexAttribute attrib;
    attrib.name = name;
    attrib.index = -1;
    attrib.length = size;
    attrib.offset = d->attributes.count() > 0 ? d->attributes.last().offset + d->attributes.last().length : 0;

    switch( type )
    {
        case QVariant::Char:
            attrib.type = GL_BYTE;
            attrib.size = 1;
            break;
        case QVariant::UInt:
            attrib.type = GL_UNSIGNED_INT;
            attrib.size = 1;
            break;
        case QVariant::Int:
            attrib.type = GL_INT;
            attrib.size = 1;
            break;
        case 137: //QVariant::Float
            attrib.type = GL_FLOAT;
            attrib.size = 1;
            break;
        case QVariant::Double:
            attrib.type = GL_DOUBLE;
            attrib.size = 1;
            break;
        case QVariant::Vector2D:
            attrib.type = GL_FLOAT;
            attrib.size = 2;
            break;
        case QVariant::Vector3D:
            attrib.type = GL_FLOAT;
            attrib.size = 3;
            break;
        case QVariant::Vector4D:
        case QVariant::Color:
            attrib.type = GL_FLOAT;
            attrib.size = 4;
            break;
        default:
            return;
    }

    d->attributes.append( attrib );
    d->vertexBuffer->setData( data, size, attrib.offset );
}
