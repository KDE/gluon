#ifndef DETECTMACPRIVATE_H
#define DETECTMACPRIVATE_H

#include <QtCore/QList>
#include <QtCore/QSharedData>
#include <IOKit/hid/IOHIDLib.h>

namespace GluonInput
{
    class InputDevice;
    class KeyBoard;
    class Mouse;
    class Joystick;
    class Tablet;

    class DetectMacPrivate : public QSharedData
    {
        public:
            DetectMacPrivate();
            DetectMacPrivate(DetectMacPrivate &other);

            QList<InputDevice *> m_inputList;
            QList<KeyBoard *> m_keyboardList;
            QList<Mouse *> m_mouseList;
            QList<Joystick *> m_joystickList;
            QList<Tablet *> m_tabletList;
            QList<InputDevice *> m_unknownList;
            IOHIDManagerRef deviceManager;
            CFSetRef devices;
    };
}
#endif