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
#ifndef GLUONDEVICES_H
#define GLUONDEVICES_H

#include <QtCore/QFlags>
#include <QtCore/QEvent>

#include <IOKit/hid/IOHIDUsageTables.h>

namespace GluonInput
{
    enum DeviceFlag
    {
        UnknownDevice = kHIDUsage_Undefined,
        KeyboardDevice = kHIDUsage_GD_Keyboard,
        MouseDevice = kHIDUsage_GD_Mouse,
        JoystickDevice = kHIDUsage_GD_Joystick,
        //TouchpadDevice = kHIDUsage_Dig_TouchPad, //this belongs under the category of digitizers
        TouchDevice = kHIDUsage_Dig_Digitizer //change this because there exist a lot of different kinds of touches
    };
    Q_DECLARE_FLAGS( Devices, DeviceFlag )

    Q_DECLARE_OPERATORS_FOR_FLAGS( Devices );
}

#endif
