#ifndef KCLJOYSTICK_H
#define KCLJOYSTICK_H

#include "kclinput.h"

/**
 * \defgroup KCL KCL
 */
//@{

// this is a default joystick, with 2 axis

class KCLJoystick : public KCLInput
{
public:
    KCLJoystick(const QString& device, QObject * parent = 0);

    int axisX() {
        return absAxisValue(ABS_X);
    }

    int axisY() {
        return absAxisValue(ABS_Y);
    }

    int axisZ() {
        return absAxisValue(ABS_Z);
    }
};

//@}
#endif // KCLJOYSTICK_H
