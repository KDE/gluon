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
#ifndef INPUTTHREAD_H
#define INPUTTHREAD_H

#include "gluon_input_export.h"
#include "gluonbuttons.h"
#include "absval.h"

#include <QtCore/QThread>
#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QSharedData>

#include <IOKit/IOKitLib.h>
#include <IOKit/hid/IOHIDKeys.h>
#include <IOKit/hid/IOHIDLib.h>

namespace GluonInput
{

    class InputThreadPrivate;

    class GLUON_INPUT_EXPORT InputThread : public QThread
    {
        Q_OBJECT
        public:
            explicit InputThread(IOHIDDeviceRef pDevice, QObject *parent = 0);
            ~InputThread();

            static void deviceReport(void *inContext, IOReturn inResult, void *inSender, IOHIDValueRef inIOHIDValueRef);

            int joystickXAxis();
            int joystickYAxis();
            int joystickZAxis();

            void run();
            void stop();

            int vendora() const;
            int product() const;
            int version() const;
            int bustype() const;

            QList<int> buttonCapabilities() const;
            QList<int> absAxisCapabilities() const;
            QList<int> relAxisCapabilities() const;
            AbsVal axisInfo(int axisCode) const;

            const QString deviceName() const;
            GluonInput::DeviceFlag deviceType() const;

            bool isEnabled() const;

            bool error();
            QString msgError();

            QObject *parent();

signals:
            void relAxisMoved(int axis, int distance);
            void absAxisMoved(int axis, int distance);
            void buttonStateChanged(int button, int value);

        private:
            void readInformation();

            QSharedDataPointer<InputThreadPrivate> d;
    };
}
#endif
