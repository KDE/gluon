/*
* This file is part of the Gluon project.
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

#ifndef GLUON_AUDIO_CAPTURE_H
#define GLUON_AUDIO_CAPTURE_H

#include <QtCore/QObject>
#include <QtCore/QStringList>

#include "gluon_audio_export.h"

namespace GluonAudio
{
    class GLUON_AUDIO_EXPORT Capture : public QObject
    {
        Q_OBJECT

    public:
        explicit Capture(QString deviceName = QString(), QObject *parent = 0);
        ~Capture();

        bool isAvailable() const;

        static QStringList deviceList();

        void record(int duration = 1000);
        void save(const QString &fileName);

    private:
        Q_DISABLE_COPY(Capture)

        class CapturePrivate;
        CapturePrivate * const d;
    };
}

#endif // GLUON_AUDIO_CAPTURE_H
