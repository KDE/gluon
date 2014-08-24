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

using namespace GluonAudio;

class AudioFile::Private
{
    public:
        Private(AudioFile* p) : parent(p), valid(false), maxBufferTime(20.0f) {}
        
        struct SourceData
        {
            Source* source;
            Decoder* dec;
            bool isDecoding;
            bool loopOnce;
            QList<Buffer> currentBuffers;
            float remainingTimeInBuffer;
        };
        
        void stopFeedingSource( SourceData* data );
        static bool generateBuffer( Buffer* buffer, bool isStereo );
        
        AudioFile* parent;
        QString file;
        bool valid;
        QList<SourceData*> dataList;
        float maxBufferTime;
};

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

AudioFile::AudioFile(QString file, QObject* parent)
    : QObject(parent)
    , d(new Private(this))
{
    d->file = file;
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
    if( d->dataList.empty() )
        AudioHelper::instance()->registerForUpdates(this);
    Private::SourceData* data = new Private::SourceData();
    data->source = source;
    data->dec = AudioHelper::instance()->decoderPlugins()[0]->createDecoder(d->file);
    data->isDecoding = false;
    data->remainingTimeInBuffer = 0.0f;
    data->loopOnce = false;
    d->dataList.prepend(data);
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
    for( Private::SourceData* data : d->dataList )
    {
        if( !data->dec->isValid() )
        {
            DEBUG_BLOCK
            DEBUG_TEXT( "Invalid decoder state..." )
            data->source->stop();
            d->stopFeedingSource(data);
            continue;
        }
        if( !data->isDecoding )
        {
            if( data->dec->isLoaded() )
            {
                if( data->dec->isStereo() )
                    data->source->setGlobal( true );
                data->dec->startDecoding();
                data->isDecoding = true;
            }
            return;
        }
        if( data->currentBuffers.count() > 0 )
        {
            int removed = data->source->removeOldBuffers();
            for( int i=0; i<removed; i++ )
                data->currentBuffers.removeLast();
        }
        data->remainingTimeInBuffer=0.0f;
        for( const Buffer& b : data->currentBuffers )
            data->remainingTimeInBuffer += b.length;
        
        while( data->remainingTimeInBuffer < d->maxBufferTime && data->dec->buffersAvailable() )
        {
            Buffer buffer = data->dec->getBuffer();
            if( !Private::generateBuffer(&buffer, data->dec->isStereo()) )
            {
                data->source->stop();
                d->stopFeedingSource(data);
            }

            data->source->queueBuffer(buffer.name);
            data->remainingTimeInBuffer += buffer.length;
            data->currentBuffers.prepend(buffer);
        }
        
        if( data->dec->isEndOfFile() )
        {
            d->stopFeedingSource(data);
        }
    }
}



