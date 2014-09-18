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

#include "camera.h"

#include "frustum.h"
#include "world.h"

#include <QSizeF>

#include <Eigen/Core>

using namespace GluonGraphics;

class Camera::Private
{
    public:
        Frustum* frustum;
        Eigen::Affine3f viewMatrix;

        QSizeF visibleArea;
        float nearPlane;
        float farPlane;

        float aspect;
};

Camera::Camera( QObject* parent )
    : Entity( parent ), d( new Private )
{
    d->frustum = new Frustum;
}

Camera::Camera( Frustum* frustum, QObject* parent )
    : Entity( parent ), d( new Private )
{
    d->frustum = frustum;
}

Camera::~Camera()
{
    delete d->frustum;
    delete d;
}

Frustum*
Camera::frustum() const
{
    return d->frustum;
}

Eigen::Affine3f
Camera::viewMatrix() const
{
    return d->viewMatrix;
}

float Camera::nearPlane() const
{
    return d->nearPlane;
}

float Camera::farPlane() const
{
    return d->farPlane;
}

QSizeF Camera::visibleArea() const
{
    return d->visibleArea;
}

void Camera::setTransform( const Eigen::Affine3f& transform )
{
    d->viewMatrix = transform.inverse();
    Entity::setTransform( d->viewMatrix );
}

void
Camera::setFrustum( Frustum* frustum )
{
    d->frustum = frustum;
}

void Camera::setVisibleArea( QSizeF area )
{
    d->visibleArea = area;
    d->frustum->setOrthoAdjusted( d->visibleArea, d->aspect, d->nearPlane, d->farPlane );
}

void Camera::setNearPlane( float near )
{
    d->nearPlane = near;
    d->frustum->setOrthoAdjusted( d->visibleArea, d->aspect, d->nearPlane, d->farPlane );
}

void Camera::setFarPlane( float far )
{
    d->farPlane = far;
    d->frustum->setOrthoAdjusted( d->visibleArea, d->aspect, d->nearPlane, d->farPlane );
}

void Camera::render()
{
    //TODO: Render a dummy object for the camera.
}

void Camera::renderContents()
{
    world()->setActiveCamera( this );
    world()->render();
}

void Camera::resize( int width, int height )
{
    d->aspect = float(width) / float(height);
    d->frustum->setOrthoAdjusted( d->visibleArea, d->aspect, d->nearPlane, d->farPlane  );
}

 
