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

#include "soundlistenercomponent.h"
#include <audio/engine.h>
#include <gameobject.h>

REGISTER_OBJECTTYPE(GluonEngine,SoundListenerComponent)

using namespace GluonEngine;

SoundListenerComponent *SoundListenerComponent::m_activeInstance = 0;

SoundListenerComponent::SoundListenerComponent(QObject *parent)
    : Component(parent)
{
}

SoundListenerComponent::SoundListenerComponent(const SoundListenerComponent &other)
    : Component(other)
{
}

GluonCore::GluonObject *SoundListenerComponent::instantiate()
{
    return new SoundListenerComponent(this);
}

void SoundListenerComponent::start()
{
}

void SoundListenerComponent::draw(int timeLapse)
{
    Q_UNUSED(timeLapse);

    if(isActive())
        GluonAudio::Engine::instance()->setListenerPosition(gameObject()->position());
}

void SoundListenerComponent::update(int elapsedMilliseconds)
{
    Q_UNUSED(elapsedMilliseconds)
}

void SoundListenerComponent::setActive(bool active)
{
    if(active)
        m_activeInstance = this;
}

void SoundListenerComponent::setEffectsEnabled(bool enable)
{
    m_effectsEnabled = enable;
}

SoundListenerComponent *SoundListenerComponent::activeInstance()
{
    return m_activeInstance;
}

Q_EXPORT_PLUGIN2(gluon_component_soundlistener, GluonEngine::SoundListenerComponent)

#include "soundlistenercomponent.moc"
