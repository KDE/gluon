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

#include "singlefile.h"

#include "../abstractplaylist.h"
#include "../audiofile.h"
#include "../source.h"

using namespace GluonAudio;

class SingleFile::Private
{
    public:
        Private() : file(0), repeat(false) {}
        
        AudioFile* file;
        bool repeat;
};

SingleFile::SingleFile(QObject* parent)
    : AbstractPlaylist(parent)
    , d( new Private() )
{
}

SingleFile::~SingleFile()
{
    delete d;
}

void SingleFile::setFile(AudioFile* file)
{
    if( d->file )
    {
        d->file->stopFeedingSource( source() );
        source()->stop();
        source()->clear();
    }
    
    d->file = file;
}

void SingleFile::setFile( QString path )
{
    //TODO: Use the Audio File Manager
    AudioFile* file = new AudioFile( path );
    setFile( file );
}

void SingleFile::removedFromSource(Source* source)
{
    GluonAudio::SingleFile::removedFromSource(source);
    
    if( getPlayingState() == Started || getPlayingState() == Paused )
    {
        d->file->stopFeedingSource(source);
    }
    setPlayingState(Stopped);
}

void SingleFile::fileNearlyFinished()
{
    if( d->repeat )
        d->file->feedSource( source() );
    else
        setPlayingState(Stopped);
}

bool SingleFile::repeat() const
{
    return d->repeat;
}

void SingleFile::setRepeat(bool repeat)
{
    d->repeat = repeat;
}

void SingleFile::start()
{
    switch( getPlayingState() )
    {
        case Started:
            break;
        case Paused:
            source()->continuePlaying();
            setPlayingState(Started);
            break;
        case Stopped:
            if( !d->file || !source() )
            {
                return;
            }
            d->file->feedSource( source() );
            setPlayingState(Started);
            break;
    }
}

void SingleFile::pause()
{
    if( getPlayingState() != Started )
        return;
    source()->pause();
    setPlayingState(Paused);
}

void SingleFile::stop()
{
    if( getPlayingState() == Stopped )
        return;
    d->file->stopFeedingSource( source() );
    source()->stop();
    source()->clear();
    setPlayingState(Stopped);
}



