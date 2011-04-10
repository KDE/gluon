/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2009 Sacha Schutz <istdasklar@free.fr>
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
#include "capture.h"
#include "capturedevice_p.h"

#include <QtCore/QtGlobal>
#include <QtCore/QDebug>
#include <QtCore/QTime>
#include <QtCore/QFile>

#ifdef Q_WS_X11
#include <AL/al.h>
#elif defined(Q_WS_MAC)
#include <OpenAL/al.h>
#elif defined(Q_WS_WIN)
#include <AL/al.h>
#endif

#include <alc.h>
#include <sndfile.h>

using namespace GluonAudio;

class Capture::CapturePrivate
{
    public:
        CaptureDevice* captureDevice;
        QVector<ALshort> samples;
        ALuint buffer;
};

Capture::Capture( QString deviceName, QObject* parent )
    : QObject( parent )
    , d( new CapturePrivate )
{
    if( isAvailable() )
    {
        d->captureDevice = new CaptureDevice( deviceName.toUtf8(), 44100, AL_FORMAT_MONO16, 44100 );
    }
    else
    {
        qCritical() << "No capture device available";
        return;
    }

    if( !d->captureDevice )
    {
        qCritical() << "Could not set the capture device";
        return;
    }
}

Capture::~Capture()
{
    delete d->captureDevice;
    delete d;
}

bool Capture::isAvailable() const
{
    return Device::isExtensionPresent( "ALC_EXT_CAPTURE" );
}

QStringList Capture::deviceList()
{
    return Device::contextOption( ALC_CAPTURE_DEVICE_SPECIFIER );
}

void Capture::record( int duration )
{
    QTime recordTime;
    recordTime.start();

    while( recordTime.elapsed() < duration )
    {
        ALCint samples = d->captureDevice->samples();
        if( samples > 0 )
        {
            //d->samples.append(samples);
            d->samples.append( d->captureDevice->startCapture( samples ) );
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


void Capture::save( const QString& fileName )
{
    SF_INFO fileInfo;
    fileInfo.channels = 1;
    fileInfo.samplerate = 44100;
    fileInfo.format = SF_FORMAT_PCM_16 | SF_FORMAT_WAV;

    SNDFILE* file = sf_open( fileName.toUtf8(), SFM_WRITE, &fileInfo );

    if( !file )
    {
        return;
    }

    sf_write_short( file, &d->samples[0], d->samples.size() );

    sf_close( file );
}

#include "capture.moc"

