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

#ifndef DETECT_H
#define DETECT_H

#include "gluon_input_export.h"

#include <QtCore/QObject>
#include <QtCore/QSharedData>

namespace GluonInput
{
    class Joystick;
    class Mouse;
    class Touch;
    class Keyboard;
    class InputDevice;

    class GLUON_INPUT_EXPORT Detect : public QObject
    {
        Q_OBJECT

        public:
            Detect(QObject *parent = 0);

            virtual void detectDevices() = 0;
            virtual void setAllEnabled(bool enable) = 0;

            virtual QList<InputDevice *> inputList() = 0;
            virtual QList<Keyboard *> keyboardList() = 0;
            virtual QList<Mouse *> mouseList() = 0;
            virtual QList<Joystick *> joystickList() = 0;
            virtual QList<Touch *> touchList() = 0;
            virtual QList<InputDevice *> unknownDeviceList() = 0;

            virtual void addInput(InputDevice *i) = 0;
            virtual void addKeyboard(Keyboard *keyboard) = 0;
            virtual void addMouse(Mouse *mouse) = 0;
            virtual void addJoystick(Joystick *joystick) = 0;
            virtual void addTouch(Touch *touch) = 0;
            virtual void addUnknown(InputDevice *i) = 0;
            virtual void clear() = 0;
    };
}
#endif
