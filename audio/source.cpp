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

#include <core/debughelper.h>

#include "listener.h"

using namespace GluonAudio;

class Source::Private
{
    public:
        Private() : valid(false), global(false), name(0), state(Stopped), volume(1.0f), parentVolume(0.0f), maxBufferSize(1.f) {}
        
        bool valid;
        bool global;
        ALuint name;
        PlayingState state;
        QList<ALuint> currentBuffers;
        QList<float> currentLengths;
        Eigen::Vector3f position;
        float volume;
        float parentVolume;
        float maxBufferSize;
        
        float timeInBuffer();
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

Source::PlayingState Source::getPlayingState()
{
    return d->state;
}

void Source::queueBuffer( unsigned int bufferName, float bufferLength )
{
    DEBUG_BLOCK
    ALuint name = bufferName;
    alSourceQueueBuffers( d->name, 1, &name );
    ALCenum error = alGetError();
    if( error != AL_NO_ERROR )
    {
        DEBUG_TEXT2( "OpenAL-Error while queueing buffer: %1", error )
        return;
    }
    d->currentBuffers.prepend(name);
    d->currentLengths.prepend(bufferLength);
    
    if( d->state == Started )
      play();
}

int Source::removeOldBuffers()
{
    DEBUG_BLOCK
    int processed = 0;
    alGetSourcei( d->name, AL_BUFFERS_PROCESSED, &processed);
    ALCenum error = alGetError();
    if( error != AL_NO_ERROR )
    {
        DEBUG_TEXT2( "OpenAL-Error while checking number of buffers: %1", error )
        return 0;
    }
    for( int i=0; i<processed; i++ )
    {
        ALuint buffer = d->currentBuffers.takeLast();
        d->currentLengths.removeLast();
        alSourceUnqueueBuffers( d->name, 1, &buffer );
        error = alGetError();
        if( error != AL_NO_ERROR )
        {
            DEBUG_TEXT2( "OpenAL-Error while removing buffer: %1", error )
        }
    }
    
    int asd;
    alGetSourcei( d->name, AL_BUFFERS_QUEUED, &asd);
    alGetError();
    //DEBUG_TEXT2( "Buffers left: %1", asd );
    
    return processed; 
}

void Source::fileNearlyFinished()
{
    if( d->timeInBuffer() < d->maxBufferSize*1.01f )
        emit queueNext();
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

float Source::getMaxBufferSize()
{
    return d->maxBufferSize;
}

void Source::play()
{
    DEBUG_BLOCK
    //DEBUG_TEXT("Play")
    if( d->state == Started )
    {
        ALenum state;
        alGetSourcei( d->name, AL_SOURCE_STATE, &state );
        ALCenum error = alGetError();
        if( error != AL_NO_ERROR )
        {
            DEBUG_TEXT2( "OpenAL-Error while getting playing state: %1", error );
            return;
        }
        if( state == AL_PLAYING )
            return;
    }
    
    alSourcePlay( d->name );
    ALCenum error = alGetError();
    if( error != AL_NO_ERROR )
    {
        DEBUG_TEXT2( "OpenAL-Error while starting to play: %1", error )
        return;
    }
    d->state = Started;
}

void Source::pause()
{
    DEBUG_BLOCK
    if( d->state == Paused )
        return;
    alSourcePause( d->name );
    ALCenum error = alGetError();
    if( error != AL_NO_ERROR )
    {
        DEBUG_TEXT2( "OpenAL-Error while pausing: %1", error )
        return;
    }
}

void Source::stop()
{
    DEBUG_BLOCK
    if( d->state == Stopped )
        return;
    alSourceStop( d->name );
    ALCenum error = alGetError();
    if( error != AL_NO_ERROR )
    {
        DEBUG_TEXT2( "OpenAL-Error while stopping to play: %1", error )
        return;
    }
}

////////////////////
// Private functions
////////////////////

float Source::Private::timeInBuffer()
{
    float time = 0;
    for( float bufferLength : currentLengths )
        time += bufferLength;
    return time;
}

