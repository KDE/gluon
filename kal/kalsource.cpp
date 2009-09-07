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

#include "kalsource.h"
#include "kalbuffer.h"
#include <sndfile.h>

#include <KDE/KApplication>
#include <KDE/KDebug>

#include "kalengine.h"


KALSource::KALSource(const QString &soundFile, QObject *parent)
        : QObject(parent)
{
    if (!QFile::exists(soundFile)) {
        kDebug() << "Could not open" << soundFile;
        return;
    }

    m_buffer = new KALBuffer(soundFile);
    init();
}

KALSource::KALSource(KALBuffer *buffer, QObject *parent)
{
    m_buffer = buffer;
    init();
}

KALSource::KALSource(ALuint buffer, QObject *parent)
{
    m_buffer = new KALBuffer();
    m_buffer->setBuffer(buffer);
    init();
}

KALSource::~KALSource()
{
    alDeleteSources(1, &m_source);
    KALEngine * engineParent = KALEngine::instance();
    engineParent->removeSource(this);
}

void KALSource::init()
{
    KALEngine *engineParent = KALEngine::instance();
    engineParent->addSource(this);
    setupSource();
}

void KALSource::setupSource()
{
    alGenSources(1, &m_source);  // Generate the source to play the buffer with
    alSourcei(m_source, AL_BUFFER, m_buffer->buffer());  // Attach source to buffer

    if (alGetError() != AL_NO_ERROR) {
        kDebug() << "Could not process sound while generating source:" << alGetError();
        return;
    }

    if (!m_source) {
        kDebug() << "Could not process sound: generated source empty.";
        return;
    }
}

void KALSource::updateSource()
{
//    stop();
//    alDeleteSources(1, &m_source);
//    //alDeleteBuffers(1, &m_buffer);
//    m_setupSource();
}

ALfloat KALSource::elapsedTime()
{
    ALfloat seconds = 0.f;
    alGetSourcef(m_source, AL_SEC_OFFSET, &seconds);
    return seconds;
}

ALint KALSource::status()
{
    ALint status;
    alGetSourcei(m_source, AL_SOURCE_STATE, &status);
    return status;
}

void KALSource::loop(bool enabled)
{
    alSourcei(m_source, AL_LOOPING, enabled);
}

ALfloat KALSource::x()
{
    return m_x;
}

ALfloat KALSource::y()
{
    return m_y;
}

ALfloat KALSource::z()
{
    return m_z;
}

ALfloat KALSource::gain()
{
    return m_gain;
}

ALfloat KALSource::pitch()
{
    return m_pitch;
}

void KALSource::setPosition(ALfloat x, ALfloat y, ALfloat z)
{
    m_x = x;
    m_y = y;
    m_z = z;

    ALfloat listenerPosition[] = { x, y, z };
    alSourcefv(m_source, AL_POSITION, listenerPosition);
}

void KALSource::setGain(ALfloat volume)
{
    m_gain = volume;
    alSourcef(m_source, AL_GAIN, volume);
}

void KALSource::setPitch(ALfloat pitch)
{
    m_pitch = pitch;
    alSourcef(m_source, AL_PITCH, pitch);
}

void KALSource::play()
{
    alSourcePlay(m_source);
}

void KALSource::pause()
{
    alSourcePause(m_source);
}

void KALSource::stop()
{
    alSourceStop(m_source);
}

void KALSource::rewind()
{
    alSourceRewind(m_source);
}

void KALSource::setMinGain(ALfloat min)
{
    alSourcef(m_source, AL_MIN_GAIN, min);
}

void KALSource::setMaxGain(ALfloat max)
{
    alSourcef(m_source, AL_MAX_GAIN, max);
}

void KALSource::setVelocity(ALfloat vx, ALfloat vy, ALfloat vz)
{
    ALfloat velocity[] = { vx, vy, vz };
    alSourcefv(m_source, AL_VELOCITY, velocity);
}

void KALSource::setDirection(ALfloat dx, ALfloat dy, ALfloat dz)
{
    ALfloat direction[] = { dx, dy, dz };
    alSourcefv(m_source, AL_POSITION, direction);
}
