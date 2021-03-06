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

#include "listener.h"

#include <QtCore/QStringList>
#include <QtCore/QHashIterator>

#include <AL/al.h>
#include <AL/alc.h>

#include <core/log.h>

#include "channel.h"

using namespace GluonAudio;

GLUON_DEFINE_SINGLETON( Listener )

class Listener::Private
{
    public:
        Private() : isValid(false), device(0), context(0), volume(1.0f), position(0,0,0) {}
        ~Private() {}

        bool isValid;
        QList<Channel*> channels;
        QList<Source*> sources;
        
        ALCdevice* device;
        ALCcontext* context;
        float volume;
        Eigen::Vector3f position;
};

Listener::Listener ( QObject* parent )
    : GluonCore::Singleton< GluonAudio::Listener >( parent ), d( new Private )
{
    d->device = alcOpenDevice(NULL);
    if( !d->device )
    {
        ERROR() << "OpenAL: Error while opening device";
        return;
    }
    
    alGetError(); // Reset error stack
    
    d->context = alcCreateContext(d->device, NULL);
    if( !alcMakeContextCurrent(d->context) )
    {
        ERROR() << "OpenAL Error: Could not make context current.";
        
    }
    ALCenum error = alGetError();
    if( error != AL_NO_ERROR )
    {
        ERROR() << "OpenAL Error while creating context: " << error;
        return;
    }
    
}

Listener::~Listener()
{
    alcMakeContextCurrent(NULL);
    alcDestroyContext(d->context);
    alcCloseDevice(d->device);
    
    delete d;
}

float Listener::masterVolume() const
{
    return d->volume;
}

void Listener::setMasterVolume(float vol)
{
    d->volume = vol;
    foreach( Channel* c, d->channels )
    {
        c->setParentChannelVolume( d->volume );
    }
    foreach( Source* s, d->sources )
    {
        s->setParentChannelVolume( d->volume );
    }
}

QList<Channel*> Listener::channels() const
{
    return d->channels;
}

void Listener::addChannel(Channel* channel)
{
    d->channels.append( channel );
    channel->setParent(this);
    channel->setParentChannelVolume( d->volume );
}

QList<Source*> Listener::sources() const
{
    return d->sources;
}

void Listener::addSource(Source* source)
{
    d->sources.append( source );
    source->setParentChannelVolume( d->volume );
}

Eigen::Vector3f Listener::listenerPosition()
{
    return d->position;
}

void Listener::setListenerPosition( const Eigen::Vector3f& position )
{
    if( position == d->position )
        return;
    d->position = position;
    alListener3f( AL_POSITION, position.x(), position.y(), position.z() );
}
