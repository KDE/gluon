#ifndef DETECTLINUXPRIVATE_H
#define DETECTLINUXPRIVATE_H

#include <QtCore/QList>
#include <QtCore/QSharedData>

namespace GluonInput
{
    class InputDevice;
    class Keyboard;
    class Mouse;
    class Joystick;
    class Tablet;

    class DetectLinuxPrivate : public QSharedData
    {
        public:
            DetectLinuxPrivate();
            DetectLinuxPrivate(DetectLinuxPrivate &other);

            QList<InputDevice *> inputList;
            QList<Keyboard *> keyboardList;
            QList<Mouse *> mouseList;
            QList<Joystick *> joystickList;
            QList<Tablet *> tabletList;
            QList<InputDevice *> unknownList;
    };
}
#endif
