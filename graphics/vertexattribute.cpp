/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Giulio Camuffo <giuliocamuffo@gmail.com>
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

#include "vertexattribute.h"

#include <QString>

using namespace GluonGraphics;

class VertexAttribute::VertexAttributePrivate
{
    public:
        VertexAttributePrivate()
            : location( -1 )
            , offset( -1 )
            , size( 0 )
        {

        }

        QVector<float> data;
        QString name;
        int location;
        int offset;
        int size;
};

VertexAttribute::VertexAttribute()
               : d( new VertexAttributePrivate() )
{
}

VertexAttribute::VertexAttribute( const QString& name, int size)
               : d( new VertexAttributePrivate() )
{
    d->name = name;
    d->size = size;
}

VertexAttribute::VertexAttribute( const VertexAttribute& other )
               : d( new VertexAttributePrivate() )
{
    *this = other;
}

VertexAttribute::~VertexAttribute()
{
    delete d;
}

void VertexAttribute::append( float data )
{
    d->data << data;
}

void VertexAttribute::setLocation( int location )
{
    d->location = location;
}

void VertexAttribute::setOffset( int offset )
{
    d->offset = offset;
}

const float* VertexAttribute::data() const
{
    return d->data.constData();
}

QString VertexAttribute::name() const
{
    return d->name;
}

int VertexAttribute::itemCount() const
{
    return d->data.size();
}

int VertexAttribute::itemSize() const
{
    return d->size;
}

int VertexAttribute::size() const
{
    return d->data.size() * sizeof( float );
}
int VertexAttribute::location() const
{
    return d->location;
}

int VertexAttribute::offset() const
{
    return d->offset;
}

VertexAttribute& VertexAttribute::operator=( const VertexAttribute& other )
{
    d->name = other.d->name;
    d->size = other.d->size;
    d->data = other.d->data;
    d->location = other.d->location;
    d->offset = other.d->offset;
    d->size = other.d->size;

    return *this;
}

VertexAttribute& VertexAttribute::operator<<( float data )
{
    d->data << data;

    return *this;
}
