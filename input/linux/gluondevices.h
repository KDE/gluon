/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
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
#include <linux/input.h>

namespace GluonInput
{
    enum DeviceFlag {
        UnknownDevice = 0,
        KeyboardDevice = 1,
        MouseDevice = 1 << 1,
        JoystickDevice = 1 << 2,
        TouchDevice = 1 << 3,
        TouchpadDevice = 1 << 4
    };
    Q_DECLARE_FLAGS(Devices, DeviceFlag)

    enum InputTypeFlag {
        Button = QEvent::Type(QEvent::User + EV_KEY),
        RelativeAxis = QEvent::Type(QEvent::User + EV_REL),
        AbsoluteAxis = QEvent::Type(QEvent::User + EV_ABS)
    };
};

Q_DECLARE_OPERATORS_FOR_FLAGS(GluonInput::Devices);

#endif
