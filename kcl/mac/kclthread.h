#ifndef _KCLTHREAD_H_
#define _KCLTHREAD_H_

#include <QtCore/qthread.h>

#include <IOKit/IOKitLib.h>
#include <IOKit/hid/IOHIDKeys.h>
#include <IOKit/hid/IOHIDLib.h>
#include <QObject>

class KCLThread : public QThread
{
    Q_OBJECT
public:
    KCLThread(IOHIDDeviceRef pDevice, QObject* parent = 0);
    ~KCLThread();
    
    static void deviceReport(void * inContext, IOReturn inResult, void * inSender, IOHIDReportType inType, uint32_t inReportID, uint8_t * inReport, CFIndex inReportLength );    
    void run();
};

#endif