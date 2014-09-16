/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2014 Felix Rohrbach <kde@fxrh.de>
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

#include "source.h"

#include <AL/al.h>
#include <AL/alc.h>

#include <QtCore/QVector>
#include <QtCore/QDebug>

#include <core/debughelper.h>

#include "listener.h"
#include "abstractplaylist.h"
#include "audiohelper.h"

using namespace GluonAudio;

class Source::Private
{
    public:
        Private() : valid(false), global(false), name(0), currentBufferLength(0), position(0.f,0.f,0.f), volume(1.0f), parentVolume(0.0f)
                  , maxBufferSize(1.f), pitch(1.f), radius(1.f), filesQueued(0), paused(false), updatesRegistered(false), playlist(0) {}
        
        bool valid;
        bool global;
        ALuint name;
        QList<Buffer> currentBuffers;
        float currentBufferLength;
        Eigen::Vector3f position;
        float volume;
        float parentVolume;
        float maxBufferSize;
        float pitch;
        float radius;
        int filesQueued;
        bool paused;
        bool updatesRegistered;
        AbstractPlaylist* playlist;
        
        void play();
        void calculateBufferLength();
};

Source::Source(QObject* parent)
    : QObject(parent)
    , d( new Private() )
{
    DEBUG_BLOCK
    Listener::instance();
    alGenSources(1, &d->name);
    ALCenum error = alGetError();
    if( error != AL_NO_ERROR )
    {
        DEBUG_TEXT2( "OpenAL-Error while creating source: %1", error )
        return;
    }
}

Source::~Source()
{
    delete d;
}

void Source::queueBuffer( Buffer buffer )
{
    DEBUG_BLOCK
    ALuint name = buffer.name;
    alSourceQueueBuffers( d->name, 1, &name );
    ALCenum error = alGetError();
    if( error != AL_NO_ERROR )
    {
        DEBUG_TEXT2( "OpenAL-Error while queueing buffer: %1", error )
        return;
    }
    d->currentBuffers.prepend(buffer);
    
    d->play();
    d->calculateBufferLength();
    if( !d->updatesRegistered )
    {
        AudioHelper::instance()->registerForUpdates(this);
        d->updatesRegistered = true;
    }
}

int Source::getNumberOfBuffers()
{
    DEBUG_BLOCK
    int buffers;
    alGetSourcei( d->name, AL_BUFFERS_QUEUED, &buffers);
    ALCenum error = alGetError();
    if( error != AL_NO_ERROR )
    {
        DEBUG_TEXT2( "OpenAL-Error while checking number of buffers: %1", error )
        return 0;
    }
    return buffers;
}

int Source::removeOldBuffers()
{
    DEBUG_BLOCK
    int processed = 0;
    alGetSourcei( d->name, AL_BUFFERS_PROCESSED, &processed);
    ALCenum error = alGetError();
    if( error != AL_NO_ERROR )
    {
        DEBUG_TEXT2( "OpenAL-Error while checking number of processed buffers: %1", error )
        return 0;
    }
    for( int i=0; i<processed; i++ )
    {
        Buffer buffer = d->currentBuffers.takeLast();
        alSourceUnqueueBuffers( d->name, 1, &buffer.name );
        error = alGetError();
        if( error != AL_NO_ERROR )
        {
            DEBUG_TEXT2( "OpenAL-Error while unqueueing buffer: %1", error )
            continue;
        }
        alDeleteBuffers( 1, &buffer.name );
        error = alGetError();
        if( error != AL_NO_ERROR )
        {
            DEBUG_TEXT2( "OpenAL-Error while removing buffer: %1", error )
        }
    }
    
    d->calculateBufferLength();
    
    int asd;
    alGetSourcei( d->name, AL_BUFFERS_QUEUED, &asd);
    alGetError();
    //DEBUG_TEXT2( "Buffers left: %1", asd );
    
    return processed; 
}

void Source::audioFileAdded()
{
    d->filesQueued++;
}

void Source::clear()
{
    DEBUG_BLOCK
    d->filesQueued = 0;
    for( Buffer& buffer : d->currentBuffers )
    {
        alSourceUnqueueBuffers( d->name, 1, &buffer.name );
        ALCenum error = alGetError();
        if( error != AL_NO_ERROR )
        {
            DEBUG_TEXT2( "OpenAL-Error while unqueueing buffers: %1", error )
            return;
        }
        alDeleteBuffers( 1, &buffer.name );
        error = alGetError();
        if( error != AL_NO_ERROR )
        {
            DEBUG_TEXT2( "OpenAL-Error while removing buffers: %1", error )
            return;
        }
    }
    d->currentBufferLength = 0.f;
    d->currentBuffers.clear();
    AudioHelper::instance()->unregisterForUpdates(this);
    d->updatesRegistered = false;
}

bool Source::isValid() const
{
    return d->valid;
}

bool Source::isGlobal() const
{
    return d->global;
}

void Source::setGlobal( bool isGlobal )
{
    DEBUG_BLOCK
    if( isGlobal == d->global )
        return;
    alSourcei( d->name, AL_SOURCE_RELATIVE, isGlobal ? AL_TRUE : AL_FALSE );
    ALCenum error = alGetError();
    if( error != AL_NO_ERROR )
    {
        DEBUG_TEXT2( "OpenAL-Error while setting relative: %1", error )
        return;
    }
    setPosition( Eigen::Vector3f(0.0f, 0.0f, 0.0f) );
    d->global = isGlobal;
}

Eigen::Vector3f Source::position() const
{
    return d->position;
}

void Source::setPosition( Eigen::Vector3f position )
{
    DEBUG_BLOCK
    if( d->global )
        return;
    if( d->position == position )
        return;
    alSource3f( d->name, AL_POSITION, position[0], position[1], position[2] );
    ALCenum error = alGetError();
    if( error != AL_NO_ERROR )
    {
        DEBUG_TEXT2( "OpenAL-Error while setting position: %1", error )
        return;
    }
    d->position = position;
}

float Source::volume() const
{
    return d->volume;
}

float Source::realVolume() const
{
    return d->volume * d->parentVolume;
}

void Source::setVolume( float vol )
{
    DEBUG_BLOCK
    d->volume = vol;
    alSourcef( d->name, AL_GAIN, realVolume() );
    ALCenum error = alGetError();
    if( error != AL_NO_ERROR )
    {
        DEBUG_TEXT2( "OpenAL-Error while setting volume: %1", error )
        return;
    }
}

void Source::setParentChannelVolume( float vol )
{
    DEBUG_BLOCK
    d->parentVolume = vol;
    alSourcef( d->name, AL_GAIN, realVolume() );
    ALCenum error = alGetError();
    if( error != AL_NO_ERROR )
    {
        DEBUG_TEXT2( "OpenAL-Error while setting volume: %1", error )
        return;
    }
    if( !d->valid )
        d->valid = true;
}

float Source::positionInBuffers()
{
    DEBUG_BLOCK
    float position = 0.0f;
    alGetSourcef(d->name, AL_SEC_OFFSET, &position );
    ALCenum error = alGetError();
    if( error != AL_NO_ERROR )
    {
        DEBUG_TEXT2( "OpenAL-Error while getting second offset: %1", error )
    }
    return position;
}

float Source::remaingTime()
{
    return d->currentBufferLength - positionInBuffers();
}


float Source::getMaxBufferSize()
{
    return d->maxBufferSize;
}

AbstractPlaylist* Source::playlist() const
{
    return d->playlist;
}

void Source::setPlaylist(AbstractPlaylist* playlist)
{
    if( d->playlist )
        d->playlist->removedFromSource(this);
    
    clear();
    
    d->playlist = playlist;
    if( d->playlist )
        d->playlist->addedToSource(this);
}

void Source::pause()
{
    DEBUG_BLOCK
    if( d->paused )
        return;
    alSourcePause( d->name );
    ALCenum error = alGetError();
    if( error != AL_NO_ERROR )
    {
        DEBUG_TEXT2( "OpenAL-Error while pausing: %1", error )
        return;
    }
}

void Source::continuePlaying()
{
    DEBUG_BLOCK
    if( !d->paused )
        return;
    alSourcePause( d->name );
    ALCenum error = alGetError();
    if( error != AL_NO_ERROR )
    {
        DEBUG_TEXT2( "OpenAL-Error while continueing: %1", error )
        return;
    }
}

void Source::stop()
{
    DEBUG_BLOCK
    alSourceStop( d->name );
    ALCenum error = alGetError();
    if( error != AL_NO_ERROR )
    {
        DEBUG_TEXT2( "OpenAL-Error while stopping to play: %1", error )
        return;
    }
    d->paused = false;
}

void Source::update()
{
    if( !d->updatesRegistered )
        return;
    DEBUG_BLOCK
    ALenum state;
    alGetSourcei( d->name, AL_SOURCE_STATE, &state );
    ALCenum error = alGetError();
    if( error != AL_NO_ERROR )
    {
        DEBUG_TEXT2( "OpenAL-Error while getting playing state: %1", error );
        return;
    }
    if( state == AL_STOPPED )
    {
        // Buffer ran out
        AudioHelper::instance()->unregisterForUpdates(this);
        d->updatesRegistered = false;
        emit endOfBuffer(this);
    }
}

float Source::pitch() const
{
    return d->pitch;
}

void Source::setPitch(float pitch)
{
    DEBUG_BLOCK
    if( pitch == d->pitch )
        return;

    alSourcef( d->name, AL_PITCH, pitch );
    ALCenum error = alGetError();
    if( error != AL_NO_ERROR )
    {
        DEBUG_TEXT2( "OpenAL-Error while setting pitch: %1", error );
        return;
    }
    d->pitch = pitch;
}

float Source::radius() const
{
    return d->radius;
}

void Source::setRadius(float radius)
{
    DEBUG_BLOCK
    if( radius == d->radius )
        return;
    
    alSourcef( d->name, AL_REFERENCE_DISTANCE, radius );
    ALCenum error = alGetError();
    if( error != AL_NO_ERROR )
    {
        DEBUG_TEXT2( "OpenAL-Error while setting radius: %1", error );
        return;
    }
    d->radius = radius;
}

/////////////////////////////////////////
// Private Functions
/////////////////////////////////////////

void Source::Private::play()
{
    DEBUG_BLOCK
    //DEBUG_TEXT("Play")
    
    ALenum state;
    alGetSourcei( name, AL_SOURCE_STATE, &state );
    ALCenum error = alGetError();
    if( error != AL_NO_ERROR )
    {
        DEBUG_TEXT2( "OpenAL-Error while getting playing state: %1", error );
        return;
    }
    if( state == AL_PLAYING )
        return;
    
    alSourcePlay( name );
    error = alGetError();
    if( error != AL_NO_ERROR )
    {
        DEBUG_TEXT2( "OpenAL-Error while starting to play: %1", error )
        return;
    }
}

void Source::Private::calculateBufferLength()
{
    currentBufferLength = 0;
    for( const Buffer& buffer : currentBuffers )
    {
        currentBufferLength += buffer.length;
    }
}



