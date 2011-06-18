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

#include <audio/engine.h>
#include <audio/sound.h>
#include <engine/assets/audio/sound/soundasset.h>
#include <engine/gameobject.h>
#include <core/metainfo.h>

#include <QtCore/QDebug>
#include <QMimeData>

REGISTER_OBJECTTYPE( GluonEngine, SoundEmitterComponent )

using namespace GluonEngine;
using namespace GluonAudio;

class SoundEmitterComponent::SoundEmitterComponentPrivate
{
    public:
        SoundEmitterComponentPrivate()
            : asset( 0 )
            , sound( 0 )
            , radius( 10000.0f )
            , volume( 1.0f )
            , pitch( 1.0f )
            , loop( false )
            , autoPlay( false )
        {}

        Asset* asset;
        GluonAudio::Sound* sound;
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
    d->sound = new GluonAudio::Sound();
}

SoundEmitterComponent::~SoundEmitterComponent()
{
    if( d->sound->isValid() )
        d->sound->stop();

    if( d->asset )
        d->asset->deref();

    d->sound->deleteLater();
    delete d;
}

QString SoundEmitterComponent::category() const
{
    return QString( "Audio" );
}

void SoundEmitterComponent::play()
{
    if( d->sound->isValid() )
        d->sound->play();
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
        d->sound->load( asset->data()->text() ) ;
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
        d->sound->load( d->asset->data()->text() );
    }

    d->sound->setPosition( gameObject()->position() );
    d->sound->setRadius( d->radius );
    d->sound->setVolume( d->volume );
    d->sound->setPitch( d->pitch );
    d->sound->setLoop( d->loop );

    if( d->autoPlay && d->sound->isValid() )
        d->sound->play();
}

void SoundEmitterComponent::draw( int /* timeLapse */ )
{
    if( d->sound->isValid() )
        d->sound->setPosition( gameObject()->position() );
}

void SoundEmitterComponent::stop()
{
    if( d->sound->isValid() )
        d->sound->stop();
}

void SoundEmitterComponent::cleanup()
{
    d->sound->clear();
}

float SoundEmitterComponent::radius() const
{
    return d->radius;
}

void SoundEmitterComponent::setRadius( float radius )
{
    d->radius = radius;
    if( d->sound->isValid() )
        d->sound->setRadius( radius );
}

float SoundEmitterComponent::volume() const
{
    return d->volume;
}

void SoundEmitterComponent::setVolume( float volume )
{
    d->volume = volume;
    if( d->sound->isValid() )
        d->sound->setVolume( volume );
}

float SoundEmitterComponent::pitch() const
{
    return d->pitch;
}

void SoundEmitterComponent::setPitch( float pitch )
{
    d->pitch = pitch;
    if( d->sound->isValid() )
        d->sound->setPitch( pitch );
}

bool SoundEmitterComponent::isLooping() const
{
    return d->loop;
}

bool SoundEmitterComponent::isPlaying() const
{
    if( d->sound->isValid() )
    {
        return d->sound->isPlaying();
    }
    return false;
}

void SoundEmitterComponent::setLoop( bool loop )
{
    d->loop = loop;

    if( d->sound->isValid() )
        d->sound->setLoop( loop );
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

Q_EXPORT_PLUGIN2( gluon_component_soundemitter, GluonEngine::SoundEmitterComponent )

#include "soundemittercomponent.moc"
