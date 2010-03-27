#include "joystickprivate.h"

using namespace GluonInput;

JoystickPrivate::JoystickPrivate()
{
}

JoystickPrivate::JoystickPrivate(JoystickPrivate &other)
        : QSharedData(other)
{
}
