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

#ifndef KALPHONON_H
#define KALPHONON_H

#include "kalengine_export.h"

#include <Phonon/AudioOutput>

#include <QtCore/QRegExp>

class KALPhononPrivate;

/**
* @class KALPhonon kalphonon.h <KALPhonon>
* KALPhonon is a wrapper class around Phonon to make it possible to use
* Phonon output device in KALEngine
*/
class KALENGINE_EXPORT KALPhonon : public QObject
{
    Q_OBJECT

public:
    KALPhonon(QObject *parent = 0);

    void resetOutput();

    QString alDevice() const;
    Phonon::AudioOutput* phononOutput() const;
    Phonon::Category category() const;

public Q_SLOTS:
    bool setCategory(Phonon::Category category);

Q_SIGNALS:
    void deviceChanged(const QString &deviceName);

private:
    KALPhononPrivate *d;

private Q_SLOTS:
    bool setDevice(const Phonon::AudioOutputDevice &device);

};

#endif // KALPHONON_H
