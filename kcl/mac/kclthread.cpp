#include "kclthread.h"

#include <QtCore/qeventloop.h>
#include "kcl.h"
#include <QtCore/QCoreApplication>
#include "kclinputevent.h"
#include <IOKit/hid/IOHIDUsageTables.h>
#include "kclcode.h"

KCLThread::KCLThread(IOHIDDeviceRef pDevice, int deviceUsage ,QObject * parent)
: QThread(parent)
{   
    m_deviceUsage = deviceUsage;
    IOHIDDeviceOpen(pDevice,kIOHIDOptionsTypeNone);
    IOHIDDeviceScheduleWithRunLoop( pDevice, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode );
    IOHIDDeviceRegisterInputValueCallback(pDevice, deviceReport, this);
}

KCLThread::~KCLThread()
{
}

int KCLThread::deviceUsage() const
{
    return m_deviceUsage;
}

void KCLThread::run()
{
    this->exec();
}

void KCLThread::deviceReport(void * inContext, IOReturn inResult, void * inSender, IOHIDValueRef inIOHIDValueRef) 
{
    IOHIDDeviceRef deviceRef = (IOHIDDeviceRef) inSender;
    KCLThread * currentThread = (KCLThread* ) inContext;
    if(inResult == kIOReturnSuccess && CFGetTypeID(deviceRef) == IOHIDDeviceGetTypeID())
    {
        IOHIDElementRef elementRef = IOHIDValueGetElement(inIOHIDValueRef);
        
        int usagePage = IOHIDElementGetUsagePage( elementRef );
        int usage = IOHIDElementGetUsage( elementRef );
        int value = IOHIDValueGetIntegerValue(inIOHIDValueRef);
            
        if(usagePage == kHIDPage_GenericDesktop || usagePage == kHIDPage_KeyboardOrKeypad || usagePage == kHIDPage_Button)
        {
            if(usagePage == kHIDPage_GenericDesktop && usage == 60)
                return;
            else if(usagePage == kHIDPage_KeyboardOrKeypad && (usage <= 3 || usage > 231))
                return;
            
            QEvent::Type eventType;
            
            switch (currentThread->deviceUsage())
            {
                case KCL::KeyBoard:
                    eventType = QEvent::Type(KCL::Key);
                    break;
                case KCL::Mouse:
                    if(usagePage == kHIDPage_GenericDesktop)
                    {
                        eventType = QEvent::Type(KCL::RelativeAxis);
                    }
                    else if(usagePage == kHIDPage_Button)
                    {
                        value += KCL_CODE_BUTTON_SIZE;
                        eventType = QEvent::Type(KCL::Key);
                    }
                case KCL::Joystick:
                    break;
                case KCL::Tablet:
                    break;
                case KCL::Touchpad:
                    break;
                default:
                    break;
            }
            
            CFNumberRef numberRef =  (CFNumberRef)IOHIDDeviceGetProperty(deviceRef,CFSTR(kIOHIDLocationIDKey));
            int id = -1;
            CFNumberGetValue(numberRef, kCFNumberSInt32Type, &id);
            KCLInputEvent * event = new KCLInputEvent(usage, value, usagePage, usage, id, eventType);
            QCoreApplication::sendEvent(currentThread->parent(), event);
         }
    }
}

#include "kclthread.moc"