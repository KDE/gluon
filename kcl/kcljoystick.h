#ifndef KCLJOYSTICK_H
#define KCLJOYSTICK_H
#include "kclinput.h"

//===============================
// this is a default Joystick, with 2 axis

class KCLJoystick : public KCLInput
{
public:
    KCLJoystick(const QString& device, QObject * parent=0);

    int axisX(){return absAxis(ABS_X);}
    int axisY(){return absAxis(ABS_Y);}
    int axisZ(){return absAxis(ABS_Z);}



};

#endif // KCLJOYSTICK_H
