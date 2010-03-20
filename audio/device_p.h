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

#ifndef KALDEVICE_H
#define KALDEVICE_H

#include <QtCore/QStringList>

#ifdef Q_WS_X11
#include <AL/alc.h>
#endif
#ifdef Q_WS_MAC
#include <OpenAL/alc.h>
#endif

namespace GluonAudio
{

    class Device
    {
        public:
            Device(ALCdevice *device = 0);
            ~Device();

            static bool isExtensionPresent(const QString &extension);

            static QStringList contextOption(int option);

        protected:
            ALCdevice *m_device;
    };
}

#endif // KALDEVICE_H
