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

#include "animatedspriterenderercomponent.h"

#include <graphics/item.h>
#include <graphics/engine.h>
#include <graphics/material.h>
#include <graphics/mesh.h>
#include <graphics/materialinstance.h>
#include <graphics/texture.h>
#include <engine/gameobject.h>
#include <engine/asset.h>
#include <engine/game.h>

#include <QtCore/QMimeData>
#include <QtCore/QVariant>
#include <QtGui/QMatrix4x4>
#include <QtGui/QColor>

REGISTER_OBJECTTYPE( GluonEngine, AnimatedSpriteRendererComponent )

using namespace GluonEngine;

class AnimatedSpriteRendererComponent::Private
{
    public:
        Private()
            : item( 0 )
            , material( 0 )
            , localInstance( 0 )
            , color( QColor( 255, 255, 255 ) )
            , size( QSizeF( 1.0f, 1.0f ) )
            , animating( true )
            , looping( true )
            , playing( true )
            , currentAnimation( 0 )
            , direction( 0 )
            , frameRate( 25 )
            //textureCount = 1;
            , currentTime( 1000 / frameRate )
            , currentFrame( 0.0 )

            , frameSize( QSizeF( 64.f, 64.f ) )
            , textureSize( QSizeF( 1024.f, 1024.f ) )

            , frameWidthUV( 0.0625 )
            , frameHeightUV( 0.0625 )

            , frameCounts( QList<int>() << 1 )
            , startFrames( QList<int>() << 0 )
        {
        }

        GluonGraphics::Item* item;
        GluonGraphics::MaterialInstance* material;
        GluonGraphics::MaterialInstance* localInstance;

        QColor color;
        QSizeF size;

        bool animating;
        bool looping;
        bool playing;

        int currentAnimation;
        int direction;
        int frameRate;
        //int textureCount;

        int currentTime;
        float currentFrame;
        int currentMaxFrame;

        QSizeF frameSize;
        QSizeF textureSize;

        float frameWidthUV;
        float frameHeightUV;

        QList<int> frameCounts;
        QList<int> startFrames;
};

AnimatedSpriteRendererComponent::AnimatedSpriteRendererComponent( QObject* parent )
    : Component( parent )
    , d( new Private )
{

}

AnimatedSpriteRendererComponent::~AnimatedSpriteRendererComponent()
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

QString AnimatedSpriteRendererComponent::category() const
{
    return QString( "Graphics Rendering" );
}

void AnimatedSpriteRendererComponent::initialize()
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
        }
        else
        {
            texture = qobject_cast<Asset*>( GluonCore::GluonObjectFactory::instance()->wrappedObject( d->material->property( "texture0" ) ) );
        }

        if( texture )
        {
            texture->load();
            d->textureSize = GluonGraphics::Engine::instance()->texture( texture->data()->text() )->image().size();
            d->frameWidthUV = d->frameSize.width() / d->textureSize.width();
            d->frameHeightUV = d->frameSize.height() / d->textureSize.height();
        }

        d->item->setMaterialInstance( d->material );
    }
}

void AnimatedSpriteRendererComponent::start()
{
    if( d->material )
    {
        d->localInstance = new GluonGraphics::MaterialInstance();
        d->localInstance->setMaterial( d->material->material() );
        QList<QByteArray> propertyNames = d->material->dynamicPropertyNames();
        foreach( const QByteArray & name, propertyNames )
        {
            d->localInstance->setProperty( name, d->material->property( name ) );
        }
        d->item->setMaterialInstance( d->localInstance );
    }
}

void AnimatedSpriteRendererComponent::update( int elapsedMilliseconds )
{
    if( d->animating && d->playing )
    {
        d->currentFrame += d->frameRate / ( 1000.f / elapsedMilliseconds );
        if( d->currentFrame > d->currentMaxFrame )
        {
            if( d->looping )
            {
                d->currentFrame = d->startFrames.at( d->currentAnimation );
            }
            else
            {
                d->playing = false;
            }
        }
    }
}

void AnimatedSpriteRendererComponent::draw( int /* timeLapse */ )
{
    if( d->item )
    {
        QMatrix4x4 transform = gameObject()->transform();
        transform.scale( d->size.width() / 2, d->size.height() / 2 );
        d->item->setTransform( transform );

        if( d->animating && d->playing )
        {
            QVector4D frame;
            frame.setX( d->frameWidthUV * int( d->currentFrame ) );
            frame.setY( d->frameHeightUV * d->direction );
            frame.setZ( d->frameWidthUV );
            frame.setW( d->frameHeightUV );
            if( d->localInstance )
                d->localInstance->setProperty( "frame", frame );
        }
    }
}

void AnimatedSpriteRendererComponent::stop()
{
    if( d->localInstance )
    {
        d->localInstance->deleteLater();
        d->localInstance = 0;
        d->item->setMaterialInstance( d->material );
    }
}

void AnimatedSpriteRendererComponent::cleanup()
{
    if( d->item )
    {
        GluonGraphics::Engine::instance()->destroyItem( d->item );
        d->item = 0;
    }
}

bool AnimatedSpriteRendererComponent::isAnimating()
{
    return d->animating;
}

bool AnimatedSpriteRendererComponent::isLooping()
{
    return d->looping;
}

bool AnimatedSpriteRendererComponent::isPlaying()
{
    return d->playing;
}

void AnimatedSpriteRendererComponent::setAnimating( bool animate )
{
    d->animating = animate;
}

void AnimatedSpriteRendererComponent::setLooping( bool loop )
{
    d->looping = loop;
    if( !d->playing )
        d->playing = true;
}

QSizeF AnimatedSpriteRendererComponent::size()
{
    return d->size;
}

void AnimatedSpriteRendererComponent::setSize( const QSizeF& size )
{
    d->size = size;
}

GluonGraphics::MaterialInstance*
AnimatedSpriteRendererComponent::material()
{
    return d->material;
}

void AnimatedSpriteRendererComponent::setMaterial( GluonGraphics::MaterialInstance* material )
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

void AnimatedSpriteRendererComponent::setMaterial( const QString& path )
{
    setMaterial( qobject_cast<GluonGraphics::MaterialInstance*>( Game::instance()->gameProject()->findItemByName( path ) ) );
}

int AnimatedSpriteRendererComponent::animation()
{
    return d->currentAnimation;
}

void AnimatedSpriteRendererComponent::setAnimation( int anim )
{
    if( anim < 0 || anim > d->frameCounts.size() - 1 )
        return;

    d->currentAnimation = anim;
    d->currentFrame = d->startFrames.at( anim );
    d->currentMaxFrame = d->startFrames.at( anim ) + d->frameCounts.at( anim );
}

int AnimatedSpriteRendererComponent::direction()
{
    return d->direction;
}

void AnimatedSpriteRendererComponent::setDirection( int direction )
{
    d->direction = direction;
}

QList< int > AnimatedSpriteRendererComponent::frameCounts()
{
    return d->frameCounts;
}

void AnimatedSpriteRendererComponent::setFrameCounts( const QList< int >& counts )
{
    d->frameCounts = counts;
    setAnimation( d->currentAnimation );
}

int AnimatedSpriteRendererComponent::frameRate()
{
    return d->frameRate;
}

void AnimatedSpriteRendererComponent::setFrameRate( int frameRate )
{
    d->frameRate = frameRate;
}

QSizeF AnimatedSpriteRendererComponent::frameSize()
{
    return d->frameSize;
}

void AnimatedSpriteRendererComponent::setFrameSize( const QSizeF& size )
{
    d->frameSize = size;
    d->frameWidthUV = d->frameSize.width() / d->textureSize.width();
    d->frameHeightUV = d->frameSize.height() / d->textureSize.height();
}

QList< int > AnimatedSpriteRendererComponent::startFrames()
{
    return d->startFrames;
}

void AnimatedSpriteRendererComponent::setStartFrames( const QList< int >& starts )
{
    d->startFrames = starts;
    setAnimation( d->currentAnimation );
}

// TODO: Add support for multiple-texture based animation.
// int AnimatedSpriteRendererComponent::textureCount()
// {
//
// }
//
// void AnimatedSpriteRendererComponent::setTextureCount ( int count )
// {
//
// }

Q_EXPORT_PLUGIN2( gluon_component_spriterenderer, GluonEngine::AnimatedSpriteRendererComponent );

#include "animatedspriterenderercomponent.moc"
