#ifndef KCLKEYBOARD_H
#define KCLKEYBOARD_H

#include "kclinput.h"
#include <IOKit/hid/IOHIDLib.h>

class KCL_EXPORT KCLKeyBoard : public KCLInput
{
public:
    KCLKeyBoard(IOHIDDeviceRef device, QObject * parent = 0);
};

#endif // KCLKEYBOARD_H
