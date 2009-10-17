#include "kcltablet.h"

KCLTablet::KCLTablet(IOHIDDeviceRef device, QObject *parent)
        : KCLInput(device, parent)
{
}

