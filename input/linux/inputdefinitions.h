#ifndef INPUTDIFINITIONS_H
#define INPUTDIFINITIONS_H

#include <QtCore/QFlags>
#include <QtCore/QEvent>
#include <linux/input.h>

/**
 * \defgroup KCL KCL
 */
//@{

namespace GluonInput 
{
    enum DeviceFlag {
        UnknownDevice = 0x0,
        KeyBoardDevice = 0x1,
        MouseDevice = 0x2,
        JoystickDevice = 0x4,
        TabletDevice = 0x8,
        TouchpadDevice = 0x16
    };
    Q_DECLARE_FLAGS(Devices, DeviceFlag)

    enum InputTypeFlag {
        Key = QEvent::Type(QEvent::User+EV_KEY),
        RelativeAxis = QEvent::Type(QEvent::User+EV_REL),
        AbsoluAxis = QEvent::Type(QEvent::User+EV_ABS)
    };




    Q_DECLARE_FLAGS(InputTypes, InputTypeFlag)
};

Q_DECLARE_OPERATORS_FOR_FLAGS(GluonInput::Devices);

Q_DECLARE_OPERATORS_FOR_FLAGS(GluonInput::InputTypes);

//@}
#endif // KCL_H
