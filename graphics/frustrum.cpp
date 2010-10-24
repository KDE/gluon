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

#include "frustrum.h"

#include <QtGui/QMatrix4x4>

using namespace GluonGraphics;

class Frustrum::FrustrumPrivate
{
    public:
        FrustrumPrivate() { mode = FM_ORTHO; }
        FrustrumPrivate( const FrustrumPrivate& other )
            : matrix(other.matrix)
        {

        }

        enum Mode
        {
            FM_ORTHO,
            FM_ADJUSTED_ORTHO,
            FM_PERSPECTIVE
        };

        Mode mode;

        QMatrix4x4 matrix;

        QRectF viewPlane;
        float nearPlane;
        float farPlane;
        float fov;
};

Frustrum::Frustrum()
    : d(new FrustrumPrivate)
{
    d->matrix.ortho(-50, 50, -50, 50, 1, 100);
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
    return false;
}

bool
Frustrum::containsSphere( const QVector3D& point, float radius )
{
    return false;
}

float Frustrum::nearPlane()
{
    return d->nearPlane;
}

float Frustrum::farPlane()
{
    return d->farPlane;
}

QRectF Frustrum::viewPlane()
{
    return d->viewPlane;
}

void
Frustrum::setOrthographic( float left, float right, float bottom, float top, float near, float far )
{
    d->matrix.setToIdentity();
    d->matrix.ortho(left, right, bottom, top, near, far);

    d->nearPlane = near;
    d->farPlane = far;

    d->viewPlane.setCoords(left, top, right, bottom);

    d->mode = FrustrumPrivate::FM_ORTHO;
}

void
Frustrum::setOrthoAdjusted( const QSizeF& area, float aspect, float near, float far )
{
    float visibleWidth = area.width();
    float visibleHeight = area.height();

    if(aspect > 1.f)
    {
        visibleWidth = visibleWidth * aspect;
    }
    else
    {
        visibleHeight = visibleHeight * (1/aspect);
    }

    d->matrix.setToIdentity();
    d->matrix.ortho(-(visibleWidth/2), visibleWidth/2, -(visibleHeight/2), visibleHeight/2, near, far);

    d->nearPlane = near;
    d->farPlane = far;

    d->viewPlane.setCoords( -(area.width()/2), -(area.height()/2), area.width()/2, area.height()/2 );

    d->mode = FrustrumPrivate::FM_ADJUSTED_ORTHO;
}

void
Frustrum::setPerspective( float fov, float aspect, float near, float far )
{
    d->matrix.setToIdentity();
    d->matrix.perspective(fov, aspect, near, far);

    d->nearPlane = near;
    d->farPlane = far;
    d->fov = fov;

    //Todo: set view plane.

    d->mode = FrustrumPrivate::FM_PERSPECTIVE;
}

void Frustrum::updateFrustrum( float aspect )
{
    switch(d->mode)
    {
        case FrustrumPrivate::FM_ORTHO:
            break;
        case FrustrumPrivate::FM_ADJUSTED_ORTHO:
            setOrthoAdjusted(d->viewPlane.size(), aspect, d->nearPlane, d->farPlane);
            break;
        case FrustrumPrivate::FM_PERSPECTIVE:
            setPerspective(d->fov, aspect, d->nearPlane, d->farPlane);
            break;
    }
}








