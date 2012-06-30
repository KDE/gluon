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

#include <graphics/manager.h>
#include <graphics/camera.h>
#include <graphics/frustrum.h>
#include <graphics/viewport.h>
#include <graphics/rendertarget.h>
#include <graphics/materialinstance.h>
#include <graphics/material.h>

#include <engine/gameobject.h>
#include <engine/asset.h>

#include <QtGui/QMatrix4x4>
#include <QtCore/QSizeF>
#include <graphics/world.h>

REGISTER_OBJECTTYPE( GluonEngine, CameraControllerComponent )

using namespace GluonEngine;

class CameraControllerComponent::CameraControllerComponentPrivate
{
    public:
        CameraControllerComponentPrivate()
            : camera( 0 )
            , active( true )
            , visibleArea( QSizeF( 100.0f, 100.0f ) )
            , nearPlane( 1.0f )
            , farPlane( 100.0f )
            , material( 0 )
        {
        }

        GluonGraphics::Camera* camera;
        bool active;

        QSizeF visibleArea;
        float nearPlane;
        float farPlane;

        GluonGraphics::MaterialInstance* material;

        static GluonGraphics::Camera* activeCamera;
};

GluonGraphics::Camera* CameraControllerComponent::CameraControllerComponentPrivate::activeCamera = 0;

CameraControllerComponent::CameraControllerComponent( QObject* parent )
    : Component( parent )
    , d( new CameraControllerComponentPrivate )
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
    delete d;
}

QString CameraControllerComponent::category() const
{
    return QString( "Graphics " );
}

void CameraControllerComponent::initialize()
{
    if( !d->camera )
        d->camera = GluonGraphics::Manager::instance()->currentWorld()->createEntity< GluonGraphics::Camera >();

    GluonGraphics::RenderTarget* rt = GluonGraphics::Manager::instance()->resource< GluonGraphics::RenderTarget >( GluonGraphics::Manager::Defaults::RenderTarget );
    if( d->active )
    {
        rt->addChild( d->camera );
    }

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
        d->camera->setTransform( gameObject()->transform().inverted() );
}

void CameraControllerComponent::cleanup()
{
    CameraControllerComponentPrivate::activeCamera = 0;
    GluonGraphics::Manager::instance()->resource< GluonGraphics::RenderTarget >( GluonGraphics::Manager::Defaults::RenderTarget )->removeChild( d->camera );

    GluonGraphics::Manager::instance()->currentWorld()->destroyEntity( d->camera );
    d->camera = 0;
}

bool CameraControllerComponent::isActive()
{
    return d->active;
}

void CameraControllerComponent::setActive( bool active )
{
    if( d->active && d->camera )
        GluonGraphics::Manager::instance()->resource< GluonGraphics::RenderTarget >( GluonGraphics::Manager::Defaults::RenderTarget )->removeChild( d->camera );

    d->active = active;
    if( active && d->camera )
    {
        CameraControllerComponentPrivate::activeCamera = d->camera;
        GluonGraphics::Manager::instance()->resource< GluonGraphics::RenderTarget >( GluonGraphics::Manager::Defaults::RenderTarget )->addChild( d->camera );
//         GluonGraphics::Engine::instance()->setActiveCamera( d->camera );
    }
}

void CameraControllerComponent::setVisibleArea( const QSizeF& area )
{
    d->visibleArea = area;

//     if( d->camera )
//         d->camera->frustrum()->setOrthoAdjusted( d->visibleArea, GluonGraphics::Engine::instance()->currentViewport()->aspectRatio(), d->nearPlane, d->farPlane );
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

//     if( d->camera )
//         d->camera->frustrum()->setOrthoAdjusted( d->visibleArea, GluonGraphics::Engine::instance()->currentViewport()->aspectRatio(), d->nearPlane, d->farPlane );
}

void CameraControllerComponent::setFarPlane( float farValue )
{
    d->farPlane = farValue;

//     if( d->camera )
//         d->camera->frustrum()->setOrthoAdjusted( d->visibleArea, GluonGraphics::Engine::instance()->currentViewport()->aspectRatio(), d->nearPlane, d->farPlane );
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

//     GluonGraphics::RenderTarget* target = GluonGraphics::Engine::instance()->mainRenderTarget();
//     if( target )
//     {
//         if( material )
//         {
//             target->setMaterialInstance( material );
//         }
//         else
//         {
//             target->setMaterialInstance( GluonGraphics::Engine::instance()->material( "default" )->createInstance( fullyQualifiedName() ) );
//         }
//     }
}

Q_EXPORT_PLUGIN2( gluon_component_cameracontroller, GluonEngine::CameraControllerComponent );

#include "cameracontrollercomponent.moc"
