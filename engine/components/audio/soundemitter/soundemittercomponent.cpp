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

#include <QtCore/QDebug>

#include <core/debughelper.h>
#include <audio/engine.h>
#include <audio/sound.h>
#include <engine/assets/audio/sound/soundasset.h>
#include <engine/gameobject.h>
#include <QMimeData>

REGISTER_OBJECTTYPE(GluonEngine, SoundEmitterComponent)

using namespace GluonEngine;

class SoundEmitterComponent::SoundEmitterComponentPrivate
{
    public:
        SoundEmitterComponentPrivate() { asset = 0; sound = 0; buffer = 0; loop = false; }
        
        Asset *asset;
        
        GluonAudio::Sound *sound;
        GluonAudio::Buffer *buffer;
        bool loop;
};

SoundEmitterComponent::SoundEmitterComponent(QObject *parent)
        : Component(parent), 
        d(new SoundEmitterComponentPrivate)
{

}

SoundEmitterComponent::SoundEmitterComponent(const GluonEngine::SoundEmitterComponent &other)
        : Component(other),
        d(other.d)
{
}

SoundEmitterComponent::~SoundEmitterComponent()
{
    stop();
    
    delete d;
}

void
SoundEmitterComponent::play()
{
    d->sound->play();
}

Asset *
SoundEmitterComponent::sound()
{
    return d->asset;
}

void
SoundEmitterComponent::setSound(Asset* asset)
{
    d->asset = asset;
    
    if(d->sound && asset->data()->hasFormat("application/gluon-audio-buffer"))
    {
        d->sound->stop();
        d->buffer->setBuffer(asset->data()->data("application/gluon-audio-buffer").toUInt(), true);
        d->sound->load(d->buffer);
    }
}

void
SoundEmitterComponent::start()
{
    DEBUG_FUNC_NAME
    if(!d->sound)
        d->sound = new GluonAudio::Sound();
    
    if(!d->buffer)
        d->buffer = new GluonAudio::Buffer();
    
    if(d->asset)
    {
        if(!d->asset->isLoaded()) 
            d->asset->load();
        
        if(d->asset->data()->hasFormat("application/gluon-audio-buffer")) 
        {
            DEBUG_TEXT(QString("Setting buffer to %1").arg(QString(d->asset->data()->data("application/gluon-audio-buffer"))));
            d->buffer->setBuffer(d->asset->data()->data("application/gluon-audio-buffer").toUInt(), true);
        }
    }
    
    d->sound->load(d->buffer);
    
    if(d->loop)
    {
        d->sound->setLoop(true);
        d->sound->play();
    }
}

void
SoundEmitterComponent::draw(int timeLapse)
{
    Q_UNUSED(timeLapse);
    d->sound->setPosition(gameObject()->position());
}

void
SoundEmitterComponent::update(int elapsedMilliseconds)
{
    Q_UNUSED(elapsedMilliseconds)
}

void SoundEmitterComponent::stop()
{
    if(d->sound)
    {
        d->sound->stop();
        
        delete d->sound;
        d->sound = 0;
        d->buffer = 0;
    }
}

bool
SoundEmitterComponent::isLooping()
{
    return d->loop;
}

bool SoundEmitterComponent::isPlaying()
{
    if(d->sound)
    {
        return d->sound->isPlaying();
    }
    return false;
}

void
SoundEmitterComponent::setLoop(bool loop)
{
    d->loop = loop;
    
    if(d->sound)
    {
        d->sound->setLoop(loop);
        if(loop)
        {
            d->sound->play();
        }
        else if(d->sound->isPlaying())
        {
            d->sound->stop();
        }
    }
}

Q_EXPORT_PLUGIN2(gluon_component_soundemitter, GluonEngine::SoundEmitterComponent)

#include "soundemittercomponent.moc"
