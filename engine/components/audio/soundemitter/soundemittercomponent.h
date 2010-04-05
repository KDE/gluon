/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Guillaume Martres <smarter@ubuntu.com>
 * Copyright (c) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef GLUON_ENGINE_SOUNDEMITTERCOMPONENT_H
#define GLUON_ENGINE_SOUNDEMITTERCOMPONENT_H

#include <engine/gluon_engine_export.h>
#include <engine/component.h>

namespace GluonEngine
{
    class Asset;

    class GLUON_ENGINE_EXPORT SoundEmitterComponent : public Component
    {
            Q_OBJECT
            Q_PROPERTY(GluonEngine::Asset* sound READ sound WRITE setSound)
            Q_PROPERTY(bool loop READ isLooping WRITE setLoop)
            Q_PROPERTY(bool autoPlay READ autoPlay WRITE setAutoPlay)


            Q_INTERFACES(GluonEngine::Component)
            GLUON_OBJECT(GluonEngine::SoundEmitterComponent)

        public:
            SoundEmitterComponent(QObject *parent = 0);
            SoundEmitterComponent(const GluonEngine::SoundEmitterComponent &other);
            ~SoundEmitterComponent();

            Asset *sound();
            
            virtual void initialize();
            virtual void start();
            virtual void draw(int timeLapse = 0);
            virtual void stop();
            virtual void cleanup();

            Q_INVOKABLE bool isLooping();
            Q_INVOKABLE bool isPlaying();
            Q_INVOKABLE bool autoPlay();

        public slots:
            Q_INVOKABLE void play();
            Q_INVOKABLE void setLoop(bool loop);
            Q_INVOKABLE void setSound(Asset *asset);
            Q_INVOKABLE void setAutoPlay(bool autoPlay);
            
        private:
            class SoundEmitterComponentPrivate;
            SoundEmitterComponentPrivate * const d;
    };

}

Q_DECLARE_METATYPE(GluonEngine::SoundEmitterComponent)
Q_DECLARE_METATYPE(GluonEngine::SoundEmitterComponent*)

#endif // GLUON_ENGINE_SOUNDEMITTERCOMPONENT_H
