#ifndef JOYSTICKPRIVATE_H
#define JOYSTICKPRIVATE_H

#include <QtCore/QSharedData>

namespace GluonInput
{
    class JoystickPrivate : public QSharedData
    {
        public:
            JoystickPrivate();
            JoystickPrivate(JoystickPrivate &other);
    };
}

#endif