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

using namespace GluonAudio;

class AbstractPlaylist::Private
{
    public:
        Private() : source(0) {}
        
        Source* source;
};

AbstractPlaylist::AbstractPlaylist(Source* source)
    : d(new Private())
{
    d->source = source;
    if( d->source )
    {
        connect( d->source, SIGNAL(queueNext()), this, SLOT(queueNext()) );
    }
}

AbstractPlaylist::~AbstractPlaylist()
{
    delete d;
}

void AbstractPlaylist::setSource(Source* source)
{
    if( d->source )
    {
        disconnect( d->source, SIGNAL(queueNext()), this, SLOT(queueNext()) );
    }
    if( source )
    {
        connect( d->source, SIGNAL(queueNext()), this, SLOT(queueNext()) );
    }
    d->source = source;
}

Source* AbstractPlaylist::source() const
{
    return d->source;
}