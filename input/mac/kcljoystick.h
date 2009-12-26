#ifndef KCLJOYSTICK_H
#define KCLJOYSTICK_H

#include "kclinput.h"
#include <IOKit/hid/IOHIDLib.h>

class KCL_EXPORT KCLJoystick : public KCLInput
{
    Q_OBJECT
public:
    KCLJoystick(IOHIDDeviceRef device, QObject * parent = 0);

    int axisX() const;
    int axisY()const;
    int axisZ() const;
};

//@}
#endif // KCLJOYSTICK_H
