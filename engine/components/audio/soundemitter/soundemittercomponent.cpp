/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Guillaume Martres <smarter@ubuntu.com>
 * Copyright (c) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

#include "soundemittercomponent.h"

#include <core/debughelper.h>
#include <audio/engine.h>
#include <audio/sound.h>
#include <engine/assets/audio/sound/soundasset.h>
#include <engine/gameobject.h>
#include <core/metainfo.h>

#include <QtCore/QDebug>
#include <QMimeData>

REGISTER_OBJECTTYPE(GluonEngine, SoundEmitterComponent)

using namespace GluonEngine;

class SoundEmitterComponent::SoundEmitterComponentPrivate
{
    public:
        SoundEmitterComponentPrivate()
            : asset(0)
            , sound(0)
            , buffer(0)
            , radius(10000.0f)
            , volume(1.0f)
            , pitch(1.0f)
            , loop(false)
            , autoPlay(false)
            {}

        Asset *asset;
        GluonAudio::Sound *sound;
        GluonAudio::Buffer *buffer;
        float radius;
        float volume;
        float pitch;
        bool loop;
        bool autoPlay;
};

SoundEmitterComponent::SoundEmitterComponent(QObject *parent)
    : Component(parent)
    , d(new SoundEmitterComponentPrivate)
{
    metaInfo()->setPropertyRange("pitch", 0.5, 2.0);
}

SoundEmitterComponent::SoundEmitterComponent(const GluonEngine::SoundEmitterComponent &other)
    : Component(other)
    , d(other.d)
{
}

SoundEmitterComponent::~SoundEmitterComponent()
{
    stop();
    delete d;
}

QString SoundEmitterComponent::category() const
{
    return QString("Audio");
}

void SoundEmitterComponent::play()
{
    d->sound->play();
}

Asset *SoundEmitterComponent::sound()
{
    return d->asset;
}

void SoundEmitterComponent::setSound(Asset *asset)
{
    d->asset = asset;

    if (d->sound && asset->data()->hasFormat("application/gluon-audio-buffer")) {
        d->sound->stop();
        d->buffer->setBuffer(asset->data()->data("application/gluon-audio-buffer").toUInt(), true);
        d->sound->load(d->buffer);
    }
}

void SoundEmitterComponent::initialize()
{
    if (!d->sound)
        d->sound = new GluonAudio::Sound();

    if (!d->buffer)
        d->buffer = new GluonAudio::Buffer();
}

void SoundEmitterComponent::start()
{
    if (d->asset) {
        if (!d->asset->isLoaded()) d->asset->load();

        if (d->asset->data()->hasFormat("application/gluon-audio-buffer")) {
            d->buffer->setBuffer(d->asset->data()->data("application/gluon-audio-buffer").toUInt(), true);
        }
    }

    d->sound->load(d->buffer);
    d->sound->setPosition(gameObject()->position());
    d->sound->setRadius(d->radius);
    d->sound->setVolume(d->volume);
    d->sound->setPitch(d->pitch);
    d->sound->setLoop(d->loop);

    if (d->autoPlay)
        d->sound->play();
}

void SoundEmitterComponent::draw(int timeLapse)
{
    Q_UNUSED(timeLapse);
    if (d->sound)
      d->sound->setPosition(gameObject()->position());
}

void SoundEmitterComponent::stop()
{
    if (d->sound) {
        d->sound->stop();
    }
}

void SoundEmitterComponent::cleanup()
{
    delete d->sound;

    d->sound = 0;
    d->buffer = 0;
}

float SoundEmitterComponent::radius() const
{
    return d->radius;
}

void SoundEmitterComponent::setRadius(float radius)
{
    if (d->sound)
        d->sound->setRadius(radius);
    d->radius = radius;
}

float SoundEmitterComponent::volume() const
{
    return d->volume;
}

void SoundEmitterComponent::setVolume(float volume)
{
    d->volume = volume;
    if (d->sound)
        d->sound->setVolume(volume);
}

float SoundEmitterComponent::pitch() const
{
    return d->pitch;
}

void SoundEmitterComponent::setPitch(float pitch)
{
    d->pitch = pitch;
    if (d->sound)
        d->sound->setPitch(pitch);
}

bool SoundEmitterComponent::isLooping() const
{
    return d->loop;
}

bool SoundEmitterComponent::isPlaying() const
{
    if (d->sound) {
        return d->sound->isPlaying();
    }
    return false;
}

void SoundEmitterComponent::setLoop(bool loop)
{
    d->loop = loop;

    if (d->sound) {
        d->sound->setLoop(loop);
        if (loop) {
            d->sound->play();
        } else if (d->sound->isPlaying()) {
            d->sound->stop();
        }
    }
}

bool SoundEmitterComponent::autoPlay() const
{
    return d->autoPlay;
}

void SoundEmitterComponent::setAutoPlay(bool autoPlay)
{
    d->autoPlay = autoPlay;
}

Q_EXPORT_PLUGIN2(gluon_component_soundemitter, GluonEngine::SoundEmitterComponent)

#include "soundemittercomponent.moc"
