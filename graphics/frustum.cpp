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

class Frustum::FrustumPrivate
{
    public:
        FrustumPrivate() { }
        FrustumPrivate( const FrustumPrivate& other )
            : matrix(other.matrix)
        {

        }

        QMatrix4x4 matrix;
};

Frustum::Frustum()
    : d(new FrustumPrivate)
{
    d->matrix.ortho(-1, 1, -1, 1, -1, 1);
}

Frustum::Frustum( const GluonGraphics::Frustum& other )
    : d(other.d)
{

}

Frustum& Frustum::operator=( const GluonGraphics::Frustum & other )
{
    d->matrix = other.d->matrix;

    return *this;
}


Frustum::~Frustum()
{
    delete d;
}

QMatrix4x4
Frustum::projectionMatrix()
{
    return d->matrix;
}

bool
Frustum::containsPoint( const QVector3D& point )
{

}

bool
Frustum::containsSphere( const QVector3D& point, float radius )
{

}

void
Frustum::setOrthographic( float left, float right, float bottom, float top, float near, float far )
{
    d->matrix.ortho(left, right, bottom, top, near, far);
}

void
Frustum::setPerspective( float fov, float aspect, float near, float far )
{
    d->matrix.perspective(fov, aspect, near, far);
}
