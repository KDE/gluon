#ifndef INPUTDIFINITIONS_H
#define INPUTDIFINITIONS_H

#include <QtCore/QFlags>
#include <QtCore/QEvent>
#include <IOKit/hid/IOHIDUsageTables.h>

namespace GluonInput {
    enum DeviceFlag {
        UnknownDevice = kHIDUsage_Undefined,
        KeyBoardDevice = kHIDUsage_GD_Keyboard,
        MouseDevice = kHIDUsage_GD_Mouse,
        JoystickDevice = kHIDUsage_GD_Joystick,
        TouchpadDevice = kHIDUsage_Dig_TouchPad, //this belongs under the category of digitizers
        TabletDevice = kHIDUsage_Dig_Digitizer //change this because there exist alot of different kinds of tablets
    };
    Q_DECLARE_FLAGS(Devices, DeviceFlag)

    enum InputTypeFlag {
        Key = QEvent::Type(QEvent::User+1),
        RelativeAxis = QEvent::Type(QEvent::User+2),
        AbsoluAxis = QEvent::Type(QEvent::User+3)
    };

    Q_DECLARE_FLAGS(InputTypes, InputTypeFlag)
};

Q_DECLARE_OPERATORS_FOR_FLAGS(GluonInput::Devices);

Q_DECLARE_OPERATORS_FOR_FLAGS(GluonInput::InputTypes);

//@}
#endif // KCL_H
