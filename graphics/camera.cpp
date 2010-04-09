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
            : fieldOfView(90),
            aspectRatio(1.0f),
            nearPlane(0.0f),
            farPlane(100.0f),
            modelViewMatrixDirty(true),
            projectionMatrixDirty(true)
        { }
        QVector3D position;
        
        float fieldOfView;
        float aspectRatio;
        float nearPlane;
        float farPlane;
        
        QMatrix4x4 modelViewMatrix;
        bool modelViewMatrixDirty;
        QMatrix4x4 projectionMatrix;
        bool projectionMatrixDirty;
        
        int viewport[4];
};

Camera::Camera()
    : d(new CameraPrivate)
{
    
}

Camera::~Camera()
{
}

void Camera::setFieldOfView(float fov)
{
    d->fieldOfView = fov;
    d->projectionMatrixDirty = true;
}

void Camera::setAspectRatio(float aspect)
{
    d->aspectRatio = aspect;
    d->projectionMatrixDirty = true;
}

void Camera::setDepthRange(float near, float far)
{
    d->nearPlane = near;
    d->farPlane = far;
    d->projectionMatrixDirty = true;
}

void Camera::setPosition(const QVector3D& pos)
{
    d->position = pos;
    d->modelViewMatrixDirty = true;
}

void Camera::setPosition(float x, float y, float z)
{
    setPosition(QVector3D(x, y, z));
}

QVector3D Camera::position() const
{
    return d->position;
}


/*void Camera::setLookAt(const QVector3D& lookat)
{
    mLookAt = lookat;
    mModelviewMatrixDirty = true;
}

void Camera::setUp(const QVector3D& up)
{
    mUp = up;
    mModelviewMatrixDirty = true;
}

void Camera::setDirection(const QVector3D& dir)
{
    setLookAt(mPosition + dir);
}*/

void Camera::setViewport(int x, int y, int width, int height)
{
    d->viewport[0] = x;
    d->viewport[1] = y;
    d->viewport[2] = width;
    d->viewport[3] = height;
}

void Camera::applyPerspective()
{
    if (d->projectionMatrixDirty)
    {
        recalculateProjectionMatrix();
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMultMatrixd((GLdouble*)(d->projectionMatrix.data()));
    glMatrixMode(GL_MODELVIEW);
}

void Camera::applyOrtho()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float left = d->viewport[0] / 10.0f - d->viewport[2] / 20.0f;
    float right = (d->viewport[0] + d->viewport[2]) / 20.0f;
    float top = d->viewport[1] / 10.0f - d->viewport[3] / 20.0f;
    float bottom = (d->viewport[1] + d->viewport[3]) / 20.0f;

    glOrtho(left, right, top, bottom, d->nearPlane, d->farPlane);
    glMatrixMode(GL_MODELVIEW);
}

void Camera::applyView(bool reset)
{
    if (d->modelViewMatrixDirty)
    {
        recalculateModelviewMatrix();
    }

    if (reset)
    {
        glLoadIdentity();
    }
    glMultMatrixd((GLdouble*)(d->modelViewMatrix.data()));
}

void Camera::applyViewport()
{
    glViewport(d->viewport[0], d->viewport[1], d->viewport[2], d->viewport[3]);
}

void Camera::recalculateModelviewMatrix()
{
    // Code from Mesa project, src/glu/sgi/libutil/project.c
    d->modelViewMatrixDirty = false;
    /*QVector3D forward = mLookAt.normalized();
    QVector3D side = -QVector3D::crossProduct(forward, mUp).normalized();
    QVector3D up = QVector3D::crossProduct(side, forward);*/
    QVector3D forward(0.0f, 0.0f, 1.0f);
    QVector3D side(1.0f, 0.0f, 0.0f);
    QVector3D up(0.0f, 1.0f, 0.0f);

    d->modelViewMatrix.setToIdentity();
    d->modelViewMatrix.setColumn(0, QVector4D(side.x(), side.y(), side.z(), 0));
    d->modelViewMatrix.setColumn(1, QVector4D(up.x(), up.y(), up.z(), 0));
    d->modelViewMatrix.setColumn(2, QVector4D(-forward.x(), -forward.y(), -forward.z(), 0));
    d->modelViewMatrix.translate(d->position);
}

void Camera::recalculateProjectionMatrix()
{
    // Code from Mesa project, src/glu/sgi/libutil/project.c
    d->projectionMatrixDirty = false;
    d->projectionMatrix.setToIdentity();

    float radians = d->fieldOfView / 2 * M_PI / 180;

    float deltaZ = d->farPlane - d->nearPlane;
//    float sine = Eigen::ei_sin(radians);
    float sine = sin(radians);
    if ((deltaZ == 0) || (sine == 0) || (d->aspectRatio == 0))
    {
        return;
    }
//    float cotangent = Eigen::ei_cos(radians) / sine;
    float cotangent = cos(radians) / sine;

    d->projectionMatrix(0, 0) = cotangent / d->aspectRatio;
    d->projectionMatrix(1, 1) = cotangent;
    d->projectionMatrix(2, 2) = -(d->farPlane + d->nearPlane) / deltaZ;
    d->projectionMatrix(3, 2) = -1;
    d->projectionMatrix(2, 3) = -2 * d->nearPlane * d->farPlane / deltaZ;
    d->projectionMatrix(3, 3) = 0;

    //glO
    //mProjectionMatrix.
}

void Camera::setModelviewMatrix(const QMatrix4x4& modelview)
{
    d->modelViewMatrix = modelview;
    d->modelViewMatrixDirty = false;
}

void Camera::setProjectionMatrix(const QMatrix4x4& projection)
{
    d->projectionMatrix = projection;
    d->projectionMatrixDirty = false;
}

QMatrix4x4 Camera::modelviewMatrix() const
{
    if (d->modelViewMatrixDirty)
    {
        const_cast<Camera*>(this)->recalculateModelviewMatrix();
    }
    return d->modelViewMatrix;
}

QMatrix4x4 Camera::projectionMatrix() const
{
    if (d->projectionMatrixDirty)
    {
        const_cast<Camera*>(this)->recalculateProjectionMatrix();
    }
    return d->projectionMatrix;
}

QVector3D Camera::project(const QVector3D& v, bool* ok) const
{
    // TODO add unit test
//    QVector3D res;
//    QVector4D p4 = projectionMatrix() * (modelviewMatrix() * QVector4D(v[0],v[1],v[2],1));
//    if (p4.w()!=0)
//    {
//      res = p4.start<3>() / p4.w();
//      res = (res * 0.5).cwise() + 0.5;
//      res.start<2>() = Eigen::Vector2f(mViewport[0],mViewport[1])
//                       + Eigen::Vector2f(mViewport[2],mViewport[3]).cwise() * res.start<2>();
//      if (ok)
//          *ok = true;
//    }
//    else if (ok)
//        *ok = false;
//    return res;
}

QVector3D Camera::unProject(const QVector3D& v, bool* ok) const
{
    // TODO add unit test
    /*   if (ok) *ok = true;
        Eigen::Vector4f a;
        a << (v.start<2>() - Eigen::Vector2f(mViewport[0],mViewport[1]))
                  .cwise() / Eigen::Vector2f(mViewport[2],mViewport[3]),
             v.z(),
             1;
        a.start<3>() = a.start<3>() * 2 - Eigen::Vector3f::Constant(1);
        // FIXME if we assume the projection matrix always has the structure defined in
        // recalculateProjectionMatrix, then the following matrix product could be
        // significantly improved !!
        a = (projectionMatrix() * modelviewMatrix()).inverse() * a;
        if (a.w()==0)
        {
            if (ok) *ok = false;
            return a.start<3>();
        }
        return a.start<3>() / a.w();*/
}

#include "camera.moc"
