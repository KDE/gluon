/*
   This file is part of the Gluon project.
   Copyright (C) 2009 Sacha Schutz <istdasklar@free.fr>
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

#include "capture.h"
#include "capturedevice_p.h"

#include <QtCore/QtGlobal>
#include <QtCore/QDebug>
#include <QtCore/QTime>
#include <QtCore/QFile>

#ifdef Q_WS_X11
#include <AL/al.h>
#include <AL/alc.h>
#endif

#ifdef Q_WS_MAC
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#endif

#include <sndfile.h>

class KALCapturePrivate
{
public:
    KALCaptureDevice *captureDevice;
    QVector<ALshort> samples;
    ALuint buffer;
};

KALCapture::KALCapture(QString deviceName, QObject *parent)
    : QObject(parent),
    d(new KALCapturePrivate)
{
    if (isAvailable()) {
        d->captureDevice = new KALCaptureDevice(deviceName.toUtf8(), 44100, AL_FORMAT_MONO16, 44100);
    } else {
        qCritical() << "No capture device available";
        return;
    }

    if (!d->captureDevice) {
        qCritical() << "Could not set the capture device";
        return;
    }
}

KALCapture::~KALCapture()
{
    delete d->captureDevice;
    delete d;
}

bool KALCapture::isAvailable()const
{
    return KALDevice::isExtensionPresent("ALC_EXT_CAPTURE");
}

QStringList KALCapture::deviceList()
{
    return KALDevice::contextOption(ALC_CAPTURE_DEVICE_SPECIFIER);
}

void KALCapture::record(int duration)
{
    QTime recordTime;
    recordTime.start();

    while (recordTime.elapsed() < duration) {
        ALCint samples = d->captureDevice->samples();
        if (samples > 0) {
            //d->samples.append(samples);
            d->samples.append(d->captureDevice->startCapture(samples));
        }
    }

    d->captureDevice->stopCapture();

    //FIXME: Commented since it's duplicated from above, probably useless
//     ALCint samples = d->captureDevice->samples();
//     if (samples > 0) {
//         d->samples.append(samples);
//         d->samples.append(d->captureDevice->startCapture(samples));
//     }
}


void KALCapture::save(const QString& fileName)
{
    SF_INFO fileInfo;
    fileInfo.channels = 1;
    fileInfo.samplerate = 44100;
    fileInfo.format = SF_FORMAT_PCM_16 | SF_FORMAT_WAV;

    SNDFILE *file = sf_open(fileName.toUtf8(), SFM_WRITE, &fileInfo);

    if (!file) {
        return;
    }

    sf_write_short(file, &d->samples[0], d->samples.size());

    sf_close(file);
}

#include "capture.moc"
