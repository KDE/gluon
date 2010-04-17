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
        
        QRect viewport;
        float viewportAspect;
        QSizeF visibleArea;
        
        QRectF clippingArea;
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
    d->viewport.setRect(x, y, width, height);
    d->viewportAspect = width/float(height);
    
    float visibleWidth = float(width);
    float actualWidth = 0;
    float visibleHeight = float(height);
    float actualHeight = 0;
    float widthDiff = 0;
    float heightDiff = 0;
    
    if(d->viewportAspect > 1)
    {
        actualHeight = visibleHeight;
        actualWidth = visibleHeight * d->aspectRatio;
        widthDiff = visibleWidth - actualWidth;
    }
    else
    {
        actualWidth = visibleWidth;
        actualHeight = visibleWidth * (d->visibleArea.height() / d->visibleArea.width());
        heightDiff = visibleHeight - actualHeight;
    }
    
    d->clippingArea.setX(widthDiff/2);
    d->clippingArea.setWidth(actualWidth);
    d->clippingArea.setY(heightDiff/2);
    d->clippingArea.setHeight(actualHeight);
}

void Camera::setVisibleArea(const QSizeF& area)
{
    d->visibleArea = area;
    d->aspectRatio = area.width() / area.height();
    
    applyOrtho();
}

void Camera::applyOrtho()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    float visibleWidth = d->visibleArea.width();
    float visibleHeight = d->visibleArea.height();
    
    if(d->viewportAspect > 1)
    {
        visibleWidth = visibleWidth * d->viewportAspect;
    }
    else
    {
        visibleHeight = visibleHeight * (d->viewport.height()/float(d->viewport.width()));
    }
    
    glOrtho(-(visibleWidth/2), visibleWidth/2, -(visibleHeight/2), visibleHeight/2, d->nearPlane, d->farPlane);
    
    glMatrixMode(GL_MODELVIEW);
}

void Camera::applyView(bool reset)
{
    if (d->modelViewMatrixDirty)
    {
        recalculateModelviewMatrix();
    }
    
    glScissor(d->clippingArea.x(), d->clippingArea.y(), d->clippingArea.width(), d->clippingArea.height());
    
    glMatrixMode(GL_MODELVIEW);
    glMultMatrixd((GLdouble*)d->modelViewMatrix.data());
}

void Camera::applyViewport()
{
    glViewport(d->viewport.x(), d->viewport.y(), d->viewport.width(), d->viewport.height());
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
