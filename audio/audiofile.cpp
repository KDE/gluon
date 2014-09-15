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

#include "audiofile.h"

#include <QtCore/QHash>
#include <QtCore/QDebug>

#include <AL/al.h>
#include <AL/alc.h>

#include <core/debughelper.h>

#include "source.h"
#include "audiohelper.h"
#include "decoder.h"
#include "decoderplugin.h"
#include "buffer.h"
#include "listener.h"
#include "abstractplaylist.h"

using namespace GluonAudio;

class AudioFile::Private
{
    public:
        Private(AudioFile* p) : parent(p), valid(true) {}
        
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
        
        AudioFile* parent;
        QString file;
        bool valid;
        QList<SourceData*> dataList;
};

AudioFile::AudioFile(QString file, QObject* parent)
    : QObject(parent)
    , d(new Private(this))
{
    DEBUG_BLOCK
    d->file = file;
    if( AudioHelper::instance()->decoderPlugins().empty() )
    {
        DEBUG_TEXT( "No decoder plugins found!" )
        d->valid = false;
    }
}

AudioFile::~AudioFile()
{
    delete d;
}

bool AudioFile::isValid()
{
    return d->valid;
}

void AudioFile::feedSource(Source* source)
{
    if( !d->valid )
        return;
    if( d->dataList.empty() )
        AudioHelper::instance()->registerForUpdates(this);
    Private::SourceData* data = new Private::SourceData();
    data->source = source;
    data->dec = AudioHelper::instance()->decoderPlugins()[0]->createDecoder(d->file);
    data->isDecoding = false;
    d->dataList.prepend(data);
    source->audioFileAdded();
}

void AudioFile::stopFeedingSource(Source* source)
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

void AudioFile::update()
{
    if( !d->valid )
        return;
    for( Private::SourceData* data : d->dataList )
    {
        if( !data->dec->isValid() )
        {
            DEBUG_BLOCK
            DEBUG_TEXT( "Invalid decoder state..." )
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
            if( !Private::generateBuffer(&buffer, data->dec->isStereo()) )
            {
                data->source->stop();
                d->stopFeedingSource(data);
            }
            
            delete [] buffer.data;

            data->source->queueBuffer(buffer);
            remainingTimeInBuffer += buffer.length;
        }
        
        if( data->dec->isEndOfFile() )
        {
            data->source->playlist()->fileNearlyFinished();
            d->stopFeedingSource(data);
        }
    }
}

void AudioFile::Private::stopFeedingSource(AudioFile::Private::SourceData* data)
{
    data->dec->stopDecoding();
    delete data->dec;
    delete data;
    dataList.removeOne(data);
    if( dataList.empty() )
        AudioHelper::instance()->unregisterForUpdates(parent);
}

bool AudioFile::Private::generateBuffer( Buffer* buffer, bool isStereo )
{
    DEBUG_BLOCK
    ALenum format = isStereo ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
    Listener::instance();
    alGenBuffers( 1, &buffer->name );
    ALCenum error = alGetError();
    if( error != AL_NO_ERROR )
    {
        DEBUG_TEXT2( "OpenAL-Error while creating buffer: %1", error )
        return false;
    }
    alBufferData( buffer->name, format, (void*) buffer->data, buffer->size, buffer->frequency );
    error = alGetError();
    if( error != AL_NO_ERROR )
    {
        DEBUG_TEXT2( "OpenAL-Error while filling buffer: %1", error )
        return false;
    }
    return true;
}

void AudioFile::Private::initializeDecoding(AudioFile::Private::SourceData* data)
{
    if( data->dec->isStereo() )
        data->source->setGlobal( true );
    data->dec->startDecoding();
    data->isDecoding = true;
}

