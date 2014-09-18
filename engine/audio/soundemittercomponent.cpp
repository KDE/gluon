/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010-2011 Guillaume Martres <smarter@ubuntu.com>
 * Copyright (c) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

#include "soundemittercomponent.h"

#include <engine/asset.h>
#include <engine/gameobject.h>
#include <audio/source.h>
#include <audio/playlists/singlefile.h>
#include <core/metainfo.h>

REGISTER_OBJECTTYPE( GluonEngine, SoundEmitterComponent )

using namespace GluonEngine;
using namespace GluonAudio;

class SoundEmitterComponent::SoundEmitterComponentPrivate
{
    public:
        SoundEmitterComponentPrivate()
            : asset( 0 )
            , source( 0 )
            , playlist( 0 )
            , radius( 10000.0f )
            , volume( 1.0f )
            , pitch( 1.0f )
            , loop( false )
            , autoPlay( false )
        {}

        Asset* asset;
        GluonAudio::Source* source;
        GluonAudio::SingleFile* playlist;
        float radius;
        float volume;
        float pitch;
        bool loop;
        bool autoPlay;
};

SoundEmitterComponent::SoundEmitterComponent( QObject* parent )
    : Component( parent )
    , d( new SoundEmitterComponentPrivate )
{
    d->source = new GluonAudio::Source(this);
    d->playlist = new GluonAudio::SingleFile(this);
    d->source->setPlaylist( d->playlist );
}

SoundEmitterComponent::~SoundEmitterComponent()
{
    if( d->source->isValid() )
        d->source->stop();

    if( d->asset )
        d->asset->deref();

    delete d;
}

QString SoundEmitterComponent::category() const
{
    return QString( "Audio" );
}

void SoundEmitterComponent::play()
{
    if( d->source->isValid() )
        d->playlist->start();
}

Asset* SoundEmitterComponent::sound()
{
    return d->asset;
}

void SoundEmitterComponent::setSound( Asset* asset )
{
    if( d->asset )
        d->asset->deref();

    if( !asset )
    {
        d->asset = 0;
        return;
    }

    d->asset = asset;
    d->asset->ref();
    if( asset->data()->hasText() )
    {
        //debug(asset->data()->text());
        d->playlist->setFile( asset->data()->text() ) ;
    }
}

void SoundEmitterComponent::initialize()
{
}

void SoundEmitterComponent::start()
{
    if( d->asset )
    {
        if( !d->asset->isLoaded() )
            d->asset->load();
        d->playlist->setFile( d->asset->data()->text() );
    }

    d->source->setPosition( gameObject()->position() );
    d->source->setRadius( d->radius );
    d->source->setVolume( d->volume );
    d->source->setPitch( d->pitch );
    d->playlist->setRepeat( d->loop );

    if( d->autoPlay && d->source->isValid() )
        d->playlist->start();
}

void SoundEmitterComponent::draw( int /* timeLapse */ )
{
    if( d->source->isValid() )
        d->source->setPosition( gameObject()->position() );
}

void SoundEmitterComponent::stop()
{
    if( d->source->isValid() )
        d->source->stop();
}

void SoundEmitterComponent::cleanup()
{
    d->source->clear();
}

float SoundEmitterComponent::radius() const
{
    return d->radius;
}

void SoundEmitterComponent::setRadius( float radius )
{
    d->radius = radius;
    if( d->source->isValid() )
        d->source->setRadius( radius );
}

float SoundEmitterComponent::volume() const
{
    return d->volume;
}

void SoundEmitterComponent::setVolume( float volume )
{
    d->volume = volume;
    if( d->source->isValid() )
        d->source->setVolume( volume );
}

float SoundEmitterComponent::pitch() const
{
    return d->pitch;
}

void SoundEmitterComponent::setPitch( float pitch )
{
    d->pitch = pitch;
    if( d->source->isValid() )
        d->source->setPitch( pitch );
}

bool SoundEmitterComponent::isLooping() const
{
    return d->loop;
}

bool SoundEmitterComponent::isPlaying() const
{
    if( d->source->isValid() )
    {
        return d->playlist->getPlayingState() == AbstractPlaylist::Started;
    }
    return false;
}

void SoundEmitterComponent::setLoop( bool loop )
{
    d->loop = loop;

    if( d->source->isValid() )
        d->playlist->setRepeat( loop );
}

bool SoundEmitterComponent::autoPlay() const
{
    return d->autoPlay;
}

void SoundEmitterComponent::setAutoPlay( bool autoPlay )
{
    d->autoPlay = autoPlay;
}

void SoundEmitterComponent::populateMetaInfo( GluonCore::MetaInfo* info )
{
    info->setPropertyRange( "pitch", 0.5, 2.0 );
}
