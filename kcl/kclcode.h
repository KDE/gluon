#ifndef KCLCODE_H
#define KCLCODE_H

#include <QString>
#include <KIcon>
#include "kcl.h"
class KCLCode
{
public:
    static QString buttonName(int code);
    static QString eventName(int code);
    static QString relAxisName(int code);
    static QString absAxisName(int code);
    static KIcon iconDevice(KCL::DeviceFlag device);
};

#endif // KCLCODE_H
