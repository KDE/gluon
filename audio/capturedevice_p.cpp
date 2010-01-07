/*
   This file is part of Gluon Audio
   Copyright (C) 2009 Guillaume Martres <smarter@ubuntu.com>
   Copyright (C) 2010 Arjen Hiemstra <>

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

#include "capturedevice_p.h"

#ifdef Q_WS_X11
#include <AL/alc.h>
#endif
#ifdef Q_WS_MAC
#include <OpenAL/alc.h>
#endif

KALCaptureDevice::KALCaptureDevice(const QString &deviceName, int frequency, int format, int buffersize)
{
    m_device = alcCaptureOpenDevice(deviceName.toUtf8(), frequency, format, buffersize);
}

KALCaptureDevice::~KALCaptureDevice()
{
    alcCaptureCloseDevice(m_device);
}

ALCint KALCaptureDevice::samples()
{
    ALCint samples;
    alcGetIntegerv(m_device, ALC_CAPTURE_SAMPLES, 1, &samples);
    return samples;
}

ALshort KALCaptureDevice::startCapture(ALCsizei samples)
{
    ALshort capture;
    alcCaptureSamples(m_device, &capture, samples);
    return capture;
}

void KALCaptureDevice::stopCapture()
{
    alcCaptureStop(m_device);
}
