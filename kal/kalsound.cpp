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

#include "kalsound.h"
#include "kalbuffer.h"
#include <sndfile.h>

#include <QDebug>

#include "kalengine.h"

class KALSoundPrivate
{
public:
    KALBuffer *buffer;
    ALuint source;
    ALfloat x;
    ALfloat y;
    ALfloat z;
    ALfloat volume;
    ALfloat pitch;
};

KALSound::KALSound(QObject * parent)
           :QObject(parent),
           d(new KALSoundPrivate)
{
    init();
    d->buffer= new KALBuffer;
}
KALSound::KALSound(const QString &soundFile, QObject *parent)
    : QObject(parent),
    d(new KALSoundPrivate)
{
    init();
    d->buffer = new KALBuffer;
    load(soundFile);
}

KALSound::KALSound(KALBuffer *buffer, QObject *parent)
    :QObject(parent),
    d(new KALSoundPrivate)
{
    init();
    load(buffer);
}

KALSound::KALSound(ALuint buffer, QObject *parent)
    :QObject(parent),
    d(new KALSoundPrivate)
{
    init();
    load(buffer);
}

KALSound::~KALSound()
{
    alDeleteSources(1, &d->source);
    delete d;
}
void KALSound::load (const QString &soundFile)
{
    d->buffer->setBuffer(soundFile);
    setupSource();
}

void KALSound::load(KALBuffer * buffer) {
    d->buffer = buffer;
    setupSource();
}
void KALSound::load(ALuint buffer) {
    d->buffer = new KALBuffer(buffer);
    setupSource();
}

void KALSound::init()
{
    d->source=0;
    d->x=0;
    d->y=0;
    d->z=0;
    d->volume=0;
    d->pitch=0;
}

void KALSound::setupSource()
{
    alGenSources(1, &d->source);  // Generate the source to play the buffer with
    alSourcei(d->source, AL_BUFFER, d->buffer->buffer());  // Attach source to buffer

    if (alGetError() != AL_NO_ERROR) {
        qDebug() << "Could not process sound while generating source:" << alGetError();
        return;
    }

    if (!d->source) {
        qDebug() << "Could not process sound: generated source empty.";
        return;
    }
}
ALfloat KALSound::elapsedTime()const
{
    ALfloat seconds = 0.f;
    alGetSourcef(d->source, AL_SEC_OFFSET, &seconds);
    return seconds;
}

ALint KALSound::status()const
{
    ALint status;
    alGetSourcei(d->source, AL_SOURCE_STATE, &status);
    return status;
}

void KALSound::setLoop(bool enabled)
{
    alSourcei(d->source, AL_LOOPING, enabled);

}

ALfloat KALSound::x()const
{
    return d->x;
}

ALfloat KALSound::y()const
{
    return d->y;
}

ALfloat KALSound::z()const
{
    return d->z;
}

ALfloat KALSound::volume()const
{
    return d->volume;
}

ALfloat KALSound::pitch()const
{
    return d->pitch;
}

void KALSound::setPosition(ALfloat x, ALfloat y, ALfloat z)
{
    d->x = x;
    d->y = y;
    d->z = z;

    ALfloat listenerPosition[] = { x, y, z };
    alSourcefv(d->source, AL_POSITION, listenerPosition);
}

void KALSound::setVolume(ALfloat volume)
{
    d->volume = volume;
    alSourcef(d->source, AL_GAIN, volume);
}

void KALSound::setPitch(ALfloat pitch)
{
    d->pitch = pitch;
    alSourcef(d->source, AL_PITCH, pitch);
}

void KALSound::play()
{
    alSourcePlay(d->source);
}

void KALSound::pause()
{
    alSourcePause(d->source);
}

void KALSound::stop()
{
    alSourceStop(d->source);
}

void KALSound::rewind()
{
    alSourceRewind(d->source);
}

void KALSound::setMinVolume(ALfloat min)
{
    alSourcef(d->source, AL_MIN_GAIN, min);
}

void KALSound::setMaxVolume(ALfloat max)
{
    alSourcef(d->source, AL_MAX_GAIN, max);
}

void KALSound::setVelocity(ALfloat vx, ALfloat vy, ALfloat vz)
{
    ALfloat velocity[] = { vx, vy, vz };
    alSourcefv(d->source, AL_VELOCITY, velocity);
}

void KALSound::setDirection(ALfloat dx, ALfloat dy, ALfloat dz)
{
    ALfloat direction[] = { dx, dy, dz };
    alSourcefv(d->source, AL_POSITION, direction);
}

void KALSound::setTimePosition(ALfloat time)
{
    alSourcef(d->source, AL_SEC_OFFSET, time);

}
ALfloat KALSound::duration()const
{
    return d->buffer->duration();
}
ALuint  KALSound::source()const {
    return d->source;
}
