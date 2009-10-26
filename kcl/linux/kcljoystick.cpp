#include "kcljoystick.h"

KCLJoystick::KCLJoystick(const QString& device, QObject * parent)
        : KCLInput(device, parent)
{
}

#include "kcljoystick.moc"
