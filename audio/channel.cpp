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

#include "channel.h"

using namespace GluonAudio;

class Channel::Private
{
    public:
        Private() : valid(false), volume(1.0f), parentVolume(0.0f) {}
        
        bool valid;
        QList<Channel*> channels;
        QList<Source*> sources;
        float volume;
        float parentVolume;
};

Channel::Channel(QObject* parent)
    : QObject(parent)
    , d(new Private())
{   
}

Channel::~Channel()
{
    delete d;
}

bool Channel::isValid() const
{
    return d->valid;
}

void Channel::setChannelVolume( float volume )
{
    d->volume = volume;
    if( !d->valid )
        return;
    foreach( Channel* c, d->channels )
    {
        c->setParentChannelVolume( d->volume * d->parentVolume );
    }
    foreach( Source* s, d->sources )
    {
        s->setParentChannelVolume( d->volume * d->parentVolume );
    }
}

float Channel::channelVolume() const
{
    return d->volume;
}

void Channel::addSubchannel(Channel* subchannel)
{
    d->channels.append( subchannel );
    subchannel->setParent(this);
    if( d->valid )
        subchannel->setParentChannelVolume( d->volume * d->parentVolume );
}

QList<Channel*> Channel::subchannels() const
{
    return d->channels;
}

void Channel::addSource(Source* source)
{
    d->sources.append(source);
    source->setParent(this);
    if( d->valid )
        source->setParentChannelVolume( d->volume * d->parentVolume );
}

QList<Source*> Channel::sources() const
{
    return d->sources;
}

void Channel::setParentChannelVolume(float volume)
{
    d->valid = true;
    foreach( Channel* c, d->channels )
    {
        c->setParentChannelVolume( d->volume * d->parentVolume );
    }
    foreach( Source* s, d->sources )
    {
        s->setParentChannelVolume( d->volume * d->parentVolume );
    }
}


