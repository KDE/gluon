#include "kcljoystick.h"

KCLJoystick::KCLJoystick(IOHIDDeviceRef device, QObject * parent)
        : KCLInput(device, parent)
{
}

int KCLJoystick::axisX() const
{
    //return absAxisValue(ABS_X);
    return 0;
}

int KCLJoystick::axisY()const 
{
    //return absAxisValue(ABS_Y);
    return 0;
}

int KCLJoystick::axisZ() const
{
    //return absAxisValue(ABS_Z);
    return 0;
}