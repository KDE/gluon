/*
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

#ifndef KALUTILS_H
#define KALUTILS_H

#include <QtCore/QStringList>

#ifdef Q_WS_X11
#include <AL/alc.h>
#endif
#ifdef Q_WS_MAC
#include <OpenAL/alc.h>
#endif

class KALDevice
{
public:
    KALDevice(ALCdevice *device = 0);
    ~KALDevice();

    static bool isExtensionPresent(const QString &extension);

    static QStringList contextOption(int option);

protected:
    ALCdevice *m_device;
};

#endif // KALUTILS_H
