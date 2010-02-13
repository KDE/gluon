/*
* This file is part of the Gluon project.
* Copyright (C) 2009 Sacha Schutz <istdasklar@free.fr>
* Copyright (C) 2009 Guillaume Martres <smarter@ubuntu.com>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; see the file COPYING.  If not, write to
* the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
* Boston, MA 02110-1301, USA.
*/

#ifndef GLUON_AUDIO_ENGINE_H
#define GLUON_AUDIO_ENGINE_H

#include "gluon_audio_export.h"

#include <QtCore/QObject>
#include <QtCore/QStringList>

#include <alc.h>

#include <core/singleton.h>
#include <Eigen/Geometry>

namespace GluonAudio
{
    class Sound;
    class Buffer;

    class GLUON_AUDIO_EXPORT Engine : public GluonCore::Singleton<Engine>
    {
    public:
        /**
        * Change the output device to the specified OpenAL device name
        * @param deviceName the OpenAL device name
        * @return true if the new device was successfuly set, false otherwise
        * @see deviceList, setCategory
        */
        bool setDevice(const QString &deviceName);

        static ALCcontext *context() {
            return instance()->getAlContext();
        }

        static ALCdevice* device() {
            return instance()->getAlDevice();
        }

        Eigen::Vector3f listenerPosition();
        void setListenerPosition(const Eigen::Vector3f& position);


        /**
        * @return a QStringList of the available output devices
        * @see setDevice
        */
        static QStringList deviceList();

        static void close() {
            delete instance();
        }

        ALCdevice *getAlDevice() {
            return m_device;
        }

        ALCcontext *getAlContext() {
            return m_context;
        }
        void alcList(const char* arg1);

    private:
        friend class GluonCore::Singleton<Engine>;

        Engine();
        ~Engine();

        Q_DISABLE_COPY(Engine)

        ALCcontext *m_context;
        ALCdevice *m_device;
    };
}

#endif // GLUON_AUDIO_ENGINE_H
