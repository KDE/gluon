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

#include "soundlistenercomponent.h"
#include "kal/kalengine.h"
#include "kal/kalsound.h"
#include "assets/soundasset/soundasset.h"
#include "gameproject/gameobject.h"

#include <QtCore/QDebug>

REGISTER_OBJECTTYPE(Gluon,SoundEmitterComponent)

using namespace Gluon;
using namespace Eigen;

SoundEmitterComponent::SoundEmitterComponent(QObject *parent)
    : Component(parent),
      m_sound(0)
{
}

SoundEmitterComponent::SoundEmitterComponent(const Gluon::SoundEmitterComponent &other)
    : Component(other)
{
}

GluonObject *SoundEmitterComponent::instantiate()
{
    return new SoundEmitterComponent(this);
}


void SoundEmitterComponent::play()
{
    KALEngine::instance();

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
    m_sound = new KALSound(m_soundAsset->buffer());
}

void SoundEmitterComponent::Update(int elapsedMilliseconds)
{
    SoundListenerComponent *listener = SoundListenerComponent::activeInstance();
    if (!listener->effectsEnabled()) {
        return;
    }

    Vector3f relativePosition = gameObject()->position() - listener->gameObject()->position();
    m_sound->setPosition(relativePosition);
}

#include "soundemittercomponent.moc"
