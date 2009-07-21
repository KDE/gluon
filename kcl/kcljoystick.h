#ifndef KCLJOYSTICK_H
#define KCLJOYSTICK_H
#include "kclinput.h"

//===============================
// this is a default Joystick, with 2 axis

class KCLJoystick : public KCLInput
{
public:
    KCLJoystick(const QString& device, QObject * parent=0);

    int axisX(){return axisAbsolu(ABS_X);}
    int axisY(){return axisAbsolu(ABS_Y);}




};

#endif // KCLJOYSTICK_H
