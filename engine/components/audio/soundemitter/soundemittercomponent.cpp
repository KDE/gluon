/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "soundemittercomponent.h"

#include <QtCore/QDebug>

#include <audio/engine.h>
#include <audio/sound.h>
#include <engine/assets/audio/sound/soundasset.h>
#include <engine/gameobject.h>

REGISTER_OBJECTTYPE(GluonEngine,SoundEmitterComponent)

using namespace GluonEngine;

SoundEmitterComponent::SoundEmitterComponent(QObject *parent)
    : Component(parent),
      m_sound(0)
{
}

SoundEmitterComponent::SoundEmitterComponent(const GluonEngine::SoundEmitterComponent &other)
    : Component(other)
{
}

GluonCore::GluonObject *SoundEmitterComponent::instantiate()
{
    return new SoundEmitterComponent(this);
}


void SoundEmitterComponent::play()
{
    GluonAudio::Engine::instance();

    m_sound->play();
}

void SoundEmitterComponent::stop()
{
    m_sound->stop();
}

void SoundEmitterComponent::setSound(SoundAsset *asset)
{
    if (m_sound) {
        m_sound->deleteLater();
        m_sound = 0;
    }

    m_soundAsset = asset;
    m_sound = new GluonAudio::Sound(m_soundAsset->buffer());
}

void SoundEmitterComponent::update(int elapsedMilliseconds)
{
    Q_UNUSED(elapsedMilliseconds)

    m_sound->setPosition(gameObject()->worldPosition());
}

Q_EXPORT_PLUGIN2(gluon_component_soundemitter, GluonEngine::SoundEmitterComponent)

#include "soundemittercomponent.moc"
