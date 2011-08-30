/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2009 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2009-2011 Guillaume Martres <smarter@ubuntu.com>
 * Copyright (C) 2011 Laszlo Papp <lpapp@kde.org>
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

#include <core/debughelper.h>

#include <alure.h>

using namespace GluonAudio;

class Sound::SoundPrivate
{
    public:
        SoundPrivate()
            : isValid(false)
            , isStreamed(false)
            , isLooping(false)
            , status(STOPPED)
            , stream(0)
            , source(0)
            , position(QVector3D( 0, 0, 0 ))
            , volume(1.0f)
            , pitch(1.0f)
            , radius(10000.0f)
            , duration(0)
        {
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
                DEBUG_TEXT2( "%1", str )
                isValid = false;
                return true;
            }
            return false;
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
            status = STOPPED;
            if( isStreamed )
            {
                alureDestroyStream( stream, 0, 0 );
            }
            stream = 0;
        }

        QString path;

        bool isValid;
        bool isStreamed;
        bool isLooping;
        Status status;
        alureStream* stream;
        ALuint source;
        QVector3D position;
        ALfloat volume;
        ALfloat pitch;
        ALfloat radius;
        double duration;
};

Sound::Sound(QObject *parent)
    : QObject( parent )
    , d( new SoundPrivate )
{
    Engine::instance();
    d->isValid = false;
}

Sound::Sound( const QString& fileName, QObject *parent )
    : QObject( parent )
    , d( new SoundPrivate )
{
    Engine::instance();
    load( fileName );
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

    alureStreamSizeIsMicroSec(true);
    alureStream *stream = alureCreateStreamFromFile(fileName.toLocal8Bit().data(), Engine::instance()->bufferLength(), 0, NULL);
    if( stream )
        d->duration = (double)alureGetStreamLength(stream) / alureGetStreamFrequency(stream);

    d->isStreamed = (d->duration >= Engine::instance()->bufferLength()*Engine::instance()->buffersPerStream() / 1e6);
    if( d->isStreamed )
        d->stream = stream;
    else
    {
        alureDestroyStream(stream, 0, NULL);
        stream = NULL;

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

ALfloat Sound::timeOffset() const
{
    if( !d->isValid )
    {
        return -1;
    }

    ALfloat seconds = 0.f;
    alGetSourcef( d->source, AL_SEC_OFFSET, &seconds );
    return seconds;
}

bool Sound::isLooping() const
{
    return d->isLooping;
}

bool Sound::isPlaying() const
{
    return d->status == PLAYING;
}

bool Sound::isPaused() const
{
    return d->status == PAUSED;
}

bool Sound::isStopped() const
{
    return d->status == STOPPED;
}

void Sound::setLoop( bool enabled )
{
    if( !d->isValid )
    {
        return -1;
    }

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
    if( !d->isValid )
    {
        return -1;
    }

    ALfloat volume;
    alGetSourcef( d->source, AL_GAIN, &volume );
    return volume;
}

ALfloat Sound::pitch() const
{
    return d->pitch;
}

ALfloat Sound::radius() const
{
    return d->radius;
}

double Sound::duration() const
{
    if( !d->isValid )
    {
        return 0;
    }
    return d->duration;
}

void Sound::setPosition( ALfloat x, ALfloat y, ALfloat z )
{
    setPosition( QVector3D( x, y, z ) );
}

void Sound::setPosition( QVector3D position )
{
    if( !d->isValid )
    {
        return;
    }

    d->position = position;
    ALfloat sourcePosition[] = { position.x(), position.y() , position.z() };
    alSourcefv( d->source, AL_POSITION, sourcePosition );
}

void Sound::setVolume( ALfloat volume )
{
    if( !d->isValid )
    {
        return;
    }

    d->volume = volume;
    alSourcef( d->source, AL_GAIN, volume );
}

void Sound::setPitch( ALfloat pitch )
{
    if( !d->isValid )
    {
        return;
    }

    d->pitch = pitch;
    alSourcef( d->source, AL_PITCH, pitch );
}

void Sound::setRadius( ALfloat radius )
{
    if( !d->isValid )
    {
        return;
    }

    d->radius = radius;
    alSourcef( d->source, AL_REFERENCE_DISTANCE, radius );
}

void Sound::callbackStopped( void* object, ALuint source )
{
    static_cast<GluonAudio::Sound*>( object )->cbStop();
}

void Sound::cbStop()
{
    d->status = STOPPED;
    if( d->isLooping )
    {
        play();
    }
    else
    {
        emit stopped();
    }
}

void Sound::play()
{
    if( isPaused() )
    {
        alureResumeSource( d->source );
    }
    else if( isPlaying() )
    {
        return;
    }

    if( d->isStreamed )
    {
        int loopCount = ( d->isLooping ? -1 : 0 );
        alurePlaySourceStream( d->source, d->stream, Engine::instance()->buffersPerStream(), loopCount, Sound::callbackStopped, this );
    }
    else
    {
        alurePlaySource( d->source, callbackStopped, this );
    }
    d->status = PLAYING;
    d->newError( "Playing " + d->path + " failed" );
    emit played();
}

void Sound::pause()
{
    alurePauseSource( d->source );
    d->status = PAUSED;
    d->newError( "Pausing " + d->path + " failed" );
    emit paused();
}

void Sound::stop()
{
    alureStopSource( d->source, false );
    d->status = STOPPED;
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

void Sound::setVelocity( ALfloat vx, ALfloat vy, ALfloat vz )
{
    if( !d->isValid )
    {
        return;
    }

    ALfloat velocity[] = { vx, vy, vz };
    alSourcefv( d->source, AL_VELOCITY, velocity );
}

void Sound::setDirection( ALfloat dx, ALfloat dy, ALfloat dz )
{
    if( !d->isValid )
    {
        return;
    }

    ALfloat direction[] = { dx, dy, dz };
    alSourcefv( d->source, AL_POSITION, direction );
}

void Sound::setTimeOffset( ALfloat time )
{
    if( !d->isValid )
    {
        return;
    }

    alSourcef( d->source, AL_SEC_OFFSET, time );

}

#include "sound.moc"
