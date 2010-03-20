/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
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
            active = false;
        }

        GluonGraphics::Camera *camera;
        bool active;

        static GluonGraphics::Camera *activeCamera;
};

GluonGraphics::Camera* CameraControllerComponent::CameraControllerComponentPrivate::activeCamera = 0;

CameraControllerComponent::CameraControllerComponent(QObject* parent) : Component(parent)
{
    d = new CameraControllerComponentPrivate;
}

CameraControllerComponent::CameraControllerComponent(const CameraControllerComponent& other)
        : Component(other),
        d(other.d)
{
}

CameraControllerComponent::~CameraControllerComponent()
{
    delete d->camera;
    delete d;
}

void CameraControllerComponent::start()
{
    if (!d->camera)
        d->camera = new GluonGraphics::Camera();

    if (d->active)
        GluonGraphics::Engine::instance()->setActiveCamera(d->camera);
}

void CameraControllerComponent::draw(int timeLapse)
{
    Q_UNUSED(timeLapse)

#warning TODO: Set rotation/fov/all that crap
    if (d->camera)
        d->camera->setPosition(gameObject()->position());
}

void CameraControllerComponent::update(int elapsedMilliseconds)
{
    Q_UNUSED(elapsedMilliseconds)
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

Q_EXPORT_PLUGIN2(gluon_component_cameracontroller, GluonEngine::CameraControllerComponent);

#include "cameracontrollercomponent.moc"
