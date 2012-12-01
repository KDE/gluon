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

#include <QQuaternion>

using namespace GluonCore;

class AxisAlignedBox::Private
{
    public:
        Private( QVector3D pos, QVector3D size )
            : position( pos ), size( size ) {}

        // Get the vector that contains the absolute values of the components of vector.
        static QVector3D absAll( const QVector3D& vector );
        // Get the vector that contains the minimum of vector1 and vector2 for each component separately.
        static QVector3D minAll( const QVector3D& vector1, const QVector3D& vector2 );
        // Get the vector that contains the maximum of vector1 and vector2 for each component separately.
        static QVector3D maxAll( const QVector3D& vector1, const QVector3D& vector2 );

        QVector3D position;
        QVector3D size;
};

QVector3D AxisAlignedBox::Private::absAll( const QVector3D& vector )
{
    return QVector3D( qAbs(vector.x()), qAbs(vector.y()), qAbs(vector.z()) );
}

QVector3D AxisAlignedBox::Private::minAll( const QVector3D& vector1, const QVector3D& vector2 )
{
    return QVector3D( qMin(vector1.x(), vector2.x()),
                      qMin(vector1.y(), vector2.y()),
                      qMin(vector1.z(), vector2.z()) );
}

QVector3D AxisAlignedBox::Private::maxAll( const QVector3D& vector1, const QVector3D& vector2 )
{
    return QVector3D( qMax(vector1.x(), vector2.x()),
                      qMax(vector1.y(), vector2.y()),
                      qMax(vector1.z(), vector2.z()) );
}

AxisAlignedBox::AxisAlignedBox( QVector3D centerPosition, QVector3D size )
    : d( new Private( centerPosition, Private::absAll(size) ) )
{
}

AxisAlignedBox::AxisAlignedBox( const AxisAlignedBox& box )
    : d( new Private( box.d->position, box.d->size ) )
{
}

AxisAlignedBox::~AxisAlignedBox()
{
    delete d;
}

QVector3D AxisAlignedBox::position() const
{
    return d->position;
}

void AxisAlignedBox::setPosition( const QVector3D& newPosition )
{
    d->position = newPosition;
}

QVector3D AxisAlignedBox::size() const
{
    return d->size;
}

void AxisAlignedBox::setSize( const QVector3D& newSize )
{
    d->size = Private::absAll(newSize);
}

AxisAlignedBox AxisAlignedBox::united( const AxisAlignedBox& box ) const
{
    QVector3D newSize = Private::absAll( d->position - box.position() ) + 0.5*( d->size + box.size() );
    QVector3D newPosition = Private::minAll( d->position - 0.5*d->size, box.position() - 0.5*box.size() ) + 0.5*newSize;
    return AxisAlignedBox( newPosition, newSize );
}

void AxisAlignedBox::unite( const AxisAlignedBox& box )
{
    QVector3D newSize = Private::absAll( d->position - box.position() ) + 0.5*( d->size + box.size() );
    d->position = Private::minAll( d->position - 0.5*d->size, box.position() - 0.5*box.size() ) + 0.5*newSize;
    d->size = newSize;
}

AxisAlignedBox AxisAlignedBox::scaled( const QVector3D& factors ) const
{
    return AxisAlignedBox( d->position, d->size * factors );
}

void AxisAlignedBox::scale( const QVector3D& factors )
{
    d->size *= factors;
}

AxisAlignedBox AxisAlignedBox::rotated( const QQuaternion& orientation ) const
{
    QVector3D rotatedXVector = orientation.rotatedVector( QVector3D(d->size.x(), 0, 0) );
    QVector3D rotatedYVector = orientation.rotatedVector( QVector3D(0, d->size.y(), 0) );
    QVector3D rotatedZVector = orientation.rotatedVector( QVector3D(0, 0, d->size.z()) );
    QVector3D rotatedVector = Private::maxAll( rotatedXVector, Private::maxAll( rotatedYVector, rotatedZVector ) );
    return AxisAlignedBox( d->position, rotatedVector );
}

void AxisAlignedBox::rotate( const QQuaternion& orientation )
{
    QVector3D rotatedXVector = orientation.rotatedVector( QVector3D(d->size.x(), 0, 0) );
    QVector3D rotatedYVector = orientation.rotatedVector( QVector3D(0, d->size.y(), 0) );
    QVector3D rotatedZVector = orientation.rotatedVector( QVector3D(0, 0, d->size.z()) );
    d->size = Private::maxAll( rotatedXVector, Private::maxAll( rotatedYVector, rotatedZVector ) );
}

AxisAlignedBox& AxisAlignedBox::operator=( const AxisAlignedBox& box )
{
    d->size = box.d->size;
    d->position = box.d->position;
    return *this;
}
