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

#include "effectfile.h"

#include "source.h"
#include "audiohelper.h"
#include "abstractplaylist.h"
#include "decoder.h"
#include "decoderplugin.h"
#include "buffer.h"
#include <core/log.h>

#include <QtCore/QHash>

using namespace GluonAudio;

class EffectFile::Private
{
    public:
        Private() : dec(0), valid(true), decodingStarted(false), isFinished(false) {}
        
        QList<Source*> sources;
        QHash<Source*, int> sourcePosition;
        QList<Buffer> buffer;
        Decoder* dec;
        bool valid;
        bool decodingStarted;
        bool isFinished;
};

EffectFile::EffectFile(QString file, QObject* parent)
    : AbstractFile(file, parent)
{
    d->dec = AudioHelper::instance()->decoderPlugins()[0]->createDecoder(this->file());
}

EffectFile::~EffectFile()
{
    delete d->dec;
    delete d;
}

void EffectFile::feedSource(Source* source)
{
    d->sources.append(source);
    d->sourcePosition.insert(source, 0);
    
    if( !d->decodingStarted )
    {
        AudioHelper::instance()->registerForUpdates(this);
    }
    else
    {
        if( d->dec->isStereo() )
            source->setGlobal(true);
    }
}

void EffectFile::stopFeedingSource(Source* source)
{
    d->sources.removeAll(source);
    d->sourcePosition.remove(source);
}

void EffectFile::update()
{
    if( !isValid() )
        return;
    if( !d->dec->isValid() )
    {
        ERROR() << "Invalid decoder state...";
        for( Source* s : d->sources )
        {
            stopFeedingSource(s);
        }
        return;
    }
    if( !d->decodingStarted )
    {
        if( d->dec->isLoaded() )
        {
            if( d->dec->isStereo() )
            {
                for( Source* s : d->sources )
                {
                    s->setGlobal(true);
                }
            }
            d->dec->startDecoding();
            d->decodingStarted = true;
        }
        return;
    }
    
    if( !d->isFinished )
    {
        while( d->dec->buffersAvailable() )
        {
            d->buffer.append( d->dec->getBuffer() );
        }
        
        if( d->dec->isEndOfFile() )
            d->isFinished = true;
    }
    
    for( Source* source : d->sources )
    {
        source->removeOldBuffers();
        
        float remainingTimeInBuffer = source->remaingTime();
        
        while( d->sourcePosition[source] < d->sources.count() && remainingTimeInBuffer < source->getMaxBufferSize() )
        {
            d->sourcePosition[source]++;
            
            Buffer buffer = d->buffer.at( d->sourcePosition[source] );
            if( !generateBuffer( &buffer, d->dec->isStereo() ) )
            {
                stopFeedingSource( source );
                break;
            }
            
            source->queueBuffer( buffer );
            remainingTimeInBuffer += buffer.length;
        }
        
        if( d->isFinished && d->sourcePosition[source] == d->sources.count() )
        {
            source->playlist()->fileNearlyFinished();
            stopFeedingSource( source );
        }
    }       
}
