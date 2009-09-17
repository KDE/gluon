#ifndef KCL_H
#define KCL_H
#include <QFlags>
#include <QEvent>
#include <linux/input.h>
namespace KCL {
    enum DeviceFlag {
        Unknown = 0x0,
        KeyBoard = 0x1,
        Mouse = 0x2,
        Joystick = 0x3,
        Tablet = 0x4,
        Touchpad = 0x5
    };
    Q_DECLARE_FLAGS(Devices, DeviceFlag)

    enum InputTypeFlag {
        NoType = 0x0,
        Key = QEvent::User+EV_KEY,
        RelatifAxis = QEvent::User+EV_REL,
        AbsoluAxis = QEvent::User+EV_ABS
    };




    Q_DECLARE_FLAGS(InputTypes, InputTypeFlag)
};

Q_DECLARE_OPERATORS_FOR_FLAGS(KCL::Devices);

Q_DECLARE_OPERATORS_FOR_FLAGS(KCL::InputTypes);
#endif // KCL_H
