/*
* This file is part of the KALEngine project.
* Copyright (C) 2007 Laurent Gomila <laurent.gom@gmail.com>
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

#include "kalsource.h"
#include "kalengine.h"
#include "kalsoundloader.h"
#include "kalbuffer.h"
#include <sndfile.h>

#include <KDE/KApplication>
#include <KDE/KDebug>

class KALSourcePrivate
{
public:
    KALSourcePrivate()
            : source(0) {}

    /**
    * @internal
    */
    void setupSource();

    KALEngine *parentEngine;
    bool toPlay;
    KALBuffer buffer;
    ALuint source;
    ALfloat x;
    ALfloat y;
    ALfloat z;
    ALfloat gain;
    ALfloat pitch;
};

KALSource::KALSource(const QString &_soundFile, KALEngine *parent)
        : QObject(parent)
{
    d = new KALSourcePrivate();
    d->parentEngine = parent;

    QString soundFile;

    if (KApplication::instance()) {
        QString soundFile = KALSoundLoader::global()->soundPath(_soundFile);
    }

    if (soundFile.isEmpty()) {
        soundFile = _soundFile;
    }

    if (!QFile::exists(soundFile)) {
        kError() << "Could not open" << soundFile;
    }

    if (soundFile.isEmpty()) {
        d->buffer.setHelloWord();
    } else {
        d->buffer.setBuffer(soundFile);
    }

    if (alGetError() != AL_NO_ERROR) {
        kError() << "Could not process sound while creating buffer:" << alGetError();
        return;
    }

    if (d->buffer.isEmpty()) {
        kError() << "Could not process sound: buffer empty.";
        return;
    }

    d->setupSource();

    connect(parentEngine(), SIGNAL(deviceChanged(QString)), this, SLOT(updateSource()));
}


KALSource::KALSource(KALBuffer buffer, KALEngine *parent)
{
d = new KALSourcePrivate();
d->parentEngine = parent;
d->buffer = buffer;
d->setupSource();
connect(parentEngine(), SIGNAL(deviceChanged(QString)), this, SLOT(updateSource()));
}

KALSource::KALSource(ALuint buffer, KALEngine *parent)
{
d = new KALSourcePrivate();
d->parentEngine = parent;
d->buffer.setBuffer(buffer);
d->setupSource();
connect(parentEngine(), SIGNAL(deviceChanged(QString)), this, SLOT(updateSource()));


}
KALSource::~KALSource()
{
    alDeleteSources(1, &d->source);

}

void KALSourcePrivate::setupSource()
{
    alGenSources(1, &source);  // Generate the source to play the buffer with
    alSourcei(source, AL_BUFFER, buffer.buffer());  // Attach source to buffer

    if (alGetError() != AL_NO_ERROR) {
        kError() << "Could not process sound while generating source:" << alGetError();
        return;
    }

    if (!source) {
        kError() << "Could not process sound: generated source empty.";
        return;
    }
}

void KALSource::updateSource()
{
    stop();

    alDeleteSources(1, &d->source);
    //alDeleteBuffers(1, &d->buffer);
    d->setupSource();
}

ALfloat KALSource::elapsedTime()
{
    ALfloat seconds = 0.f;
    alGetSourcef(d->source, AL_SEC_OFFSET, &seconds);
    return seconds;
}

ALint KALSource::status()
{
    ALint status;
    alGetSourcei(d->source, AL_SOURCE_STATE, &status);
    return status;
}

void KALSource::loop(bool enabled)
{
    alSourcei(d->source, AL_LOOPING, enabled);
}

ALfloat KALSource::x()
{
    return d->x;
}

ALfloat KALSource::y()
{
    return d->y;
}

ALfloat KALSource::z()
{
    return d->z;
}

ALfloat KALSource::gain()
{
    return d->gain;
}

ALfloat KALSource::pitch()
{
    return d->pitch;
}

KALEngine* KALSource::parentEngine()
{
    return d->parentEngine;
}

void KALSource::setPosition(ALfloat x, ALfloat y, ALfloat z)
{
    d->x = x;
    d->y = y;
    d->z = z;

    ALfloat listenerPosition[] = { x, y, z };
    alSourcefv(d->source, AL_POSITION, listenerPosition);
}

void KALSource::setGain(ALfloat volume)
{
    d->gain = volume;
    alSourcef(d->source, AL_GAIN, volume);
}

void KALSource::setPitch(ALfloat pitch)
{
    d->pitch = pitch;
    alSourcef(d->source, AL_PITCH, pitch);
}

void KALSource::play()
{
    alSourcePlay(d->source);
}

void KALSource::pause()
{
    alSourcePause(d->source);
}

void KALSource::stop()
{
    alSourceStop(d->source);
}

void KALSource::rewind()
{
    alSourceRewind(d->source);
}

void KALSource::setMinGain(ALfloat min)
{
    alSourcef(d->source, AL_MIN_GAIN, min);
}
void KALSource::setMaxGain(ALfloat max)
{
    alSourcef(d->source, AL_MAX_GAIN, max);
}
void KALSource::setVelocity(ALfloat vx, ALfloat vy, ALfloat vz)
{
    ALfloat velocity[] = { vx, vy, vz };
    alSourcefv(d->source, AL_VELOCITY, velocity);
}
void KALSource::setDirection(ALfloat dx, ALfloat dy, ALfloat dz)
{
    ALfloat direction[] = { dx, dy, dz };
    alSourcefv(d->source, AL_POSITION, direction);
}