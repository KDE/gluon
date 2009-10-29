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

using namespace Gluon;

REGISTER_OBJECTTYPE(SoundListenerComponent)

SoundListenerComponent::SoundListenerComponent(QObject *parent)
    : Component(parent)
{
}

SoundListenerComponent::SoundListenerComponent(const Gluon::SoundListenerComponent &other)
    : Component(other)
{
}

GluonObject *SoundListenerComponent::instantiate()
{
    return new SoundListenerComponent(this);
}

void SoundListenerComponent::Update(int elapsedMilliseconds)
{
    if (!m_effectsEnabled) {
        return;
    }

    //TODO: implement GameObject/Component relation
    //m_position = m_gameObject->position();
}

void SoundListenerComponent::setActive(bool active)
{
    //GlobalComponent::instance()->setActiveListener(this);
    m_isActive = true;
}

void SoundListenerComponent::setEffectsEnabled(bool enable)
{
    m_effectsEnabled = enable;
}

Eigen::Vector3f SoundListenerComponent::position()
{
    Q_ASSERT(m_effectsEnabled);

    return m_position;
}

#include "soundlistenercomponent.moc"
