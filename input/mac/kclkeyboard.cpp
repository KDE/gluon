#include "kclkeyboard.h"

KCLKeyBoard::KCLKeyBoard(IOHIDDeviceRef device, QObject * parent)
        : KCLInput(device, parent)
{
}
