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

#ifndef GLUON_ENGINE_SOUNDEMITTERCOMPONENT_H
#define GLUON_ENGINE_SOUNDEMITTERCOMPONENT_H

#include <engine/gluon_engine_export.h>
#include <engine/component.h>

namespace GluonAudio {
    class Sound;
}

namespace GluonEngine
{
class SoundAsset;

class GLUON_ENGINE_EXPORT SoundEmitterComponent : public Component
{
    Q_OBJECT
    Q_PROPERTY(SoundAsset *sound READ sound WRITE setSound)
    Q_PROPERTY(bool loop READ isLooping WRITE setLoop)
    Q_INTERFACES(GluonEngine::Component)

    public:
        SoundEmitterComponent(QObject *parent = 0);
        SoundEmitterComponent(const GluonEngine::SoundEmitterComponent &other);

        virtual GluonCore::GluonObject *instantiate();

        SoundAsset *sound() {
            return m_soundAsset;
        }

        void setSound(SoundAsset *asset);

        virtual void start();
        virtual void update(int elapsedMilliseconds);
        virtual void draw(int timeLapse = 0);

        void play();
        //void stop();

        bool isLooping();

    public slots:
        void setLoop(bool loop);

    private:
        GluonAudio::Sound *m_sound;
        SoundAsset *m_soundAsset;
};

}

#endif // GLUON_ENGINE_SOUNDEMITTERCOMPONENT_H
