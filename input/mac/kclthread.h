#ifndef _KCLTHREAD_H_
#define _KCLTHREAD_H_

#include <QtCore/qthread.h>

#include <IOKit/IOKitLib.h>
#include <IOKit/hid/IOHIDKeys.h>
#include <IOKit/hid/IOHIDLib.h>

#include <QtCore/QObject>

#include "kcl_export.h"

class KCL_EXPORT KCLThread : public QThread
{
    Q_OBJECT
public:
    KCLThread(IOHIDDeviceRef pDevice, int deviceUsage , QObject* parent = 0);
    ~KCLThread();
    static void deviceReport(void * inContext, IOReturn inResult, void * inSender, IOHIDValueRef inIOHIDValueRef);
    void run();
    
    int deviceUsage() const;
private:
    int m_deviceUsage;
};

#endif