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

#ifndef SOUNDLISTENERCOMPONENT_H
#define SOUNDLISTENERCOMPONENT_H

#include "component.h"
#include "common/ksingleton.h"
#include "src/gluonvarianttypes.h"

namespace Gluon
{

class SoundListenerComponent : public Component, public KSingleton<SoundListenerComponent>
{
    Q_OBJECT
    Q_PROPERTY(bool effectsEnabled READ effectsEnabled WRITE setEffectsEnabled)
    Q_PROPERTY(Eigen::Vector3f position READ position)

public:
    virtual void Update(int elapsedMilliseconds);

    void setEffectsEnabled(bool enable);
    bool effectsEnabled() {
        return m_effectsEnabled;
    }

    Eigen::Vector3f position();

private:
    bool m_effectsEnabled;
    Eigen::Vector3f m_position;
};

}

#endif // SOUNDLISTENERCOMPONENT_H
