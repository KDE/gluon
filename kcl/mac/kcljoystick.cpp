#include "kcljoystick.h"

KCLJoystick::KCLJoystick(IOHIDDeviceRef device, QObject * parent)
        : KCLInput(device, parent)
{
}

int KCLJoystick::axisX() const
{
    return absAxisValue(m_xAbsUsage);
}

int KCLJoystick::axisY()const 
{
    return absAxisValue(m_yAbsUsage);
}

int KCLJoystick::axisZ() const
{
    return absAxisValue(m_zAbsUsage);
}

#include "kcljoystick.moc"
