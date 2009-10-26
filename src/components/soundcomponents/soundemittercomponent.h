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

#ifndef GLUON_SOUNDEMITTERCOMPONENT_H
#define GLUON_SOUNDEMITTERCOMPONENT_H

#include "gluon/component.h"

class KALSound;

namespace Gluon
{
class SoundAsset;

class SoundEmitterComponent : public Component
{
    Q_OBJECT
    Q_PROPERTY(SoundAsset *sound READ sound WRITE setSound)

public:
    SoundEmitterComponent(QObject *parent = 0);
    SoundEmitterComponent(const Gluon::SoundEmitterComponent &other);

    virtual GluonObject *instantiate();

    SoundAsset *sound() {
        return m_soundAsset;
    }

    void setSound(SoundAsset *asset);

private:
    virtual void Update(int elapsedMilliseconds);
    KALSound *m_sound;
    SoundAsset *m_soundAsset;
};

}

#endif // GLUON_SOUNDEMITTERCOMPONENT_H
