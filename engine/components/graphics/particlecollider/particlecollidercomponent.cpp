/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Laszlo Papp <djszapi@archlinux.us>
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

#include "particlecollidercomponent.h"

#include <texture.h>
#include <game.h>

#include "graphics/item.h"
#include "graphics/engine.h"
#include "graphics/material.h"
#include "graphics/mesh.h"
#include "graphics/materialinstance.h"
#include "engine/gameobject.h"
#include "engine/asset.h"

#include <QtGui/QMatrix4x4>
#include <QtGui/QColor>
#include <QtCore/QMimeData>
#include <QtCore/QVariant>

REGISTER_OBJECTTYPE( GluonEngine, ParticleColliderComponent )

using namespace GluonEngine;

class ParticleColliderComponent::Private
{
    public:
        Private()
            : item( 0 )
            , material( 0 )
            , color( 255, 255, 255 )
            , size( 1.0f, 1.0f )
            , bounceFactor( 0 )
            , collisionEnergyLoss( 0 )
            , minKillVelocity( 0 )
            , collidesWith( "" )
            , sendCollisionMessage( false )
        {
        }

        GluonGraphics::Item* item;
        GluonGraphics::MaterialInstance* material;

        QColor color;
        QSizeF size;

        float bounceFactor;
        int collisionEnergyLoss;
        int minKillVelocity;
        QString collidesWith;
        bool sendCollisionMessage;
};

ParticleColliderComponent::ParticleColliderComponent( QObject* parent )
    : Component( parent )
    , d( new Private )
{
}

ParticleColliderComponent::ParticleColliderComponent( const ParticleColliderComponent& other )
    : Component( other )
    , d( other.d )
{
}

ParticleColliderComponent::~ParticleColliderComponent()
{
    delete d;
}

QString ParticleColliderComponent::category() const
{
    return QString( "Graphics Particle" );
}

void ParticleColliderComponent::initialize()
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
            if(!texture)
                debug( QString( "Texture failed to load - attempted to load texture named %1 (searched for %2)" ).arg( theName ).arg( theObjectName ) );
        }
        else
            texture = qobject_cast<Asset*>( GluonCore::GluonObjectFactory::instance()->wrappedObject( d->material->property( "texture0" ) ) );

        if( texture )
            texture->load();
        d->item->setMaterialInstance( d->material );
    }
}

void ParticleColliderComponent::start()
{
}

void ParticleColliderComponent::draw( int /* timeLapse */ )
{
    if( d->item )
    {
        QMatrix4x4 transform = gameObject()->transform();
        transform.scale( d->size.width() / 2, d->size.height() / 2 );
        d->item->setTransform( transform );
    }
}

void ParticleColliderComponent::cleanup()
{
    if( d->item )
    {
        GluonGraphics::Engine::instance()->destroyItem( d->item );
        d->item = 0;
    }
}

float ParticleColliderComponent::bounceFactor() const
{
    return d->bounceFactor;
}

void ParticleColliderComponent::setBounceFactor( float bounceFactor )
{
    d->bounceFactor = bounceFactor;
}

int ParticleColliderComponent::collisionEnergyLoss() const
{
    return d->collisionEnergyLoss;
}

void ParticleColliderComponent::setCollisionEnergyLoss( int collisionEnergyLoss )
{
    d->collisionEnergyLoss = collisionEnergyLoss;
}

int ParticleColliderComponent::minKillVelocity() const
{
    return d->minKillVelocity;
}

void ParticleColliderComponent::setMinKillVelocity( int minKillVelocity )
{
    d->minKillVelocity = minKillVelocity;
}

QString ParticleColliderComponent::collidesWith() const
{
    return d->collidesWith;
}

void ParticleColliderComponent::setCollidesWith( const QString& collidesWith )
{
    d->collidesWith = collidesWith;
}

bool ParticleColliderComponent::sendCollisionMessage() const
{
    return d->sendCollisionMessage;
}

void ParticleColliderComponent::setSendCollisionMessage( bool sendCollisionMessage )
{
    d->sendCollisionMessage = sendCollisionMessage;
}

Q_EXPORT_PLUGIN2( gluon_component_particlecollider, GluonEngine::ParticleColliderComponent );

#include "particlecollidercomponent.moc"
