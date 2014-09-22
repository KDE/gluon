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

#include "musicfile.h"

#include <QtCore/QHash>
#include <QtCore/QDebug>

#include <AL/al.h>
#include <AL/alc.h>

#include <core/log.h>

#include "source.h"
#include "audiohelper.h"
#include "decoder.h"
#include "decoderplugin.h"
#include "buffer.h"
#include "listener.h"
#include "abstractplaylist.h"

using namespace GluonAudio;

class MusicFile::Private
{
    public:
        Private(MusicFile* p) : parent(p) {}
        
        struct SourceData
        {
            Source* source;
            Decoder* dec;
            bool isDecoding;
        };
        
        void stopFeedingSource( SourceData* data );
        static bool generateBuffer( Buffer* buffer, bool isStereo );
        static void initializeDecoding( SourceData* data );
        static void queueBuffer( SourceData* data );
        
        MusicFile* parent;
        QList<SourceData*> dataList;
};

MusicFile::MusicFile(QString file, QObject* parent)
    : AbstractFile(file,parent)
    , d(new Private(this))
{
}

MusicFile::~MusicFile()
{
    delete d;
}

void MusicFile::feedSource(Source* source)
{
    if( !isValid() )
        return;
    if( d->dataList.empty() )
        AudioHelper::instance()->registerForUpdates(this);
    Private::SourceData* data = new Private::SourceData();
    data->source = source;
    data->dec = AudioHelper::instance()->decoderPlugins()[0]->createDecoder(file());
    data->isDecoding = false;
    d->dataList.prepend(data);
    source->audioFileAdded();
}

void MusicFile::stopFeedingSource(Source* source)
{
    for( Private::SourceData* data : d->dataList )
    {
        if( data->source == source )
        {
            d->stopFeedingSource(data);
            return;
        }
    }
}

void MusicFile::update()
{
    if( !isValid() )
        return;
    for( Private::SourceData* data : d->dataList )
    {
        if( !data->dec->isValid() )
        {
            ERROR() << "Invalid decoder state...";
            data->source->clear();
            d->stopFeedingSource(data);
            continue;
        }
        if( !data->isDecoding )
        {
            if( data->dec->isLoaded() )
            {
                Private::initializeDecoding(data);
            }
            return;
        }
        data->source->removeOldBuffers();
        
        float remainingTimeInBuffer = data->source->remaingTime();
        
        while( remainingTimeInBuffer < data->source->getMaxBufferSize() && data->dec->buffersAvailable() )
        {
            Buffer buffer = data->dec->getBuffer();
            if( !generateBuffer(&buffer, data->dec->isStereo()) )
            {
                data->source->stop();
                d->stopFeedingSource(data);
            }
            
            delete [] buffer.data;

            data->source->queueBuffer(buffer);
            remainingTimeInBuffer += buffer.length;
        }
        
        if( data->dec->isEndOfFile() && !data->dec->buffersAvailable() )
        {
            data->source->playlist()->fileNearlyFinished();
            d->stopFeedingSource(data);
        }
    }
}

void MusicFile::Private::stopFeedingSource(MusicFile::Private::SourceData* data)
{
    data->dec->stopDecoding();
    delete data->dec;
    delete data;
    dataList.removeOne(data);
    if( dataList.empty() )
        AudioHelper::instance()->unregisterForUpdates(parent);
}

void MusicFile::Private::initializeDecoding(MusicFile::Private::SourceData* data)
{
    if( data->dec->isStereo() )
        data->source->setGlobal( true );
    data->dec->startDecoding();
    data->isDecoding = true;
}

