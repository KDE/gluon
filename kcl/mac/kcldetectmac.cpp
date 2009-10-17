#include "kcldetectmac.h"

#include <IOKit/IOKitLib.h>
#include <IOKit/hid/IOHIDKeys.h>
#include <IOKit/hid/IOHIDLib.h>

KCLDetectMac::KCLDetectMac(QObject * parent)
: KCLDetectAbstract(parent)
{
}

KCLDetectMac::~KCLDetectMac()
{
    //    kDebug()<<"clear device...";
    //    foreach ( KCLInput * input, m_inputList)
    //    {
    //        delete input;
    //    }
}

void KCLDetectMac::searchDevice()
{
    //KCLDetectMac *detect = this;
    
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
    
    //detect->setAllEnable();
}

QList<KCLInput *> KCLDetectMac::getInputList() 
{
    return m_inputList;
}

QList<KCLKeyBoard *> KCLDetectMac::getKeyboardList() 
{
    return m_keyboardList;
}

QList<KCLMouse *> KCLDetectMac::getMouseList() 
{
    return m_mouseList;
}

QList<KCLJoystick *> KCLDetectMac::getJoystickList() 
{
    return m_joystickList;
}

QList<KCLTablet *> KCLDetectMac::getTabletList() 
{
    return m_tabletList;
}

QList<KCLInput *> KCLDetectMac::getUnknownDeviceList() 
{
    return m_unknownList;
}


void KCLDetectMac::addInput(KCLInput *i) 
{
    m_inputList.append(i);
}

void KCLDetectMac::addKeyboard(KCLInput *i)
{
    KCLKeyBoard * keybd = new KCLKeyBoard(i->device());
    keybd->setEnable();
    m_keyboardList.append(keybd);
}

void KCLDetectMac::addMouse(KCLInput *i) 
{
    KCLMouse * mouse = new KCLMouse(i->device());
    mouse->setEnable();
    m_mouseList.append(mouse);
}

void KCLDetectMac::addJoystick(KCLInput *i)
{
    KCLJoystick * joy = new KCLJoystick(i->device());
    joy->setEnable();
    m_joystickList.append(joy);
    
}

void KCLDetectMac::addTablet(KCLInput *i) 
{
    KCLTablet * tablet = new KCLTablet(i->device());
    tablet->setEnable();
    m_tabletList.append(tablet);
}

void KCLDetectMac::addUnknown(KCLInput *i) 
{
    m_unknownList.append(i);
}

void KCLDetectMac::clear()
{
    m_inputList.clear();
    m_keyboardList.clear();
    m_mouseList.clear();
    m_joystickList.clear();
    m_tabletList.clear();
    m_unknownList.clear();
}
