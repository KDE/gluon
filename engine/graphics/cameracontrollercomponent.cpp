/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 - 2012 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include <QtCore/QSizeF>

#include <core/resourcemanager.h>
#include <graphics/camera.h>
#include <graphics/rendertarget.h>
#include <graphics/materialinstance.h>
#include <graphics/material.h>
#include <graphics/world.h>
#include <graphics/defaults.h>

#include <engine/gameobject.h>
#include <engine/asset.h>

REGISTER_OBJECTTYPE( GluonEngine, CameraControllerComponent )

using namespace GluonEngine;

class CameraControllerComponent::Private
{
    public:
        Private() : visibleArea( QSizeF( 100.0f, 100.0f ) )
        {
        }

        GluonGraphics::RenderTarget* renderTarget = nullptr;
        GluonGraphics::Camera* camera = nullptr;
        GluonGraphics::MaterialInstance* material = nullptr;
        bool active = false;

        QSizeF visibleArea;
        float nearPlane = 1.0f;
        float farPlane = 100.0f;
};

CameraControllerComponent::CameraControllerComponent( QObject* parent )
    : Component( parent )
{

}

CameraControllerComponent::~CameraControllerComponent()
{
    if( d->material )
    {
        d->material->deref();
        Asset* materialAsset = qobject_cast<Asset*>( d->material->parent() );
        if( materialAsset )
            materialAsset->deref();
    }
}

void CameraControllerComponent::initialize()
{
    if( !d->camera )
        d->camera = GluonCore::ResourceManager::instance()->resource< GluonGraphics::World >( GluonGraphics::Defaults::World )->createEntity< GluonGraphics::Camera >();

    d->renderTarget = GluonCore::ResourceManager::instance()->resource< GluonGraphics::RenderTarget >( GluonGraphics::Defaults::RenderTarget );
    if( d->active )
    {
        d->renderTarget->addChild( d->camera );
    }

    d->camera->setVisibleArea( d->visibleArea );
    d->camera->setNearPlane( d->nearPlane );
    d->camera->setFarPlane( d->farPlane );

//     if( !d->material )
//     {
//         d->material = GluonGraphics::Engine::instance()->mainRenderTarget()->materialInstance();
//     }
//     else
//     {
//         Asset* materialAsset = qobject_cast<Asset*>( d->material->parent() );
//         if( materialAsset )
//             materialAsset->load();
//         if( GluonGraphics::Engine::instance()->mainRenderTarget() )
//             GluonGraphics::Engine::instance()->mainRenderTarget()->setMaterialInstance( d->material );
//         else
//             debug( QString( "Warning: there is no main RenderTarget set!" ) );
//     }

//     d->camera->frustrum()->setOrthoAdjusted( d->visibleArea, GluonGraphics::Manager::instance()->currentViewport()->aspectRatio(), d->nearPlane, d->farPlane );
}

void CameraControllerComponent::start()
{
}

void CameraControllerComponent::draw( int /* timeLapse */ )
{
    if( d->camera )
        d->camera->setTransform( gameObject()->transform() );
}

void CameraControllerComponent::cleanup()
{
    d->renderTarget->removeChild( d->camera );
    d->camera->world()->destroyEntity( d->camera );
    d->camera = 0;
}

bool CameraControllerComponent::isActive()
{
    return d->active;
}

void CameraControllerComponent::setActive( bool active )
{
    if( d->active && d->camera )
        d->renderTarget->removeChild( d->camera );

    d->active = active;
    if( active && d->camera )
    {
        d->renderTarget->addChild( d->camera );
    }
}

void CameraControllerComponent::setVisibleArea( const QSizeF& area )
{
    d->visibleArea = area;

    if( d->camera )
        d->camera->setVisibleArea( area );
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

GluonGraphics::MaterialInstance* CameraControllerComponent::renderTargetMaterial()
{
    return d->material;
}

void CameraControllerComponent::setNearPlane( float nearValue )
{
    d->nearPlane = nearValue;

    if( d->camera )
        d->camera->setNearPlane( nearValue );
}

void CameraControllerComponent::setFarPlane( float farValue )
{
    d->farPlane = farValue;

    if( d->camera )
        d->camera->setFarPlane( farValue );
}

void CameraControllerComponent::setRenderTargetMaterial( GluonGraphics::MaterialInstance* material )
{
    if( d->material )
    {
        d->material->deref();
        Asset* materialAsset = qobject_cast<Asset*>( d->material->parent() );
        if( materialAsset )
            materialAsset->deref();
    }
    d->material = material;
    if( d->material )
    {
        d->material->ref();
        Asset* materialAsset = qobject_cast<Asset*>( d->material->parent() );
        if( materialAsset )
            materialAsset->ref();
    }
}
