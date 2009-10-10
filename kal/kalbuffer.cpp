/*
* This file is part of the Gluon project.
* Copyright (C) 2009 Sacha Schutz <istdasklar@free.fr>
* Copyright (C) 2009 Guillaume Martres <smarter@ubuntu.com>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; see the file COPYING.  If not, write to
* the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
* Boston, MA 02110-1301, USA.
*/

#include "kalbuffer.h"
#include "kalengine.h"
#include "kalsoundreader.h"

class KALBufferPrivate
{
public:
    ALuint buffer;
};


KALBuffer::KALBuffer()
    :d(new KALBufferPrivate)
{
    d->buffer=0;
    init();
}

KALBuffer::KALBuffer(const QString &fileName)
            :d(new KALBufferPrivate)

{
    d->buffer=0;
    setBuffer(fileName);
    init();
}

KALBuffer::KALBuffer(ALuint buffer)
            :d(new KALBufferPrivate)
{
    d->buffer= buffer;
    init();
}
void KALBuffer::setBuffer(ALuint buffer) {
    d->buffer = buffer;
}
bool KALBuffer::isEmpty()const {
    return !d->buffer;
}
void KALBuffer::setHelloWord() {
    d->buffer = alutCreateBufferHelloWorld();
}

void KALBuffer::init()
{
}

ALuint KALBuffer::buffer() const {
    return  d->buffer;
}

KALBuffer::~KALBuffer()
{
    alDeleteBuffers(1, &d->buffer);
    delete d;
}

void KALBuffer::setBuffer(const QString &fileName)
{
    KALSoundReader reader(fileName);
    if (reader.canRead()) {
        d->buffer = reader.alBuffer();
    }
}

ALfloat KALBuffer::duration() const
{
    ALint size= 0.f;
    ALint bits= 0.f;
    ALint channels= 0.f;
    ALint frequency= 0.f;

    alGetBufferi( d->buffer,AL_SIZE,&size);
    alGetBufferi( d->buffer,AL_BITS,&bits);
    alGetBufferi( d->buffer,AL_CHANNELS,&channels);
    alGetBufferi( d->buffer,AL_FREQUENCY,&frequency);

    ALfloat sample = size/channels*8/bits;
    ALfloat dur = (float)sample/frequency;

    //
    //    <KittyCat> then size/channels*8/bits is the number of samples
    //[14:42] <KittyCat> and samples/(float)frequency is the time is seconds

    return dur;

}
