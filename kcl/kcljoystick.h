#ifndef KCLJOYSTICK_H
#define KCLJOYSTICK_H

#include "kclinput.h"

/**
 * \defgroup KCL KCL
 */
//@{

// this is a default joystick, with 2 axis

class KCL_EXPORT KCLJoystick : public KCLInput
{
    Q_OBJECT
public:
    KCLJoystick(const QString& device, QObject * parent = 0);

    int axisX() const{
        return absAxisValue(ABS_X);
    }

    int axisY()const {
        return absAxisValue(ABS_Y);
    }

    int axisZ() const{
        return absAxisValue(ABS_Z);
    }
};

//@}
#endif // KCLJOYSTICK_H
