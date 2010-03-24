#ifndef GLUONDEVICES_H
#define GLUONDEVICES_H

#include <QtCore/QFlags>
#include <QtCore/QEvent>
#include <linux/input.h>

namespace GluonInput
{
    enum DeviceFlag
    {
        UnknownDevice = 0x0,
        KeyBoardDevice = 0x1,
        MouseDevice = 0x2,
        JoystickDevice = 0x4,
        TabletDevice = 0x8,
        TouchpadDevice = 0x16
    };
    Q_DECLARE_FLAGS(Devices, DeviceFlag)
};

Q_DECLARE_OPERATORS_FOR_FLAGS(GluonInput::Devices);

#endif