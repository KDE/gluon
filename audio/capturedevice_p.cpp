/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2009 Guillaume Martres <smarter@ubuntu.com>
 * Copyright (C) 2010 Arjen Hiemstra <>
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
#include "capturedevice_p.h"

#ifdef Q_WS_X11
#include <AL/alc.h>
#endif
#ifdef Q_WS_MAC
#include <OpenAL/alc.h>
#endif

using namespace GluonAudio;

CaptureDevice::CaptureDevice(const QString &deviceName, int frequency, int format, int buffersize)
{
    m_device = alcCaptureOpenDevice(deviceName.toUtf8(), frequency, format, buffersize);
}

CaptureDevice::~CaptureDevice()
{
    alcCaptureCloseDevice(m_device);
}

ALCint CaptureDevice::samples()
{
    ALCint samples;
    alcGetIntegerv(m_device, ALC_CAPTURE_SAMPLES, 1, &samples);
    return samples;
}

ALshort CaptureDevice::startCapture(ALCsizei samples)
{
    ALshort capture;
    alcCaptureSamples(m_device, &capture, samples);
    return capture;
}

void CaptureDevice::stopCapture()
{
    alcCaptureStop(m_device);
}
