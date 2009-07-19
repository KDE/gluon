#ifndef KCLJOYSTICK_H
#define KCLJOYSTICK_H
#include "kclinput.h"
class KCLJoystick : public KCLInput
{
public:
    KCLJoystick(const QString& device, QObject * parent=0);
};

#endif // KCLJOYSTICK_H
