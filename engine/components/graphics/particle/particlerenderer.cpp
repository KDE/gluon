/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Laszlo Papp <lpapp@kde.org>
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

#include "particlerenderer.h"

#include <texture.h>
#include <game.h>

#include "engine/gameobject.h"
#include "engine/asset.h"

#include <graphics/item.h>
#include <graphics/engine.h>
#include <graphics/material.h>
#include <graphics/mesh.h>
#include <graphics/materialinstance.h>

#include <QtGui/QMatrix4x4>
#include <QtGui/QColor>
#include <QtCore/QMimeData>
#include <QtCore/QVariant>

REGISTER_OBJECTTYPE( GluonEngine, ParticleRendererComponent )

using namespace GluonEngine;

class ParticleRendererComponent::ParticleRendererComponentPrivate
{
    public:
        ParticleRendererComponentPrivate()
            : item( 0 )
            , texture( 0 )
            , material( 0 )
            , castShadows( true )
            , receiveShadows( true )
            , size( QSizeF( 1.0f, 1.0f ) )
            , color.setRgb( ( 255, 255, 255 ) )
            , cameraVelocityScale( 0 )
            , stretchParticles( Billboard )
            , lengthScale( 0 )
            , velocityScale( 0 )
            , uvAnimationXTile( 0 )
            , uvAnimationYTile( 0 )
            , uvAnimationCycles( 0 )
        {
        }

        GluonGraphics::Item* item;
        GluonGraphics::MaterialInstance* material;

        bool castShadows;
        bool receiveShadows;

        QColor color;
        QSizeF size;

        int cameraVelocityScale;
        StretchParticles stretchParticles;
        int lengthScale;
        int velocityScale;
        int uvAnimationXTile;
        int uvAnimationYTile;
        int uvAnimationCycles;
};

ParticleRendererComponent::ParticleRendererComponent( QObject* parent )
    : Component( parent )
    , d( new ParticleRendererComponentPrivate )
{

}

ParticleRendererComponent::~ParticleRendererComponent()
{
    delete d;
}

QString ParticleRendererComponent::category() const
{
    return QString( "Graphics Rendering" );
}

void ParticleRendererComponent::initialize()
{
    if( !d->item )
    {
        d->item = GluonGraphics::Engine::instance()->createItem( "default" );
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
            QString theObjectName = GluonObject::nameToObjectName( theName );
            texture = gameProject()->findChild<Asset*>( theObjectName );
            if( !texture )
                debug( QString( "Texture failed to load - attempted to load texture named %1 (searched for %2)" ).arg( theName ).arg( theObjectName ) );
        }
        else
            texture = qobject_cast<Asset*>( GluonCore::GluonObjectFactory::instance()->wrappedObject( d->material->property( "texture0" ) ) );

        if( texture )
            texture->load();
        d->item->setMaterialInstance( d->material );
    }
}

void ParticleRendererComponent::start()
{
}

void ParticleRendererComponent::draw( int /* timeLapse */ )
{
    if( d->item )
    {
        QMatrix4x4 transform = gameObject()->transform();
        transform.scale( d->size.width() / 2, d->size.height() / 2 );
        d->item->setTransform( transform );
    }
}

void ParticleRendererComponent::cleanup()
{
    if( d->item )
    {
        GluonGraphics::Engine::instance()->destroyItem( d->item );
        d->item = 0;
    }
}

void ParticleRendererComponent::setSize( const QSizeF& size )
{
    d->size = size;
}

QSizeF ParticleRendererComponent::size()
{
    return d->size;
}

GluonGraphics::MaterialInstance*
ParticleRendererComponent::material()
{
    return d->material;
}

void ParticleRendererComponent::setMaterial( GluonGraphics::MaterialInstance* material )
{
    d->material = material;

    if( d->item )
    {
        if( material )
        {
            d->item->setMaterialInstance( material );
        }
        else
        {
            d->item->setMaterialInstance( GluonGraphics::Engine::instance()->material( "default" )->instance( "default" ) );
        }
    }
}

void ParticleRendererComponent::setMaterial( const QString& path )
{
    setMaterial( qobject_cast<GluonGraphics::MaterialInstance*>( Game::instance()->gameProject()->findGlobalItemByName( path ) ) );
}

int cameraVelocityScale()
{
    return cameraVelocityScale;
}

void setCameraVelocity( int cameraVelocity )
{
    d->cameraVelocity = cameraVelocity;
}

StretchParticles stretchParticles()
{
    return stretchParticles;
}

void setStretchParticles( StretchParticles stretchParticles )
{
    d->stretchParticles = stretchParticles;
}

int lengthScale()
{
    return lengthScale;
}

void setLengthScale( int lengthScale )
{
    d->lengthScale = lengthScale;
}

int velocityScale()
{
    return velocityScale;
}

void setVelocityScale( int velocityScale )
{
    d->velocityScale = velocityScale;
}

int uvAnimationXTile()
{
    return uvAnimationXTile;
}

void setUVAnimationXTile( int uvAnimationXTile )
{
    d->uvAnimationXTile = uvAnimationXTile;
}

int uvAnimationYTile()
{
    return uvAnimationYTile;
}

void setUVAnimationYTile( int uvAnimationYTile )
{
    d->uvAnimationYTile = uvAnimationYTile;
}

int uvAnimationCycles()
{
    return uvAnimationCycles;
}

void setUVAnimationCycles( int uvAnimationCycles )
{
    d->uvAnimationCycles = uvAnimationCycles;
}

Q_EXPORT_PLUGIN2( gluon_component_particlerenderer, GluonEngine::ParticleRendererComponent );

#include "particlerenderer.moc"
