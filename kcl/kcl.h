#ifndef KCL_H
#define KCL_H
#include <QFlags>

class KCL
{
public:
    KCL();
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
        Button = 0x1,
        RelatifAxis = 0x2,
        AbsoluAxis = 0x3
    };
    Q_DECLARE_FLAGS(InputTypes, InputTypeFlag)

};

Q_DECLARE_OPERATORS_FOR_FLAGS(KCL::Devices);

Q_DECLARE_OPERATORS_FOR_FLAGS(KCL::InputTypes);
#endif // KCL_H
