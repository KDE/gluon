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
#include "gluonvarianttypes.h"

namespace Gluon
{

class SoundListenerComponent : public Component
{
    Q_OBJECT
    Q_PROPERTY(bool active READ isActive WRITE setActive)
    Q_PROPERTY(bool effectsEnabled READ effectsEnabled WRITE setEffectsEnabled)

public:
    SoundListenerComponent(QObject *parent = 0);
    SoundListenerComponent(const Gluon::SoundListenerComponent &other);

    virtual GluonObject *instantiate();

    virtual void Update(int elapsedMilliseconds);

    void setActive(bool active);
    bool isActive() {
        if (m_activeInstance != this) {
            return false;
        }
        return true;
    }

    void setEffectsEnabled(bool enable);
    bool effectsEnabled() {
        return m_effectsEnabled;
    }

    static SoundListenerComponent *activeInstance();

private:
    bool m_effectsEnabled;

    static SoundListenerComponent *m_activeInstance;
};

}

#endif // SOUNDLISTENERCOMPONENT_H
