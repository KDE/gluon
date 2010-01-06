#ifndef KCLCODE_H
#define KCLCODE_H

#include <QString>
#include <QIcon>
#include <QEvent>
#include "kcl.h"
#include "kcl_export.h"
/**
 * \defgroup KCL KCL
 */
//@{

class KCL_EXPORT KCLCode
{
public:
    static QString buttonName(int code);
    static QString eventName(int code);
    static QString relAxisName(int code);
    static QString absAxisName(int code);
    static QIcon iconDevice(KCL::DeviceFlag device);


};

//@}
#endif // KCLCODE_H
