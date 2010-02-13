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

#include <sndfile.h>
#include <QtCore/QDebug>

#include "engine.h"
#include "sound.h"
#include "buffer.h"

using namespace GluonAudio;

class Sound::SoundPrivate
{
public:
    Buffer *buffer;
    ALuint source;
    QVector3D position;
    ALfloat volume;
    ALfloat pitch;
};

Sound::Sound(QObject * parent)
           :QObject(parent),
           d(new SoundPrivate)
{
    init();
    d->buffer= new Buffer;
}

Sound::Sound(const QString &soundFile, QObject *parent)
    : QObject(parent),
    d(new SoundPrivate)
{
    init();
    d->buffer = new Buffer;
    load(soundFile);
}

Sound::Sound(Buffer *buffer, QObject *parent)
    :QObject(parent),
    d(new SoundPrivate)
{
    init();
    load(buffer);
}

Sound::Sound(ALuint buffer, QObject *parent)
    :QObject(parent),
    d(new SoundPrivate)
{
    init();
    load(buffer);
}

Sound::~Sound()
{
    alDeleteSources(1, &d->source);
    if(d->buffer) delete d->buffer;
    delete d;
}
void Sound::load (const QString &soundFile)
{
    d->buffer->setBuffer(soundFile);
    setupSource();
}

void Sound::load(Buffer * buffer) {
    d->buffer = buffer;
    setupSource();
}
void Sound::load(ALuint buffer) {
    d->buffer = new Buffer(buffer);
    setupSource();
}

void Sound::init()
{
    d->source=0;
    d->position.setX(0);
    d->position.setY(0);
    d->position.setZ(0);
    d->volume=0;
    d->pitch=0;

    alGenSources(1, &d->source);  // Generate the source to play the buffer with
}

void Sound::setupSource()
{
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

ALfloat Sound::elapsedTime()const
{
    ALfloat seconds = 0.f;
    alGetSourcef(d->source, AL_SEC_OFFSET, &seconds);
    return seconds;
}

ALint Sound::status()const
{
    ALint status;
    alGetSourcei(d->source, AL_SOURCE_STATE, &status);
    return status;
}

void Sound::setLoop(bool enabled)
{
    alSourcei(d->source, AL_LOOPING, enabled);

}

QVector3D Sound::position() const
{
    return d->position;
}

ALfloat Sound::x()const
{
    return d->position.x();
}

ALfloat Sound::y()const
{
    return d->position.y();
}

ALfloat Sound::z()const
{
    return d->position.z();
}

ALfloat Sound::volume()const
{
    return d->volume;
}

ALfloat Sound::pitch()const
{
    return d->pitch;
}

void Sound::setPosition(ALfloat x, ALfloat y, ALfloat z)
{
    QVector3D tempPosition(x,y,z);

    setPosition(tempPosition);
}

void Sound::setPosition(QVector3D position)
{
    d->position = position;

    ALfloat sourcePosition[] = { position.x(), position.y() , position.z() };
    alSourcefv(d->source, AL_POSITION, sourcePosition);
}

void Sound::setVolume(ALfloat volume)
{
    d->volume = volume;
    alSourcef(d->source, AL_GAIN, volume);
}

void Sound::setPitch(ALfloat pitch)
{
    d->pitch = pitch;
    alSourcef(d->source, AL_PITCH, pitch);
}

void Sound::play()
{
    alSourcePlay(d->source);
}

void Sound::pause()
{
    alSourcePause(d->source);
}

void Sound::stop()
{
    alSourceStop(d->source);
}

void Sound::rewind()
{
    alSourceRewind(d->source);
}

void Sound::setMinVolume(ALfloat min)
{
    alSourcef(d->source, AL_MIN_GAIN, min);
}

void Sound::setMaxVolume(ALfloat max)
{
    alSourcef(d->source, AL_MAX_GAIN, max);
}

void Sound::setVelocity(ALfloat vx, ALfloat vy, ALfloat vz)
{
    ALfloat velocity[] = { vx, vy, vz };
    alSourcefv(d->source, AL_VELOCITY, velocity);
}

void Sound::setDirection(ALfloat dx, ALfloat dy, ALfloat dz)
{
    ALfloat direction[] = { dx, dy, dz };
    alSourcefv(d->source, AL_POSITION, direction);
}

void Sound::setTimePosition(ALfloat time)
{
    alSourcef(d->source, AL_SEC_OFFSET, time);

}
ALfloat Sound::duration()const
{
    return d->buffer->duration();
}
ALuint  Sound::source()const {
    return d->source;
}

#include "sound.moc"
