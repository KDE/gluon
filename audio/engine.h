/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2009 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2009-2011 Guillaume Martres <smarter@ubuntu.com>
 * Copyright (C) 2010 Laszlo Papp <lpapp@kde.org>
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

#ifndef GLUON_AUDIO_ENGINE_H
#define GLUON_AUDIO_ENGINE_H

#include "gluon_audio_export.h"

#include <core/singleton.h>

#include <QtGui/QVector3D>

namespace GluonAudio
{
    class Sound;

    class GLUON_AUDIO_EXPORT Engine : public GluonCore::Singleton<Engine>
    {
            Q_OBJECT
            GLUON_SINGLETON( Engine )
        public:
            /**
            * Change the output device to the specified OpenAL device name
            * @param deviceName the OpenAL device name
            * @return true if the new device was successfuly set, false otherwise
            * @see deviceList, setCategory
            */
            bool setDevice( const QString& deviceName );

            /**
            * Position of the listener in 3D
            * @see Sound::setPosition
            */
            QVector3D listenerPosition();
            void setListenerPosition( const QVector3D& position );


            /**
            * @return a QStringList of the available output devices
            * @see setDevice
            */
            static QStringList deviceList();

            /**
             * Length of a buffer in microseconds when streaming a file
             * Any file whose duration is bigger than this times buffersPerStream()
             * will be streamed when called as an argument of Sound::Sound(const QString&)
             * When a file is streamed, only part of it is in memory at a given time.
             * Default: 250000 microseconds
             * @see Sound::Sound
             */
            int bufferLength();
            void setBufferLength( int microsecs );

            /**
             * Number of buffers in memory at the same time when streaming a file
             * Default: 3 buffers per stream
             */
            int buffersPerStream();
            void setBuffersPerStream( int buffers );

            //FIXME: this shouldn't be public
            uint genBuffer( const QString& fileName );

        private:
            ~Engine();

            class EnginePrivate;
            EnginePrivate* const d;
    };
}

#endif // GLUON_AUDIO_ENGINE_H
