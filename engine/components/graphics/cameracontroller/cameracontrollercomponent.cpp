/******************************************************************************
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

#include "cameracontrollercomponent.h"

#include <core/debughelper.h>
#include <graphics/camera.h>
#include <engine/gameobject.h>
#include <graphics/engine.h>

REGISTER_OBJECTTYPE(GluonEngine, CameraControllerComponent)

using namespace GluonEngine;

class CameraControllerComponent::CameraControllerComponentPrivate
{
    public:
        CameraControllerComponentPrivate()
        {
            camera = 0;
            active = true;
            visibleArea = QSizeF(100.0f, 100.0f);
            nearPlane = 1.0f;
            farPlane = 100.0f;
        }

        GluonGraphics::Camera *camera;
        bool active;
        QSizeF visibleArea;
        float nearPlane;
        float farPlane;

        static GluonGraphics::Camera *activeCamera;
};

GluonGraphics::Camera* CameraControllerComponent::CameraControllerComponentPrivate::activeCamera = 0;

CameraControllerComponent::CameraControllerComponent(QObject* parent) 
    : Component(parent),
    d(new CameraControllerComponentPrivate)
{
    
}

CameraControllerComponent::CameraControllerComponent(const CameraControllerComponent& other)
        : Component(other),
        d(other.d)
{
}

CameraControllerComponent::~CameraControllerComponent()
{
    delete d;
}

void CameraControllerComponent::initialize()
{
    if (!d->camera)
        d->camera = new GluonGraphics::Camera();
    
    if (d->active)
    {
        GluonGraphics::Engine::instance()->setActiveCamera(d->camera);
    }
    
    d->camera->setVisibleArea(d->visibleArea);
    d->camera->setDepthRange(d->nearPlane, d->farPlane);
}

void CameraControllerComponent::start()
{
    
}

void CameraControllerComponent::draw(int timeLapse)
{
    Q_UNUSED(timeLapse)
    
    if (d->camera)
        d->camera->setModelviewMatrix(gameObject()->transform().inverted());
}

void CameraControllerComponent::cleanup()
{
    CameraControllerComponentPrivate::activeCamera = 0;
    GluonGraphics::Engine::instance()->setActiveCamera(0);
    
    delete d->camera;
    d->camera = 0;
}

bool CameraControllerComponent::isActive()
{
    return d->active;
}

void CameraControllerComponent::setActive(bool active)
{
    d->active = active;
    if (active && d->camera)
    {
        CameraControllerComponentPrivate::activeCamera = d->camera;
        GluonGraphics::Engine::instance()->setActiveCamera(d->camera);
    }
}

void CameraControllerComponent::setVisibleArea(const QSizeF& area)
{
    d->visibleArea = area;
    
    if(d->camera)
        d->camera->setVisibleArea(d->visibleArea);
}

QSizeF CameraControllerComponent::visibleArea()
{
    return d->visibleArea;
}

float CameraControllerComponent::nearPlane()
{
    return d->nearPlane;
}

float CameraControllerComponent::farPlane()
{
    return d->farPlane;
}

void CameraControllerComponent::setNearPlane(float near)
{
    d->nearPlane = near;
    
    if(d->camera)
        d->camera->setDepthRange(d->nearPlane, d->farPlane);
}

void CameraControllerComponent::setFarPlane(float far)
{
    d->farPlane = far;
    
    if(d->camera)
        d->camera->setDepthRange(d->nearPlane, d->farPlane);
}

Q_EXPORT_PLUGIN2(gluon_component_cameracontroller, GluonEngine::CameraControllerComponent);

#include "cameracontrollercomponent.moc"
