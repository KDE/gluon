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

#include "qtmmdecoder.h"

#include <QtMultimedia/QAudioDecoder>
#include <QtMultimedia/QAudioBuffer>
#include <QtMultimedia/QAudioFormat>
#include <QtCore/QIODevice>
#include <QtCore/QFile>
#include <QtCore/QDebug>

#include <core/log.h>

using namespace GluonAudio;

class QtMMDecoder::Private
{
    public:
        Private() : decoder(0), valid(false), loaded(false), finished(false) {}
        
        QAudioDecoder* decoder;
        bool valid;
        bool loaded;
        bool finished;
};

QtMMDecoder::QtMMDecoder(QString fileName, QObject* parent)
    : QObject(parent)
{
    d = new Private();
    d->decoder = new QAudioDecoder();
    d->valid = true;
    connect( d->decoder, SIGNAL(error(QAudioDecoder::Error)), this, SLOT(gotError(QAudioDecoder::Error)) );
    connect( d->decoder, SIGNAL(finished()), this, SLOT(gotFinished()) );
    connect( d->decoder, SIGNAL(formatChanged(const QAudioFormat&)), this, SLOT(gotFormatChanged(const QAudioFormat&)) );
    d->decoder->setSourceFilename( fileName );
    DEBUG() << QString("Loading %1...").arg(fileName);
    d->loaded = true;
}

QtMMDecoder::~QtMMDecoder()
{
    delete d->decoder;
    delete d;
}

void QtMMDecoder::startDecoding()
{
    QAudioFormat format;
    format.setCodec("audio/pcm");
    format.setSampleSize(16);
    format.setSampleType(QAudioFormat::SignedInt);
    format.setSampleRate(44100);
    format.setChannelCount(1);
    d->decoder->setAudioFormat(format);
    d->decoder->start();
}

void QtMMDecoder::stopDecoding()
{
    d->decoder->stop();
    d->finished = false;
}

void QtMMDecoder::setBufferSize(int bytes)
{   
}

bool QtMMDecoder::buffersAvailable()
{
    return d->decoder->bufferAvailable();
}

Buffer QtMMDecoder::getBuffer()
{
    Buffer buffer;
    QAudioBuffer b = d->decoder->read();
    buffer.data = new qint16[b.byteCount()/2];
    memcpy(buffer.data, b.constData<qint16>(), b.byteCount());
    buffer.size = b.byteCount();
    buffer.length = b.duration()/1000000.f;
    buffer.frequency = b.format().sampleRate();
    return buffer;
}

bool QtMMDecoder::isValid()
{
    return d->valid;
}

bool QtMMDecoder::isLoaded()
{
    return d->loaded;
}

float QtMMDecoder::duration()
{
    return d->decoder->duration() / 1000.f;
}

int QtMMDecoder::size()
{
    return d->decoder->audioFormat().bytesForDuration( d->decoder->duration() );
}

bool QtMMDecoder::isStereo()
{
    return d->decoder->audioFormat().channelCount() == 2;
}

bool QtMMDecoder::isEndOfFile()
{
    return d->finished && d->decoder->bufferAvailable();
}

void QtMMDecoder::gotError(QAudioDecoder::Error error)
{
    ERROR() << "Got an error in QtMMDecoder: " << d->decoder->errorString();
    d->valid = false;
}

void QtMMDecoder::gotFinished()
{
    d->finished = true;
}

void QtMMDecoder::gotFormatChanged(const QAudioFormat& format)
{
    DEBUG() << "Decoder loaded file";
    d->loaded = true;
}

