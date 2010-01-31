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

#ifndef GLUON_ENGINE_SOUNDLISTENERCOMPONENT_H
#define GLUON_ENGINE_SOUNDLISTENERCOMPONENT_H

#include <core/gluonvarianttypes.h>
#include <engine/component.h>
#include <engine/gluon_engine_export.h>

namespace GluonEngine
{

class GLUON_ENGINE_EXPORT SoundListenerComponent : public Component
{
    Q_OBJECT
    Q_PROPERTY(bool active READ isActive WRITE setActive)
    Q_PROPERTY(bool effectsEnabled READ effectsEnabled WRITE setEffectsEnabled)

    Q_INTERFACES(GluonEngine::Component)

public:
    SoundListenerComponent(QObject *parent = 0);
    SoundListenerComponent(const SoundListenerComponent &other);

    virtual GluonCore::GluonObject *instantiate();

    virtual void Update(int elapsedMilliseconds);

    void setActive(bool active);
    bool isActive() {
        return m_activeInstance == this;
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

#endif // GLUON_ENGINE_SOUNDLISTENERCOMPONENT_H
