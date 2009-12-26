#include "kcldetectwin.h"

#include <IOKit/IOKitLib.h>
#include <IOKit/hid/IOHIDKeys.h>
#include <IOKit/hid/IOHIDLib.h>

KCLDetectWin::KCLDetectWin(QObject * parent)
: QObject(parent)
{
}

KCLDetectWin::~KCLDetectWin()
{
    //    kDebug()<<"clear device...";
    //    foreach ( KCLInput * input, m_inputList)
    //    {
    //        delete input;
    //    }
}

void KCLDetectWin::searchDevice()
{
    KCLDetectWin *detect = this;
    
    ///move it out and maybe in detection
    /*IOHIDManagerRef miw = IOHIDManagerCreate( kCFAllocatorDefault, kIOHIDOptionsTypeNone);
     
     if ( CFGetTypeID( miw ) == IOHIDManagerGetTypeID( ) ) 
     {
     IOHIDManagerSetDeviceMatching(miw, NULL);
     
     IOReturn success = IOHIDManagerOpen(miw, kIOHIDOptionsTypeNone);
     
     if(success == kIOReturnSuccess)
     {
     CFSetRef devicesSet = IOHIDManagerCopyDevices(miw);
     
     if(CFSetGetCount(devicesSet) > 0)
     {               
     CFSetApplyFunction(devicesSet, callBack, NULL);
     }
     // CFRelease(devicesSet);
     }        
     }*/
    
    detect->setAllEnable();
}

void KCLDetectWin::clear()
{
    m_inputList.clear();
    m_keyboardList.clear();
    m_mouseList.clear();
    m_joystickList.clear();
    m_tabletList.clear();
    m_unknownList.clear();
}
