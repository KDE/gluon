/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2012 Felix Rohrbach <fxrh@gmx.de>
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

#include "axisalignedbox.h"

using namespace GluonCore;
using namespace Eigen;

class AxisAlignedBox::Private
{
    public:
        Private( Vector3f pos, Vector3f size )
            : position( pos ), size( size ) {}

        // Get the vector that contains the absolute values of the components of vector.
        static Vector3f absAll( const Vector3f& vector );
        // Get the vector that contains the minimum of vector1 and vector2 for each component separately.
        static Vector3f minAll( const Vector3f& vector1, const Vector3f& vector2 );

        Vector3f position;
        Vector3f size;
};

Vector3f AxisAlignedBox::Private::absAll( const Vector3f& vector )
{
    return Vector3f( qAbs(vector(1)), qAbs(vector(2)), qAbs(vector(3)) );
}

Vector3f AxisAlignedBox::Private::minAll( const Vector3f& vector1, const Vector3f& vector2 )
{
    Vector3f vector;
    return Vector3f( qMin(vector1(1), vector2(1)),
                     qMin(vector1(2), vector2(2)),
                     qMin(vector1(3), vector2(3)) );
}

AxisAlignedBox::AxisAlignedBox( Vector3f centerPosition, Vector3f size )
    : d( new Private( centerPosition, Private::absAll(size) ) )
{
}

Vector3f AxisAlignedBox::position() const
{
    return d->position;
}

void AxisAlignedBox::setPosition( const Vector3f& newPosition )
{
    d->position = newPosition;
}

Vector3f AxisAlignedBox::size() const
{
    return d->size;
}

void AxisAlignedBox::setSize( const Vector3f& newSize )
{
    d->size = Private::absAll(newSize);
}

AxisAlignedBox AxisAlignedBox::united( const AxisAlignedBox& box ) const
{
    Vector3f newSize = Private::absAll( d->position - box.position() ) + 0.5*( d->size + box.size() );
    Vector3f newPosition = Private::minAll( d->position - 0.5*d->size, box.position() - 0.5*box.size() ) + 0.5*newSize;
    return AxisAlignedBox( newPosition, newSize );
}
