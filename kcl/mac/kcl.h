#ifndef KCL_H
#define KCL_H
#include <QtCore/QFlags>
#include <QtCore/QEvent>
#include <IOKit/hid/IOHIDUsageTables.h>

namespace KCL {
    enum DeviceFlag {
        Unknown = kHIDUsage_Undefined,
        KeyBoard = kHIDUsage_GD_Keyboard,
        Mouse = kHIDUsage_GD_Mouse,
        Joystick = kHIDUsage_GD_Joystick,
        Touchpad = kHIDUsage_Dig_TouchPad, //this belongs under the category of digitizers
        Tablet = kHIDUsage_Dig_Digitizer //change this because there exist alot of different kinds of tablets
    };
    Q_DECLARE_FLAGS(Devices, DeviceFlag)

    enum InputTypeFlag {
        Key = QEvent::Type(QEvent::User),
        RelativeAxis = QEvent::Type(QEvent::User+1),
        AbsoluAxis = QEvent::Type(QEvent::User+2)
    };

    Q_DECLARE_FLAGS(InputTypes, InputTypeFlag)
};

Q_DECLARE_OPERATORS_FOR_FLAGS(KCL::Devices);

Q_DECLARE_OPERATORS_FOR_FLAGS(KCL::InputTypes);

//@}
#endif // KCL_H
