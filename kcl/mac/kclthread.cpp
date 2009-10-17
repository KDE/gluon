#include "kclthread.h"

#include <iostream>
#include <QtCore/qeventloop.h>

//static void reportCallBack(void * inContext, IOReturn inResult, void * inSender, IOHIDReportType inType, uint32_t inReportID, uint8_t * inReport, CFIndex inReportLength );

KCLThread::KCLThread(IOHIDDeviceRef pDevice , QObject * parent)
: QThread(parent)
{   
    IOHIDDeviceOpen(pDevice,kIOHIDOptionsTypeNone);
    IOHIDDeviceScheduleWithRunLoop( pDevice, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode );
    CFIndex reportSize = (CFIndex) IOHIDDeviceGetProperty(pDevice,CFSTR( kIOHIDMaxInputReportSizeKey));
    uint8_t *report = (uint8_t*)malloc( reportSize );
    IOHIDDeviceRegisterInputReportCallback( pDevice, report, reportSize, deviceReport, NULL );
}

KCLThread::~KCLThread()
{
}

void KCLThread::run()
{
    this->exec();
}


//maybe use value callback
void KCLThread::deviceReport(void * inContext, IOReturn inResult, void * inSender, IOHIDReportType inType, uint32_t inReportID, uint8_t * inReport, CFIndex inReportLength )
{
    //refactor sedn events as kclevents to qcoreapp
    IOHIDDeviceRef deviceRef = (IOHIDDeviceRef) inSender;
    if(inResult == kIOReturnSuccess && CFGetTypeID(deviceRef) == IOHIDDeviceGetTypeID())
    {
        CFArrayRef elements = IOHIDDeviceCopyMatchingElements(deviceRef, NULL, kIOHIDOptionsTypeNone);
        
        if(elements)
        {
            
            for(int i = 0; i < CFArrayGetCount(elements); i++)
            {
                IOHIDElementRef elementRef = (IOHIDElementRef)CFArrayGetValueAtIndex(elements,(CFIndex)i);
                if(CFGetTypeID(elementRef) == IOHIDElementGetTypeID())
                {
                    uint32_t usagePage = IOHIDElementGetUsagePage( elementRef );
                    uint32_t usage = IOHIDElementGetUsage( elementRef );
                    
                    IOHIDValueRef bla = NULL;
                    IOHIDDeviceGetValue(deviceRef, elementRef, &bla);                    
                    
                    if ( bla != NULL ) 
                    {
                        CFIndex mdmd = IOHIDValueGetIntegerValue( bla );
                        
                        if(mdmd > 0 && usage > -1)
                        {
                            printf("usagepage: %d usage: %d thread: %d\n", usagePage, usage, (int)CFRunLoopGetCurrent());
                        }
                    }
                }
            }
        }
    }
}