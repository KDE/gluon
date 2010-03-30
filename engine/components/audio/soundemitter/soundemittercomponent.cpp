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

#include <audio/engine.h>
#include <audio/sound.h>
#include <engine/assets/audio/sound/soundasset.h>
#include <engine/gameobject.h>

REGISTER_OBJECTTYPE(GluonEngine, SoundEmitterComponent)

using namespace GluonEngine;

SoundEmitterComponent::SoundEmitterComponent(QObject *parent)
        : Component(parent),
        m_sound(0)
{
    //QVariant somethingEmpty;

    /*SoundAsset *theObject = m_soundAsset;
    somethingEmpty.setValue<GluonEngine::SoundAsset*>(theObject);
    setProperty("sound", somethingEmpty);*/
}

SoundEmitterComponent::SoundEmitterComponent(const GluonEngine::SoundEmitterComponent &other)
        : Component(other)
{
}

void
SoundEmitterComponent::play()
{
    m_sound->play();
}

Asset *
SoundEmitterComponent::sound()
{
    return m_soundAsset;
    //return property("sound").value<GluonEngine::SoundAsset*>();
}

void
SoundEmitterComponent::setSound(Asset* asset)
{
    m_soundAsset = asset;
    //QVariant theNewValue;
    //theNewValue.setValue<GluonEngine::SoundAsset*>(asset);
    //setProperty("sound", theNewValue);
    //m_sound->load(asset->buffer());
}

void
SoundEmitterComponent::start()
{
    m_sound = new GluonAudio::Sound();
}

void
SoundEmitterComponent::draw(int timeLapse)
{
    Q_UNUSED(timeLapse);
    m_sound->setPosition(gameObject()->position());

    if (m_sound->isLooping() && !m_sound->isPlaying())
        m_sound->play();
}

void
SoundEmitterComponent::update(int elapsedMilliseconds)
{
    Q_UNUSED(elapsedMilliseconds)
}

bool
SoundEmitterComponent::isLooping()
{

}

void
SoundEmitterComponent::setLoop(bool loop)
{

}


/*void SoundEmitterComponent::stop()
{
    m_sound->stop();
}*/


Q_EXPORT_PLUGIN2(gluon_component_soundemitter, GluonEngine::SoundEmitterComponent)

#include "soundemittercomponent.moc"
