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

#include "abstractplaylist.h"

#include "source.h"

#include <core/debughelper.h>

using namespace GluonAudio;

class AbstractPlaylist::Private
{
    public:
        Private() : source(0), state(Stopped) {}
        
        Source* source;
        PlayingState state;
};

AbstractPlaylist::AbstractPlaylist( QObject* parent )
    : QObject(parent)
    , d(new Private())
{
}

AbstractPlaylist::~AbstractPlaylist()
{
    delete d;
}

void AbstractPlaylist::addedToSource(Source* source)
{
    d->source = source;
    if( source )
    connect( source, SIGNAL(endOfBuffer(Source*)), this, SLOT(sourceOutOfBuffer(Source*)) );
}

void AbstractPlaylist::removedFromSource(Source* source)
{
    d->source = 0;
    disconnect( source, SIGNAL(endOfBuffer(Source*)), this, SLOT(sourceOutOfBuffer(Source*)) );
    
    source->stop();
    source->clear();
}

AbstractPlaylist::PlayingState AbstractPlaylist::getPlayingState() const
{
    return d->state;
}

void AbstractPlaylist::sourceOutOfBuffer(Source* s)
{
    DEBUG_BLOCK
    DEBUG_TEXT( "Got out of buffer" )
    Q_UNUSED(s)
    if( d->state == Stopped )
    {
        DEBUG_TEXT( "Signal stop" )
        emit stopped();
    }
}


Source* AbstractPlaylist::source() const
{
    return d->source;
}

void AbstractPlaylist::setPlayingState(AbstractPlaylist::PlayingState state)
{
    d->state = state;
}