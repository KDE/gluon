/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2010 Kim Jung Nissen <jungnissen@gmail.com>
 * Copyright (C) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

namespace GluonInput
{
    enum DeviceFlag
    {
        UnknownDevice = 0x0,
        KeyboardDevice = 0x1,
        MouseDevice = 0x2,
        JoystickDevice = 0x4,
        TabletDevice = 0x8,
        TouchpadDevice = 0x16
    };
    Q_DECLARE_FLAGS(Devices, DeviceFlag)

    enum InputTypeFlag
    {
        Button = QEvent::Type(QEvent::User + 1),
        RelativeAxis = QEvent::Type(QEvent::User + 2),
        AbsoluteAxis = QEvent::Type(QEvent::User + 3)
    };
};

Q_DECLARE_OPERATORS_FOR_FLAGS(GluonInput::Devices);

#endif
