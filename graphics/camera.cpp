/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Rivo Laks <rivolaks@hot.ee>
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

#include "camera.h"
#include <math.h>

#include <glew.h>

#include <core/debughelper.h>
#include "frustrum.h"
#include "engine.h"
#include "viewport.h"

using namespace GluonGraphics;

class Camera::CameraPrivate
{
    public:
        Frustrum* frustrum;
        QMatrix4x4 viewMatrix;
};

Camera::Camera( QObject* parent )
    : QObject( parent ),
      d(new CameraPrivate)
{
    d->frustrum = new Frustrum;
}

Camera::Camera( Frustrum* frustum, QObject* parent )
    : QObject( parent ),
      d(new CameraPrivate)
{
    d->frustrum = frustum;
}

Camera::~Camera()
{
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
Camera::setFrustrum( Frustrum * frustrum )
{
    d->frustrum = frustrum;
}

void
Camera::setViewMatrix( const QMatrix4x4& matrix )
{
    d->viewMatrix = matrix;
}

#include "camera.moc"
