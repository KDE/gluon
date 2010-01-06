#ifndef KCLTABLET_H
#define KCLTABLET_H

#include "kclinput.h"
#include <IOKit/hid/IOHIDLib.h>

class KCL_EXPORT KCLTablet : public KCLInput
{
public:
    KCLTablet(IOHIDDeviceRef device, QObject * parent = 0);
};

#endif // KCLTABLET_H
