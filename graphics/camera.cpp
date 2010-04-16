/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Rivo Laks <rivolaks@hot.ee>
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 * Copyright (C) 2010 Arjen Hiemstra <>
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

using namespace GluonGraphics;

class Camera::CameraPrivate
{
    public:
        CameraPrivate()
            : visibleArea(100.0f, 100.0f),
            aspectRatio(1.0f),
            nearPlane(1.0f),
            farPlane(100.0f),
            modelViewMatrixDirty(true)
        { }
        
        QVector3D position;
        QQuaternion orientation;
        
        float aspectRatio;
        float nearPlane;
        float farPlane;
        
        QMatrix4x4 modelViewMatrix;
        bool modelViewMatrixDirty;
        
        int viewport[4];
        QSizeF visibleArea;
};

Camera::Camera()
    : d(new CameraPrivate)
{
    
}

Camera::~Camera()
{
    delete d;
}

void Camera::setAspectRatio(float aspect)
{
    d->aspectRatio = aspect;
}

void Camera::setDepthRange(float near, float far)
{
    d->nearPlane = near;
    d->farPlane = far;
    
    applyOrtho();
}

void Camera::setPosition(const QVector3D& pos)
{
    d->position = pos;
    d->modelViewMatrixDirty = true;
}

void Camera::setPosition(float x, float y, float z)
{
    setPosition(QVector3D(x, y, z));
    
    recalculateModelviewMatrix();
}

QVector3D Camera::position() const
{
    return d->position;
}

QQuaternion Camera::orientation() const
{
    return d->orientation;
}

void Camera::setOrientation(const QQuaternion& orient)
{
    d->orientation = orient;
    recalculateModelviewMatrix();
}


void Camera::setViewport(int x, int y, int width, int height)
{
    d->viewport[0] = x;
    d->viewport[1] = y;
    d->viewport[2] = width;
    d->viewport[3] = height;
}

void Camera::setVisibleArea(const QSizeF& area)
{
    d->visibleArea = area;
    
    applyOrtho();
}

void Camera::applyOrtho()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
 
    glOrtho(-(d->visibleArea.width()/2), d->visibleArea.width()/2, -(d->visibleArea.height()/2), d->visibleArea.height()/2, d->nearPlane, d->farPlane);
    glMatrixMode(GL_MODELVIEW);
}

void Camera::applyView(bool reset)
{
    if (d->modelViewMatrixDirty)
    {
        recalculateModelviewMatrix();
    }
    
    glMatrixMode(GL_MODELVIEW);
    glMultMatrixd((GLdouble*)d->modelViewMatrix.data());
}

void Camera::applyViewport()
{
    glViewport(d->viewport[0], d->viewport[1], d->viewport[2], d->viewport[3]);
}

void Camera::recalculateModelviewMatrix()
{
    d->modelViewMatrixDirty = false;

    d->modelViewMatrix.setToIdentity();
    d->modelViewMatrix.translate(d->position);
    d->modelViewMatrix.rotate(d->orientation);
    d->modelViewMatrix = d->modelViewMatrix.inverted();
}

void Camera::setModelviewMatrix(const QMatrix4x4& modelview)
{
    d->modelViewMatrix = modelview;
    d->modelViewMatrixDirty = false;
}

QMatrix4x4 Camera::modelviewMatrix() const
{
    return d->modelViewMatrix;
}

#include "camera.moc"
