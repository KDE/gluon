/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2009 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2009-2011 Guillaume Martres <smarter@ubuntu.com>
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

#include "sound.h"

#include "engine.h"

#include <alure.h>

#include <core/debughelper.h>

#include <sndfile.h>

using namespace GluonAudio;

class Sound::SoundPrivate
{
    public:
        SoundPrivate()
        {
            init();
        }
        ~SoundPrivate()
        {
        }

        bool newError( const QString& str )
        {
            QLatin1String error = QLatin1String( alureGetErrorString() );
            if( error != QLatin1String( "No error" ) )
            {
                DEBUG_BLOCK
                DEBUG_TEXT2( "Alure error: %1", error )
                DEBUG_TEXT2( "%2", str )
                isValid = false;
                return true;
            }
            return false;
        }

        void init()
        {
            isValid = false;
            isStreamed = false;
            isPaused = false;
            isStopped = true;
            isLooping = false;
            stream = 0;
            source = 0;
            position = QVector3D( 0, 0, 0 );
            volume = 1.0f;
            pitch = 1.0f;
            radius = 10000.0f;
            duration = 0;
        }

        bool setupSource()
        {
            if( path.isEmpty() )
            {
                return false;
            }

            alGenSources( 1, &source );
            if( source == 0 )
            {
                DEBUG_BLOCK
                DEBUG_TEXT2( "Empty source, OpenAL error: %1", alGetError() )
                return false;
            }

            ALfloat sourcePosition[] = { position.x(), position.y() , position.z() };
            alSourcefv( source, AL_POSITION, sourcePosition );
            alSourcef( source, AL_GAIN, volume );
            alSourcef( source, AL_PITCH, pitch );
            alSourcef( source, AL_REFERENCE_DISTANCE, radius );

            return true;
        }

        void _k_deleteSource()
        {
            if( source != 0 )
            {
                alureStopSource( source, false );
                alDeleteSources( 1, &source );
                source = 0;
            }
            isValid = false;
            isStopped = true;
            if( isStreamed )
            {
                alureDestroyStream( stream, 0, 0 );
            }
            stream = 0;
        }

        QString path;

        bool isValid;
        bool isStreamed;
        bool isPaused;
        bool isStopped;
        bool isLooping;
        alureStream* stream;
        ALuint source;
        QVector3D position;
        ALfloat volume;
        ALfloat pitch;
        ALfloat radius;
        double duration;
};

Sound::Sound()
    : QObject( Engine::instance() )
    , d( new SoundPrivate )
{
    d->isValid = false;
}

Sound::Sound( const QString& fileName )
    : QObject( Engine::instance() )
    , d( new SoundPrivate )
{
    load( fileName );
}

Sound::Sound( const QString& fileName, bool toStream )
    : QObject( Engine::instance() )
    , d( new SoundPrivate )
{
    load( fileName, toStream );
}

Sound::~Sound()
{
    d->_k_deleteSource();
    delete d;
}

bool Sound::isValid() const
{
    return d->isValid;
}

bool Sound::load( const QString& fileName )
{
    SF_INFO sfinfo;
    memset( &sfinfo, 0, sizeof( sfinfo ) );
    SNDFILE* sndfile = sf_open( fileName.toLocal8Bit().data(), SFM_READ, &sfinfo );
    sf_close( sndfile );

    d->duration = ( double )sfinfo.frames / sfinfo.samplerate;
    bool toStream = ( d->duration >= ( double )( Engine::instance()->bufferLength() * Engine::instance()->buffersPerStream() ) / 1e6 );

    return load( fileName, toStream );
}

bool Sound::load( const QString& fileName, bool toStream )
{
    if( fileName.isEmpty() )
    {
        d->isValid = false;
        return false;
    }
    if( !d->path.isEmpty() )
    {
        d->_k_deleteSource();
    }
    d->path = fileName;
    if( !d->setupSource() )
        return false;
    d->isStreamed = toStream;
    if( d->isStreamed )
    {
        alureStreamSizeIsMicroSec( true );
        d->stream = alureCreateStreamFromFile( d->path.toLocal8Bit().constData(), Engine::instance()->bufferLength(), 0, 0 );
    }
    else
    {
        ALuint buffer = Engine::instance()->genBuffer( d->path );
        if( d->newError( "Loading " + d->path + " failed" ) )
        {
            d->isValid = false;
            return false;
        }
        alSourcei( d->source, AL_BUFFER, buffer );
    }

    d->isValid = !d->newError( "Loading " + d->path + " failed" );
    return d->isValid;
}

ALfloat Sound::elapsedTime() const
{
    ALfloat seconds = 0.f;
    alGetSourcef( d->source, AL_SEC_OFFSET, &seconds );
    return seconds;
}

ALint Sound::status() const
{
    ALint status;
    alGetSourcei( d->source, AL_SOURCE_STATE, &status );
    return status;
}

bool Sound::isLooping() const
{
    return d->isLooping;
}

bool Sound::isPlaying() const
{
    return !d->isStopped;
}

void Sound::setLoop( bool enabled )
{
    d->isLooping = enabled;
    if( !d->isStreamed )
    {
        alSourcei( d->source, AL_LOOPING, enabled );
    }
}

void Sound::clear()
{
    d->_k_deleteSource();
}

QVector3D Sound::position() const
{
    return d->position;
}

ALfloat Sound::x() const
{
    return d->position.x();
}

ALfloat Sound::y() const
{
    return d->position.y();
}

ALfloat Sound::z() const
{
    return d->position.z();
}

ALfloat Sound::volume() const
{
    return d->volume;
}

ALfloat Sound::pitch() const
{
    return d->pitch;
}

ALfloat Sound::radius() const
{
    return d->radius;
}

void Sound::setPosition( ALfloat x, ALfloat y, ALfloat z )
{
    setPosition( QVector3D( x, y, z ) );
}

void Sound::setPosition( QVector3D position )
{
    d->position = position;
    ALfloat sourcePosition[] = { position.x(), position.y() , position.z() };
    alSourcefv( d->source, AL_POSITION, sourcePosition );
}

void Sound::setVolume( ALfloat volume )
{
    d->volume = volume;
    alSourcef( d->source, AL_GAIN, volume );
}

void Sound::setPitch( ALfloat pitch )
{
    d->pitch = pitch;
    alSourcef( d->source, AL_PITCH, pitch );
}

void Sound::setRadius( ALfloat radius )
{
    d->radius = radius;
    alSourcef( d->source, AL_REFERENCE_DISTANCE, radius );
}

void callbackStopped( void* object, ALuint source )
{
    static_cast<GluonAudio::Sound*>( object )->stopped();
}

void Sound::stopped()
{
    d->isStopped = true;
    if( d->isLooping )
    {
        play();
    }
}

void Sound::play()
{
    if( d->isPaused )
    {
        alureResumeSource( d->source );
    }

    if( !d->isStopped )
    {
        stop();
    }

    if( d->isStreamed )
    {
        int loopCount = ( d->isLooping ? -1 : 0 );
        alurePlaySourceStream( d->source, d->stream, Engine::instance()->buffersPerStream(), loopCount, callbackStopped, this );
    }
    else
    {
        alurePlaySource( d->source, callbackStopped, this );
    }
    d->isStopped = false;
    d->newError( "Playing " + d->path + " failed" );
}

void Sound::pause()
{
    alurePauseSource( d->source );
    d->isPaused = true;
    d->newError( "Pausing " + d->path + " failed" );
}

void Sound::stop()
{
    alureStopSource( d->source, false );
    d->isStopped = true;
    d->newError( "Stopping " + d->path + " failed" );
}

void Sound::rewind()
{
    if( d->isStreamed )
    {
        alureRewindStream( d->stream );
    }
    else
    {
        alSourceRewind( d->source );
    }
    d->newError( "Rewinding " + d->path + " failed" );
}

void Sound::setMinVolume( ALfloat min )
{
    alSourcef( d->source, AL_MIN_GAIN, min );
}

void Sound::setMaxVolume( ALfloat max )
{
    alSourcef( d->source, AL_MAX_GAIN, max );
}

void Sound::setVelocity( ALfloat vx, ALfloat vy, ALfloat vz )
{
    ALfloat velocity[] = { vx, vy, vz };
    alSourcefv( d->source, AL_VELOCITY, velocity );
}

void Sound::setDirection( ALfloat dx, ALfloat dy, ALfloat dz )
{
    ALfloat direction[] = { dx, dy, dz };
    alSourcefv( d->source, AL_POSITION, direction );
}

void Sound::setTimePosition( ALfloat time )
{
    alSourcef( d->source, AL_SEC_OFFSET, time );

}

double Sound::duration() const
{
    if( !d->isValid )
    {
        return 0;
    }
    return d->duration;
}

#include "sound.moc"
