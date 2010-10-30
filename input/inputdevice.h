/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Kim Jung Nissen <jungnissen@gmail.com>
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
#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include "inputthread.h"
#include "gluondevices.h"

#include <QtCore/QMap>
#include <QtCore/QPair>
#include <QtCore/QPoint>
#include <QtCore/QThread>
#include <QtCore/QEvent>
#include <QtCore/QSharedData>
#include <QtCore/QObject>

namespace GluonInput
{
    class InputDevicePrivate;

    class GLUON_INPUT_EXPORT InputDevice : public QObject
    {
        Q_OBJECT
        Q_ENUMS(GluonInput::KeyboardButton)

        public:
            InputDevice();
            explicit InputDevice(InputThread *inputThread, QObject *parent = 0);
            ~InputDevice();

            int vendor() const;
            int product() const;
            int version() const;
            int bustype() const;

            const QString deviceName() const;
            GluonInput::DeviceFlag deviceType()const;

            QList<int> buttonCapabilities() const;
            QList<int> absAxisCapabilities() const;
            QList<int> relAxisCapabilities() const;
            AbsVal axisInfo(int axisCode) const;
            bool buttonPressed(int code) const;
            QString buttonName(int code) const;
            QString axisName(int code) const;

            bool error() const;
            QString msgError() const;

            void setInputThread(InputThread *inputThread);
            InputThread *inputThread() const;

            bool isEnabled() const;
            void setEnabled(bool enable);

        private slots:
            void buttonStateChanged(int code, int value);

        private:

            QSharedDataPointer<InputDevicePrivate> d;
    };
}
#endif // KCLINPUT_H
