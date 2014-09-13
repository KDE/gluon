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

#include "linearplaylist.h"

#include "../source.h"
#include "../audiofile.h"

#include <QtCore/QTime>

using namespace GluonAudio;

class LinearPlaylist::Private
{
    public:
        Private() : currentFile(0), random(false), repeatAll(false) {}
        
        QList<AudioFile*> files;
        int currentFile;
        bool random;
        bool repeatAll;
};

LinearPlaylist::LinearPlaylist(Source* source)
    : AbstractPlaylist(source)
    , d(new Private())
{
    qsrand(QTime::currentTime().msec());
}

LinearPlaylist::~LinearPlaylist()
{
    delete d;
}

void LinearPlaylist::setFiles(QList< AudioFile* > files)
{
    Source::PlayingState oldState = source()->getPlayingState();
    if( oldState == Source::Started || oldState == Source::Paused )
        source()->stop();
    if( !d->files.empty() )
        d->files[d->currentFile]->stopFeedingSource( source() );
    source()->clear();
    
    d->files = files;
    
    if( oldState == Source::Started || oldState == Source::Paused )
        source()->stop();
    source()->clear();
    
    if( d->files.empty() )
        return;
    
    d->files[0]->feedSource(source());
}

bool LinearPlaylist::random()
{
    return d->random;
}

void LinearPlaylist::setRandom(bool random)
{
    d->random = random;
}

bool LinearPlaylist::repeatAll()
{
    return d->repeatAll;
}

void LinearPlaylist::setRepeatAll(bool repeat)
{
    d->repeatAll = repeat;
}

void LinearPlaylist::setSource(Source* source)
{
    Source::PlayingState oldState = this->source()->getPlayingState();
    if( oldState == Source::Started || oldState == Source::Paused )
        this->source()->stop();
    if( !d->files.empty() )
        d->files[d->currentFile]->stopFeedingSource( this->source() );
    this->source()->clear();
    
    GluonAudio::AbstractPlaylist::setSource(source);
    
    if( d->files.empty() )
        return;
    
    d->files[0]->feedSource(source);
}


void LinearPlaylist::queueNext()
{
    if( random() )
    {
        d->currentFile = qrand() % d->files.count();
    }
    else
    {
        d->currentFile = (d->currentFile + 1) % d->files.count();
        if( d->currentFile == 0 && !d->repeatAll )
            return; // let it stop
    }
    d->files[d->currentFile]->feedSource(source());
}
