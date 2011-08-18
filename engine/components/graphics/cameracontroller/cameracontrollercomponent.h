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

#ifndef GLUON_ENGINE_CAMERACONTROLLERCOMPONENT_H
#define GLUON_ENGINE_CAMERACONTROLLERCOMPONENT_H

#include <engine/component.h>

namespace GluonGraphics
{
    class MaterialInstance;
}

class QSizeF;
namespace GluonEngine
{
    class GLUON_COMPONENT_CAMERACONTROLLER_EXPORT CameraControllerComponent : public Component
    {
            Q_OBJECT
            Q_INTERFACES( GluonEngine::Component )
            GLUON_OBJECT( GluonEngine::CameraControllerComponent )

            Q_PROPERTY( bool active READ isActive WRITE setActive )
            Q_PROPERTY( QSizeF visibleArea READ visibleArea WRITE setVisibleArea )
            Q_PROPERTY( float nearPlane READ nearPlane WRITE setNearPlane )
            Q_PROPERTY( float farPlane READ farPlane WRITE setFarPlane )
            Q_PROPERTY( GluonGraphics::MaterialInstance* renderTargetMaterial READ renderTargetMaterial WRITE setRenderTargetMaterial )

            Q_CLASSINFO( "org.gluon.category", "Graphics Rendering" )
            Q_CLASSINFO( "org.gluon.icon", "image-x-generic" )

        public:
            Q_INVOKABLE CameraControllerComponent( QObject* parent = 0 );
            virtual ~CameraControllerComponent();
            virtual QString category() const;

            virtual void initialize();
            virtual void start();
            virtual void draw( int timeLapse = 0 );
            virtual void cleanup();

            virtual bool isActive();
            virtual QSizeF visibleArea();
            virtual float nearPlane();
            virtual float farPlane();
            virtual GluonGraphics::MaterialInstance* renderTargetMaterial();

        public Q_SLOTS:
            virtual void setActive( bool active );
            virtual void setVisibleArea( const QSizeF& area );
            virtual void setNearPlane( float nearValue );
            virtual void setFarPlane( float farValue );
            virtual void setRenderTargetMaterial( GluonGraphics::MaterialInstance* material );

        private:
            class CameraControllerComponentPrivate;
            CameraControllerComponentPrivate* const d;
    };

}

Q_DECLARE_METATYPE( GluonEngine::CameraControllerComponent* )

#endif // GLUON_ENGINE_SPRITERENDERERCOMPONENT_H
