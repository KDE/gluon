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

#include <engine/gameobject.h>
#include <engine/asset.h>
#include <engine/game.h>

#include <graphics/manager.h>
#include <graphics/entity.h>
#include <graphics/material.h>
#include <graphics/spritemesh.h>
#include <graphics/materialinstance.h>
#include <graphics/texture.h>
#include <graphics/mesh.h>

#include <QtGui/QMatrix4x4>
#include <QtGui/QColor>
#include <graphics/world.h>

REGISTER_OBJECTTYPE( GluonEngine, SpriteRendererComponent )

using namespace GluonEngine;

class SpriteRendererComponent::SpriteRendererComponentPrivate
{
    public:
        SpriteRendererComponentPrivate() : entity( 0 ), texture( 0 ), material( 0 ), size( QSizeF( 1.0f, 1.0f ) )
        {
        }

        GluonGraphics::Entity* entity;
        GluonEngine::Asset* texture;
        GluonGraphics::MaterialInstance* material;

        QSizeF size;
};

SpriteRendererComponent::SpriteRendererComponent( QObject* parent )
    : Component( parent )
    , d( new SpriteRendererComponentPrivate )
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
    delete d;
}

QString SpriteRendererComponent::category() const
{
    return QString( "Graphics Rendering" );
}

void SpriteRendererComponent::initialize()
{
    if( !d->entity )
    {
        d->entity = GluonGraphics::Manager::instance()->currentWorld()->createEntity< GluonGraphics::Entity >();
        d->entity->setMesh( GluonGraphics::Manager::instance()->resource< GluonGraphics::SpriteMesh >( GluonGraphics::Manager::Defaults::SpriteMesh ) );
        d->entity->setVisible( enabled() );
    }

    if( d->material )
    {
        Asset* materialAsset = qobject_cast<Asset*>( d->material->parent() );
        if( materialAsset )
            materialAsset->load();

        Asset* texture = 0;
        if( d->material->property( "texture0" ).type() == QVariant::String )
        {
            QString theName( d->material->property( "texture0" ).toString() );
            texture = gameProject()->findChild<Asset*>( theName );
            if( !texture )
                debug( QString( "Texture failed to load - attempted to load texture named %1 (searched for %2)" ).arg( theName ).arg( theName ) );
        }
        else
            texture = qobject_cast<Asset*>( GluonCore::GluonObjectFactory::instance()->wrappedObject( d->material->property( "texture0" ) ) );

        if( texture )
            texture->load();

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
        QMatrix4x4 transform = gameObject()->transform();
        transform.scale( d->size.width(), d->size.height() );
        d->entity->setTransform( transform );
    }
}

void SpriteRendererComponent::cleanup()
{
    if( d->entity )
    {
        GluonGraphics::Manager::instance()->currentWorld()->destroyEntity( d->entity );
        d->entity = 0;
    }
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
            d->entity->setMaterialInstance( GluonGraphics::Manager::instance()->resource< GluonGraphics::Material >( "default" )->instance( "default" ) );
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

Q_EXPORT_PLUGIN2( gluon_component_spriterenderer, GluonEngine::SpriteRendererComponent );

#include "spriterenderercomponent.moc"
