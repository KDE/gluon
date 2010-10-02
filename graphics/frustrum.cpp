/*****************************************************************************
 * This file is part of the Gluon Development Platform
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

#include "frustum.h"

#include <QtGui/QMatrix4x4>

using namespace GluonGraphics;

class Frustrum::FrustrumPrivate
{
    public:
        FrustrumPrivate() { }
        FrustrumPrivate( const FrustrumPrivate& other )
            : matrix(other.matrix)
        {

        }

        QMatrix4x4 matrix;
};

Frustrum::Frustrum()
    : d(new FrustrumPrivate)
{
    d->matrix.ortho(-1, 1, -1, 1, -1, 1);
}

Frustrum::Frustrum( const GluonGraphics::Frustrum& other )
    : d(other.d)
{

}

Frustrum& Frustrum::operator=( const GluonGraphics::Frustrum & other )
{
    d->matrix = other.d->matrix;

    return *this;
}


Frustrum::~Frustrum()
{
    delete d;
}

QMatrix4x4
Frustrum::projectionMatrix()
{
    return d->matrix;
}

bool
Frustrum::containsPoint( const QVector3D& point )
{

}

bool
Frustrum::containsSphere( const QVector3D& point, float radius )
{

}

void
Frustrum::setOrthographic( float left, float right, float bottom, float top, float near, float far )
{
    d->matrix.ortho(left, right, bottom, top, near, far);
}

void
Frustrum::setPerspective( float fov, float aspect, float near, float far )
{
    d->matrix.perspective(fov, aspect, near, far);
}
