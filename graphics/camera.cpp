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
#include "frustum.h"

using namespace GluonGraphics;

class Camera::CameraPrivate
{
    public:
        Frustum* frustum;
        QMatrix4x4 viewMatrix;
};

Camera::Camera( QObject* parent )
    : QObject( parent ),
      d(new CameraPrivate)
{
    d->frustum = new Frustum;
}

Camera::Camera( Frustum* frustum, QObject* parent )
    : QObject( parent ),
      d(new CameraPrivate)
{
    d->frustum = frustum;
}

Camera::~Camera()
{
    delete d;
}

Frustum*
Camera::frustum()
{
    return d->frustum;
}

QMatrix4x4
Camera::viewMatrix()
{
    return d->viewMatrix;
}

void
Camera::setFrustrum( Frustum * frustum )
{
    d->frustum = frustum;
}

void
Camera::setViewMatrix( const QMatrix4x4& matrix )
{
    d->viewMatrix = matrix;
}


#include "camera.moc"
