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

#include "engine.h"

#include <QtCore/QStringList>
#include <QtCore/QHashIterator>

#include <alure.h>

using namespace GluonAudio;

GLUON_DEFINE_SINGLETON( Engine )

class Engine::EnginePrivate
{
    public:
        EnginePrivate() : bufferLength( 250000 ), buffersPerStream( 3 ) {}
        ~EnginePrivate() {}

        QHash<QString, ALuint> bufferHash;
        int bufferLength;
        int buffersPerStream;
        int minimalStreamLength;
};

Engine::Engine ( QObject* parent )
    : GluonCore::Singleton< GluonAudio::Engine >( parent ), d( new EnginePrivate )
{
    alureInitDevice( 0, 0 );
    alureUpdateInterval( 0.125 );
}

Engine::~Engine()
{
    QHashIterator<QString, ALuint> i( d->bufferHash );
    while( i.hasNext() )
    {
        i.next();
        alDeleteBuffers( 1, &( i.value() ) );
    }
    delete d;
    alureShutdownDevice();
}

uint Engine::genBuffer( const QString& fileName )
{
    ALuint buffer = d->bufferHash.value( fileName );
    if( buffer == 0 )
    {
        buffer = alureCreateBufferFromFile( fileName.toLocal8Bit().constData() );
        d->bufferHash.insert( fileName, buffer );
    }

    return buffer;
}

int Engine::bufferLength()
{
    return d->bufferLength;
}

void Engine::setBufferLength( int microsecs )
{
    d->bufferLength = microsecs;
}

int Engine::buffersPerStream()
{
    return d->buffersPerStream;
}

void Engine::setBuffersPerStream( int buffers )
{
    d->buffersPerStream = buffers;
}

QStringList Engine::deviceList()
{
    int size = 0;
    const ALCchar** _devices = alureGetDeviceNames( true, &size );
    QStringList devices;
    for( int i = 0; i < size; i++ )
    {
        devices << QString( _devices[i] );
    }
    alureFreeDeviceNames( _devices );
    return devices;
}

bool Engine::setDevice( const QString& deviceName )
{
    alureShutdownDevice();
    return alureInitDevice( deviceName.toUtf8(), 0 );
}

Eigen::Vector3f Engine::listenerPosition()
{
    ALfloat listener[3];
    alGetListenerfv( AL_POSITION, listener );

    return Eigen::Vector3f( listener[0], listener[1], listener[2] );
}

void Engine::setListenerPosition( const Eigen::Vector3f& position )
{
    alListener3f( AL_POSITION, position.x(), position.y(), position.z() );
}
