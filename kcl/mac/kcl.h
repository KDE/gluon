#ifndef KCL_H
#define KCL_H
#include <QFlags>
#include <QEvent>

/**
 * \defgroup KCL KCL
 */
//@{

namespace KCL {
    enum DeviceFlag {
        Unknown = 0x0,
        KeyBoard = 0x1,
        Mouse = 0x2,
        Joystick = 0x4,
        Tablet = 0x8,
        Touchpad = 0x16
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
