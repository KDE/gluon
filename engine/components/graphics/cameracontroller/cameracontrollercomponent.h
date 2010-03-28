/******************************************************************************
 * This file is part of the Gluon Development Platform
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

#ifndef GLUON_ENGINE_SPRITERENDERERCOMPONENT_H
#define GLUON_ENGINE_SPRITERENDERERCOMPONENT_H

#include <engine/gluon_engine_export.h>
#include <engine/component.h>

namespace GluonEngine
{
    class GLUON_ENGINE_EXPORT CameraControllerComponent : public Component
    {
            Q_OBJECT
            GLUON_OBJECT(GluonEngine::CameraControllerComponent)
            Q_PROPERTY(bool active READ isActive WRITE setActive)
            Q_INTERFACES(GluonEngine::Component)

        public:
            CameraControllerComponent(QObject* parent = 0);
            CameraControllerComponent(const CameraControllerComponent& other);
            virtual ~CameraControllerComponent();

            virtual void start();
            virtual void update(int elapsedMilliseconds);
            virtual void draw(int timeLapse = 0);

            virtual bool isActive();

        public slots:
            virtual void setActive(bool active);

        private:
            class CameraControllerComponentPrivate;
            CameraControllerComponentPrivate *d;
    };

}

Q_DECLARE_METATYPE(GluonEngine::CameraControllerComponent)
Q_DECLARE_METATYPE(GluonEngine::CameraControllerComponent*)

#endif // GLUON_ENGINE_SPRITERENDERERCOMPONENT_H
