/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2009 Guillaume Martres <smarter@ubuntu.com>
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

#ifndef CAPTUREDEVICE_P_H
#define CAPTUREDEVICE_P_H

#include "device_p.h"

#ifdef Q_WS_X11
#include <AL/al.h>
#elif defined(Q_WS_MAC)
#include <OpenAL/al.h>
#elif defined(Q_WS_WIN)
#include <AL/al.h>
#endif


namespace GluonAudio
{

    class CaptureDevice : public Device
    {
        public:
            explicit CaptureDevice( const QString& deviceName = QString(), int frequency = 44100, int format = AL_FORMAT_MONO16, int buffersize = 44100 );
            ~CaptureDevice();

            ALCint samples();

            ALshort startCapture( ALCsizei samples );
            void stopCapture();
    };
}

#endif // GLUON_AUDIO_CAPTUREDEVICE_H
