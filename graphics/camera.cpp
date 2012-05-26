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

#include "frustrum.h"
#include "viewport.h"
#include "world.h"

#include <QtGui/QMatrix4x4>

using namespace GluonGraphics;

class Camera::Private
{
    public:
        Frustrum* frustrum;
        QMatrix4x4 viewMatrix;
};

Camera::Camera( QObject* parent )
    : Entity( parent ), d( new Private )
{
    d->frustrum = new Frustrum;
}

Camera::Camera( Frustrum* frustum, QObject* parent )
    : Entity( parent ), d( new Private )
{
    d->frustrum = frustum;
}

Camera::~Camera()
{
    delete d->frustrum;
    delete d;
}

Frustrum*
Camera::frustrum()
{
    return d->frustrum;
}

QMatrix4x4
Camera::viewMatrix()
{
    return d->viewMatrix;
}

void
Camera::setFrustrum( Frustrum* frustrum )
{
    d->frustrum = frustrum;
}

void
Camera::setViewMatrix( const QMatrix4x4& matrix )
{
    d->viewMatrix = matrix;
}

void Camera::render()
{
    //world()->setActivateCamera( this );
    //world()->render();
}

void Camera::renderContents()
{
    world()->render();
}

#include "camera.moc"
