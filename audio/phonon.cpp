/*
* This file is part of the Gluon project.
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

#include "kalphonon.h"
#include "kalengine.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QStringList>
#include <QtCore/QtGlobal>
#include <QtCore/QDebug>

class KALPhononPrivate
{
    public:
        KALPhononPrivate() :
                phononOutput(0),
                parentheses(QRegExp::escape(" (") + ".*" + QRegExp::escape(")")) {}

        virtual ~KALPhononPrivate() {}

        QString alDevice;
        Phonon::AudioOutput *phononOutput;
        Phonon::Category category;
        QRegExp parentheses;

};

KALPhonon::KALPhonon(QObject *parent)
        : QObject(parent),
        d(new KALPhononPrivate)
{
}

KALPhonon::~KALPhonon()
{
    delete d;
}

bool KALPhonon::setDevice(const Phonon::AudioOutputDevice &device)
{
    // get the part of the device name that is common to Phonon and OpenAL
    QString phononDevice = device.name().remove(d->parentheses);

    QStringList alDeviceList = KALEngine::deviceList().filter(phononDevice);

    if (alDeviceList.isEmpty())
    {
        qWarning() << "Could not find any OpenAL device that matches current Phonon device";
        return false;
    }

    d->alDevice = alDeviceList.first();

    emit(deviceChanged(d->alDevice));

    return true;
}

bool KALPhonon::setCategory(Phonon::Category category)
{
    resetOutput();

    // An instance of QCoreApplication must be running to create a Phonon::AudioOutput
    if (!QCoreApplication::instance())
    {
        qWarning() << "Could not get current Phonon device because QCoreApplication is not running";
        return false;
    }

    d->phononOutput = new Phonon::AudioOutput(category, this);
    if (!setDevice(d->phononOutput->outputDevice()))
    {
        return false;
    }

    d->category = category;
    connect(d->phononOutput, SIGNAL(outputDeviceChanged(Phonon::AudioOutputDevice)), this, SLOT(setDevice(Phonon::AudioOutputDevice)));

    return true;
}

void KALPhonon::resetOutput()
{
    if (!d->phononOutput)
    {
        return;
    }

    d->phononOutput->disconnect(this);
    d->phononOutput->deleteLater();
    d->phononOutput = 0;
}

Phonon::AudioOutput* KALPhonon::phononOutput() const
{
    return d->phononOutput;
}

QString KALPhonon::alDevice() const
{
    return d->alDevice;
}

Phonon::Category KALPhonon::category() const
{
    return d->category;
}

#include "kalphonon.moc"
