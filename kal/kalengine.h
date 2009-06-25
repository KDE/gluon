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

#ifndef KALENGINE_H
#define KALENGINE_H

#include <alc.h>
#include <alut.h>
#include <QtCore/QStringList>
#include <Phonon/Global>

#include "kalengine_export.h"

class KALEnginePrivate;
class KALPhonon;

/**
* @class KALEngine kalengine.h <KALEngine>
* KALEngine is an audio engine which uses OpenAL for sound processing
*/
class KALENGINE_EXPORT KALEngine : public QObject
{
    Q_OBJECT

public:
    /**
    * Default constructor
    */
    explicit KALEngine(const QString &deviceName, QObject *parent = 0);
    explicit KALEngine(Phonon::Category category, QObject *parent = 0);
    KALEngine(QObject *parent = 0);

    /**
    * Destructor
    */
    ~KALEngine();

    /**
    * @return the list of output devices available
    */
    static QStringList deviceList();

    /**
    * Returns a pointer to the KALPhonon object used
    */
    KALPhonon *phonon();
    ALCdevice * device();
    ALCcontext *context();
public Q_SLOTS:
    /**
    * Change the output device to the one currently used by Phonon for
    * @p category.
    * Once this function is called and until setDevice or setCategory
    * is called, KALEngine will automatically change the device to match
    * the one used by Phonon when it changes
    * @return true if the new device was successfuly set, false otherwise
    * @see setDevice
    */
    bool setCategory(Phonon::Category category);

    /**
    * Change the output device to the specified OpenAL device name
    * @param deviceName the OpenAL device name
    * @return true if the new device was successfuly set, false otherwise
    * @see devicesList, setCategory
    */
    bool setDevice(const QString &deviceName = QString());


Q_SIGNALS:
    QString deviceChanged(const QString &deviceName);

private:
    KALEnginePrivate *d;

private Q_SLOTS:
    bool setDeviceName(const QString &deviceName = QString());
};

#endif // KALENGINE_H
