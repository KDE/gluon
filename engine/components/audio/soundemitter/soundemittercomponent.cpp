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
Q_DECLARE_METATYPE(GluonEngine::SoundAsset*);

using namespace GluonEngine;

SoundEmitterComponent::SoundEmitterComponent(QObject *parent)
    : Component(parent),
      m_sound(0)
{
    #warning Q_PROPERTY does not currently handle namespaced types - see bugreports.qt.nokia.com/browse/QTBUG-2151
    QVariant somethingEmpty;
    SoundAsset *theObject = m_soundAsset;
    somethingEmpty.setValue<GluonEngine::SoundAsset*>(theObject);
    setProperty("sound", somethingEmpty);
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

SoundAsset *
SoundEmitterComponent::sound()
{
    //return m_soundAsset;
    return property("sound").value<GluonEngine::SoundAsset*>();
}

void
SoundEmitterComponent::setSound(SoundAsset *asset)
{
    m_soundAsset = asset;
    QVariant theNewValue;
    theNewValue.setValue<GluonEngine::SoundAsset*>(asset);
    setProperty("sound", theNewValue);
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

    if(m_sound->isLooping() && !m_sound->isPlaying())
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
