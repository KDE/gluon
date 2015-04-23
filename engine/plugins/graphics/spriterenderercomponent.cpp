/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010-2012 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "spriterenderercomponent.h"

// #include <QtCore/qmath.h>
#include <QtGui/QColor>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <core/axisalignedbox.h>
#include <core/resourcemanager.h>

#include <graphics/defaults.h>
#include <graphics/entity.h>
#include <graphics/material.h>
#include <graphics/spritemesh.h>
#include <graphics/materialinstance.h>
#include <graphics/texture.h>
#include <graphics/mesh.h>
#include <graphics/world.h>

#include <engine/gameobject.h>
#include <engine/asset.h>
#include <engine/game.h>

REGISTER_OBJECTTYPE( GluonEngine, SpriteRendererComponent )

using namespace GluonEngine;

class SpriteRendererComponent::Private
{
    public:
        Private() : size( QSizeF( 1.0f, 1.0f ) )
        {
        }

        GluonGraphics::Entity* entity = nullptr;
        GluonEngine::Asset* texture = nullptr;
        GluonGraphics::MaterialInstance* material = nullptr;

        QSizeF size;
};

SpriteRendererComponent::SpriteRendererComponent( QObject* parent )
    : Component( parent )
{

}

SpriteRendererComponent::~SpriteRendererComponent()
{
    if( d->material )
    {
        d->material->deref();
        Asset* materialAsset = qobject_cast<Asset*>( d->material->parent() );
        if( materialAsset )
            materialAsset->deref();
    }
}

void SpriteRendererComponent::initialize()
{
    if( !d->entity )
    {
        d->entity = GluonCore::ResourceManager::instance()->resource< GluonGraphics::World >( GluonGraphics::Defaults::World )->createEntity< GluonGraphics::Entity >();
        d->entity->setMesh( GluonCore::ResourceManager::instance()->resource< GluonGraphics::SpriteMesh >( GluonGraphics::Defaults::SpriteMesh ) );
        d->entity->setVisible( false );
    }

    if( d->material )
    {
        Asset* materialAsset = qobject_cast< Asset* >( d->material->parent() );
        if( materialAsset )
            materialAsset->load();

        Asset* texture = 0;
        if( d->material->property( "texture0" ).type() == QVariant::String )
        {
            QString theName( d->material->property( "texture0" ).toString() );
            texture = gameProject()->findChild< Asset* >( theName );
        }
        else
            texture = d->material->property( "texture0" ).value< Asset* >();

        d->entity->setMaterialInstance( d->material );
    }
}

void SpriteRendererComponent::start()
{
}

void SpriteRendererComponent::draw( int /* timeLapse */ )
{
    if( d->entity )
    {
        if( !d->entity->isVisible() )
            d->entity->setVisible( true );

        Eigen::Affine3f transform = gameObject()->transform();
        transform.scale( Eigen::Vector3f(d->size.width(), d->size.height(), 1) );
        d->entity->setTransform( transform );
    }
}

void SpriteRendererComponent::cleanup()
{
    if( d->entity )
    {
        d->entity->world()->destroyEntity( d->entity );
        d->entity = 0;
    }
}

GluonCore::AxisAlignedBox
SpriteRendererComponent::boundingBox()
{
    Eigen::Vector3f sizeVector( size().width(), size().height(), 0 );
    return GluonCore::AxisAlignedBox( transformationCenter(), sizeVector );
}

void SpriteRendererComponent::setSize( const QSizeF& size )
{
    d->size = size;
}

QSizeF SpriteRendererComponent::size()
{
    return d->size;
}

GluonGraphics::MaterialInstance*
SpriteRendererComponent::material()
{
    return d->material;
}

void SpriteRendererComponent::setMaterial( GluonGraphics::MaterialInstance* material )
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

    if( d->entity )
    {
        if( material )
        {
            d->entity->setMaterialInstance( material );
        }
        else
        {
            d->entity->setMaterialInstance( GluonCore::ResourceManager::instance()->resource< GluonGraphics::Material >( GluonGraphics::Defaults::Material )->instance( GluonGraphics::Defaults::MaterialInstance ) );
        }
    }
}

void SpriteRendererComponent::setMaterial( const QString& path )
{
    setMaterial( qobject_cast<GluonGraphics::MaterialInstance*>( Game::instance()->gameProject()->findGlobalItemByName( path ) ) );
}

void SpriteRendererComponent::setEnabled( bool newEnabled )
{
    if( d->entity )
        d->entity->setVisible( newEnabled );

    GluonEngine::Component::setEnabled( newEnabled );
}
