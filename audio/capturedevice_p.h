/*
   This file is part of the Gluon project.
   Copyright (C) 2009 Guillaume Martres <smarter@ubuntu.com>

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

#ifndef GLUON_AUDIO_CAPTUREDEVICE_H
#define GLUON_AUDIO_CAPTUREDEVICE_H

#include "device_p.h"

#ifdef Q_WS_X11
#include <AL/al.h>
#endif
#ifdef Q_WS_MAC
#include <OpenAL/al.h>
#endif

namespace GluonAudio
{

    class CaptureDevice : public Device
    {
        public:
            explicit CaptureDevice(const QString &deviceName = QString(), int frequency = 44100, int format = AL_FORMAT_MONO16, int buffersize = 44100);
            ~CaptureDevice();

            ALCint samples();

            ALshort startCapture(ALCsizei samples);
            void stopCapture();
    };
}

#endif // GLUON_AUDIO_CAPTUREDEVICE_H
