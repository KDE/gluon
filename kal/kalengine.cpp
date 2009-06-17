/*
* This file is part of the KALEngine project.
* Copyright (C) 2007 Laurent Gomila <laurent.gom@gmail.com>
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

#include "kalengine.h"
#include "kalsource.h"
#include "kalphonon.h"

#include <alut.h>

#include <QtCore/QCoreApplication>
#include <QtCore/QSettings>

#include <KDebug>

class KALEnginePrivate
{
public:
    KALEnginePrivate()
            : context(0), device(0) {
        alutInitWithoutContext(0, 0);
    }

    virtual ~KALEnginePrivate() {}

    /**
    * @internal
    * Delete the device and context, used when changing the output device
    * and in the destructor
    */
    void cleanup();

    ALCcontext *context;
    ALCdevice *device;
    KALPhonon *phonon;
};

KALEngine::KALEngine(const QString &deviceName, QObject *parent)
        : QObject(parent)
{
    d = new KALEnginePrivate;
    d->phonon = new KALPhonon(this);

    setDeviceName(deviceName);
}

KALEngine::KALEngine(Phonon::Category category, QObject *parent)
        : QObject(parent)
{
    d = new KALEnginePrivate;
    d->phonon = new KALPhonon(this);

    setCategory(category);
}

KALEngine::KALEngine(QObject *parent)
        : QObject(parent)
{
    d = new KALEnginePrivate;
    d->phonon = new KALPhonon(this);

    setDevice(QString());
}

KALEngine::~KALEngine()
{
    // QObject deletes its children after deleting itself, but
    // OpenAL expects the sources to be deleted before the
    // context and device, so we do that manually
    QList<KALSource*> sources = findChildren<KALSource*>();
    qDeleteAll(sources);

    d->cleanup();

    delete d;
}

void KALEnginePrivate::cleanup()
{
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);
}

KALPhonon* KALEngine::phonon()
{
    return d->phonon;
}

bool KALEngine::setCategory(Phonon::Category category)
{
    phonon()->setCategory(category);
    if (!setDeviceName(phonon()->alDevice())) {
        return false;
    }

    connect(phonon(), SIGNAL(deviceChanged(QString)), this, SLOT(setDeviceName(QString)));

    return true;
}

bool KALEngine::setDevice(const QString &deviceName)
{
    phonon()->resetOutput();

    return setDeviceName(deviceName);
}

bool KALEngine::setDeviceName(const QString &deviceName)
{
    kDebug() << "Setting device to" << deviceName;

    if (d->device) {
        d->cleanup();
    }

    if (!deviceName.isEmpty()) {
        d->device = alcOpenDevice(deviceName.toUtf8());
    } else {
        d->device = alcOpenDevice(0);
    }

    if (!d->device) {
        return false;
    }

    d->context = alcCreateContext(d->device, 0);

    if (!d->context) {
        return false;
    }

    if (!alcMakeContextCurrent(d->context)) {
        return false;
    }

    kDebug() << "Device set";

    emit(deviceChanged(deviceName));

    return true;
}

QStringList KALEngine::deviceList()
{
    const ALCchar* devices = alcGetString(NULL, ALC_DEVICE_SPECIFIER);

    // alcGetString returns a list of devices separated by a null char (the list itself ends with a double null char)
    // So we can't pass it directly to QStringList
    QStringList deviceStringList;
    if (devices) {
        while (strlen(devices) > 0) {
            deviceStringList << QString(devices);
            devices += strlen(devices) + 1;
        }
    }
    return deviceStringList;
}
