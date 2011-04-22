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

#include "beamrenderercomponent.h"

#include <graphics/item.h>
#include <graphics/engine.h>
#include <graphics/material.h>
#include <graphics/mesh.h>
#include <graphics/materialinstance.h>
#include <graphics/texture.h>

#include <engine/gameobject.h>
#include <engine/asset.h>
#include <engine/game.h>

#include <QtGui/QMatrix4x4>
#include <QtGui/QColor>
#include <QtCore/QMimeData>
#include <QtCore/QVariant>

REGISTER_OBJECTTYPE( GluonEngine, BeamRendererComponent )

using namespace GluonEngine;

class BeamRendererComponent::Private
{
    public:
        Private()
            : baseItem( 0 )
            , beamItem( 0 )
            , tipItem( 0 )
            , baseMaterial( 0 )
            , beamMaterial( 0 )
            , tipMaterial( 0 )
            , size( QSizeF( 1.0f, 1.0f ) )
        {
        }

        void loadMaterial( GluonGraphics::MaterialInstance* material );
        void acquireReleaseMaterial( GluonGraphics::MaterialInstance* acquire, GluonGraphics::MaterialInstance* release );

        GluonGraphics::Item* baseItem;
        GluonGraphics::Item* beamItem;
        GluonGraphics::Item* tipItem;

        GluonGraphics::MaterialInstance* baseMaterial;
        GluonGraphics::MaterialInstance* beamMaterial;
        GluonGraphics::MaterialInstance* tipMaterial;

        QSizeF size;
};

BeamRendererComponent::BeamRendererComponent( QObject* parent )
    : Component( parent ), d( new Private )
{

}

BeamRendererComponent::~BeamRendererComponent()
{
    d->acquireReleaseMaterial( 0, d->baseMaterial );
    d->acquireReleaseMaterial( 0, d->beamMaterial );
    d->acquireReleaseMaterial( 0, d->tipMaterial );
    delete d;
}

QString BeamRendererComponent::category() const
{
    return QString( "Graphics Rendering" );
}

void BeamRendererComponent::initialize()
{
    if( !d->baseItem )
    {
        d->baseItem = GluonGraphics::Engine::instance()->createItem( "default" );
    }
    if( !d->beamItem )
    {
        d->beamItem = GluonGraphics::Engine::instance()->createItem( "default" );
    }
    if( !d->tipItem )
    {
        d->tipItem = GluonGraphics::Engine::instance()->createItem( "default" );
    }


    if( d->baseMaterial )
    {
        d->loadMaterial( d->baseMaterial );
        d->baseItem->setMaterialInstance( d->baseMaterial );
    }

    if( d->beamMaterial )
    {
        d->loadMaterial( d->beamMaterial );
        d->beamItem->setMaterialInstance( d->beamMaterial );
    }

    if( d->tipMaterial )
    {
        d->loadMaterial( d->tipMaterial );
        d->tipItem->setMaterialInstance( d->tipMaterial );
    }
}

void BeamRendererComponent::start()
{
}

void BeamRendererComponent::draw( int /* timeLapse */ )
{
    QMatrix4x4 transform = gameObject()->transform();
    transform.translate( 0, 0, 0.01f );
    transform.scale( d->size.width() / 2, d->size.width() / 2 );
    d->baseItem->setTransform( transform );

    transform = gameObject()->transform();
    transform.translate( 0, d->size.height() / 2 );
    transform.scale( d->size.width() / 2, d->size.height() / 2 );
    d->beamItem->setTransform( transform );

    transform = gameObject()->transform();
    transform.translate( 0, d->size.height(), 0.01f );
    transform.scale( d->size.width() / 2, d->size.width() / 2 );
    d->tipItem->setTransform( transform );
}

void BeamRendererComponent::cleanup()
{
    if( d->baseItem )
    {
        GluonGraphics::Engine::instance()->destroyItem( d->baseItem );
        d->baseItem = 0;
    }

    if( d->beamItem )
    {
        GluonGraphics::Engine::instance()->destroyItem( d->beamItem );
        d->beamItem = 0;
    }

    if( d->tipItem )
    {
        GluonGraphics::Engine::instance()->destroyItem( d->tipItem );
        d->tipItem = 0;
    }
}

void BeamRendererComponent::setSize( const QSizeF& size )
{
    d->size = size;
}

QSizeF BeamRendererComponent::size()
{
    return d->size;
}

GluonGraphics::MaterialInstance*
BeamRendererComponent::baseMaterial()
{
    return d->baseMaterial;
}

void BeamRendererComponent::setBaseMaterial( GluonGraphics::MaterialInstance* material )
{
    d->acquireReleaseMaterial( material, d->baseMaterial );
    d->baseMaterial = material;

    if( d->baseItem )
        d->baseItem->setMaterialInstance( material );
}

void BeamRendererComponent::setBaseMaterial( const QString& path )
{
    setBaseMaterial( qobject_cast<GluonGraphics::MaterialInstance*>( Game::instance()->gameProject()->findItemByName( path ) ) );
}

GluonGraphics::MaterialInstance*
BeamRendererComponent::beamMaterial()
{
    return d->beamMaterial;
}

void BeamRendererComponent::setBeamMaterial( GluonGraphics::MaterialInstance* material )
{
    d->acquireReleaseMaterial( material, d->beamMaterial );
    d->beamMaterial = material;

    if( d->beamItem )
        d->beamItem->setMaterialInstance( material );
}

void BeamRendererComponent::setBeamMaterial( const QString& path )
{
    setBeamMaterial( qobject_cast<GluonGraphics::MaterialInstance*>( Game::instance()->gameProject()->findItemByName( path ) ) );
}

GluonGraphics::MaterialInstance*
BeamRendererComponent::tipMaterial()
{
    return d->tipMaterial;
}

void BeamRendererComponent::setTipMaterial( GluonGraphics::MaterialInstance* material )
{
    d->acquireReleaseMaterial( material, d->tipMaterial );
    d->tipMaterial = material;

    if( d->tipItem )
        d->tipItem->setMaterialInstance( material );
}

void BeamRendererComponent::setTipMaterial( const QString& path )
{
    setTipMaterial( qobject_cast<GluonGraphics::MaterialInstance*>( Game::instance()->gameProject()->findItemByName( path ) ) );
}

void BeamRendererComponent::Private::loadMaterial( GluonGraphics::MaterialInstance* material )
{
    Asset* materialAsset = qobject_cast<Asset*>( material->parent() );
    if( materialAsset )
        materialAsset->load();

    Asset* texture = Game::instance()->gameProject()->findChild<Asset*>( material->property( "texture0" ).toString() );
    if( texture )
        texture->load();
}

void BeamRendererComponent::Private::acquireReleaseMaterial( GluonGraphics::MaterialInstance* acquire, GluonGraphics::MaterialInstance* release )
{
    if( release )
    {
        release->deref();
        Asset* materialAsset = qobject_cast<Asset*>( release->parent() );
        if( materialAsset )
            materialAsset->deref();
    }
    if( acquire )
    {
        acquire->ref();
        Asset* materialAsset = qobject_cast<Asset*>( acquire->parent() );
        if( materialAsset )
            materialAsset->ref();
    }
}

Q_EXPORT_PLUGIN2( gluon_component_beamrenderer, GluonEngine::BeamRendererComponent )

#include "beamrenderercomponent.moc"
