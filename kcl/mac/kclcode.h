#ifndef KCLCODE_H
#define KCLCODE_H

#define KCL_CODE_BUTTON_SIZE 232
#define KCL_CODE_RELABS_SIZE 198

#include <QtCore/QString>
#include <QtCore/QEvent>
#include "kcl.h"
#include "kcl_export.h"

class KCL_EXPORT KCLCode
{
public:
    static QString buttonName(int code);
    static QString eventName(int code);
    static QString relAxisName(int code);
    static QString absAxisName(int code);

private:
    
};

#endif // KCLCODE_H
