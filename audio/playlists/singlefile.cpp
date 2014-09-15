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
        Private() : file(0), state(Stopped) {}
        
        AudioFile* file;
        PlayingState state;
};

SingleFile::SingleFile()
    : AbstractPlaylist()
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
    
    if( d->state == Started || d->state == Paused )
    {
        d->file->stopFeedingSource(source);
    }
    d->state = Stopped;
}

void SingleFile::fileNearlyFinished()
{
    // nothing to do
}

void SingleFile::start()
{
    switch( d->state )
    {
        case Started:
            break;
        case Paused:
            source()->continuePlaying();
            break;
        case Stopped:
            if( !d->file || !source() )
            {
                return;
            }
            d->file->feedSource( source() );
            break;
    }
}

void SingleFile::pause()
{
    if( d->state != Started )
        return;
    source()->pause();
}

void SingleFile::stop()
{
    if( d->state == Stopped )
        return;
    d->file->stopFeedingSource( source() );
    source()->stop();
    source()->clear();
}



