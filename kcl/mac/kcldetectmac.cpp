#include "kcldetectmac.h"

#include <QtCore/QDebug>
#include <IOKit/IOKitLib.h>
#include <IOKit/hid/IOHIDUsageTables.h>
#include "kcl.h"

KCLDetectMac::KCLDetectMac(QObject * parent)
: KCLDetectAbstract(parent)
{
    deviceManager = NULL;
    devices = NULL;
}

KCLDetectMac::~KCLDetectMac()
{
    CFRelease(deviceManager);
    CFRelease(devices);
}

void KCLDetectMac::searchDevice()
{
    qDebug() << "Checking if deviceManager exists";
    if(deviceManager == NULL)
    {
        qDebug() << "Creating device manager";
        deviceManager = IOHIDManagerCreate( kCFAllocatorDefault, kIOHIDOptionsTypeNone);
    }
    
    CFMutableDictionaryRef dict;
    CFMutableArrayRef matchingArray = CFArrayCreateMutable( kCFAllocatorDefault, 0, &kCFTypeArrayCallBacks );
    //keyboard
    dict = createMatchingDictionary(kHIDPage_GenericDesktop, kHIDUsage_GD_Keyboard);
    if(dict)
    {
        CFArrayAppendValue(matchingArray, dict);
        CFRelease(dict);
    }
    //mouse
    dict = createMatchingDictionary(kHIDPage_GenericDesktop, kHIDUsage_GD_Mouse);
    if(dict)
    {
        CFArrayAppendValue(matchingArray, dict);
        CFRelease(dict);
    }
    //joystick
    dict = createMatchingDictionary(kHIDPage_GenericDesktop, kHIDUsage_GD_Joystick);
    if(dict)
    {
        CFArrayAppendValue(matchingArray, dict);
        CFRelease(dict);
    }
    //digitizer / tablet
    dict = createMatchingDictionary(kHIDPage_Digitizer, kHIDUsage_Dig_Digitizer);
    if(dict)
    {
        CFArrayAppendValue(matchingArray, dict);
        CFRelease(dict);
    }   
    //touchpad
    dict = createMatchingDictionary(kHIDPage_Digitizer, kHIDUsage_Dig_TouchPad);
    if(dict)
    {
        CFArrayAppendValue(matchingArray, dict);
        CFRelease(dict);
    }   
    
    if ( CFGetTypeID( deviceManager ) == IOHIDManagerGetTypeID( ) ) 
    {
        IOHIDManagerSetDeviceMatchingMultiple(deviceManager, matchingArray);
        
        if(IOHIDManagerOpen(deviceManager, kIOHIDOptionsTypeNone) == kIOReturnSuccess)
        {
            devices = IOHIDManagerCopyDevices(deviceManager);
            
            if(CFSetGetCount(devices) > 0)
            {               
                CFSetApplyFunction(devices, createDevices, this);
            }
        }        
    }
    
    setAllEnable();
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
    KCLKeyBoard * keybd = (KCLKeyBoard*) i;
    keybd->setEnable();
    m_keyboardList.append(keybd);
    m_inputList.append(i);
}

void KCLDetectMac::addMouse(KCLInput *i) 
{
    KCLMouse * mouse = (KCLMouse*) i;
    mouse->setEnable();
    m_mouseList.append(mouse);
    m_inputList.append(i);
}

void KCLDetectMac::addJoystick(KCLInput *i)
{
    KCLJoystick * joy = (KCLJoystick*) i;
    joy->setEnable();
    m_joystickList.append(joy);
    m_inputList.append(i);
}

void KCLDetectMac::addTablet(KCLInput *i) 
{
    KCLTablet * tablet = (KCLTablet*) i;
    tablet->setEnable();
    m_tabletList.append(tablet);
    m_inputList.append(i);
}

void KCLDetectMac::addUnknown(KCLInput *i) 
{
    m_unknownList.append(i);
    m_inputList.append(i);
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

void KCLDetectMac::setAllEnable()
{
    qDebug() << "Enabling all devices";
    foreach(KCLInput *input, this->getInputList()) {
        input->setEnable();
    }
}

void KCLDetectMac::setAllDisable()
{
    foreach(KCLInput *input, this->getInputList()) {
        input->setDisable();
    }
}   

void KCLDetectMac::createDevices(const void *value, void *context)
{
    IOHIDDeviceRef device = (IOHIDDeviceRef) value;
    KCLDetectMac* detect = (KCLDetectMac*) context;
    
    if ( CFGetTypeID( device ) == IOHIDDeviceGetTypeID( ) ) 
    {
        IOHIDDeviceOpen(device,kIOHIDOptionsTypeNone);
        
        int usagePage = NULL;
        int usage = NULL; 
        
        CFTypeRef type = IOHIDDeviceGetProperty( device, CFSTR( kIOHIDDeviceUsagePageKey ) );
        
        if ( type ) 
        {
            // if this is a number
            if ( CFNumberGetTypeID() == CFGetTypeID( type ) ) 
            {
                // get it's value
                CFNumberGetValue( ( CFNumberRef ) type, kCFNumberSInt32Type, &usagePage );
            }
            CFRelease(type);
        }
        
        type = IOHIDDeviceGetProperty( device, CFSTR( kIOHIDDeviceUsageKey ) );
        
        if ( type ) 
        {
            // if this is a number
            if ( CFNumberGetTypeID() == CFGetTypeID( type ) ) 
            {
                // get it's value
                CFNumberGetValue( ( CFNumberRef ) type, kCFNumberSInt32Type, &usage );
            }
            CFRelease(type);
        }
        
        if(!usage || !usagePage)
        {
            type = IOHIDDeviceGetProperty( device, CFSTR( kIOHIDPrimaryUsagePageKey ) );
            
            if ( type ) 
            {
                // if this is a number
                if ( CFNumberGetTypeID() == CFGetTypeID( type ) ) 
                {
                    // get it's value
                    CFNumberGetValue( ( CFNumberRef ) type, kCFNumberSInt32Type, &usagePage );
                }
                CFRelease(type);
            }
            
            type = IOHIDDeviceGetProperty( device, CFSTR( kIOHIDPrimaryUsageKey ) );

            if ( type ) 
            {
                // if this is a number
                if ( CFNumberGetTypeID() == CFGetTypeID( type ) ) 
                {
                    // get it's value
                    CFNumberGetValue( ( CFNumberRef ) type, kCFNumberSInt32Type, &usage );
                }
                CFRelease(type);
            }
            
        }
        
        if(!usage || !usagePage)
        {
            usagePage = 0;
        }

        
        KCLInput* inputDevice;
        if(usagePage == kHIDPage_GenericDesktop)
        {
            switch (usage) 
            {
                case KCL::KeyBoard:
                    inputDevice = new KCLKeyBoard(device);
                    detect->addKeyboard(inputDevice);
                    break;
                case KCL::Mouse:
                    inputDevice = new KCLMouse(device);
                    detect->addMouse(inputDevice);
                    break;
                case KCL::Joystick:
                    inputDevice = new KCLJoystick(device);
                    detect->addJoystick(inputDevice);
                    break;
                default:
                    inputDevice = new KCLInput(device);
                    detect->addUnknown(inputDevice);
                    break;
            }
        }
        else if(usagePage == kHIDPage_Digitizer)
        {
            switch (usage) 
            {
                case KCL::Touchpad:
                    break;
                case KCL::Tablet:
                    inputDevice = new KCLTablet(device);
                    detect->addTablet(inputDevice);
                    break;
                default:
                    inputDevice = new KCLInput(device);
                    detect->addUnknown(inputDevice);
                    break;
            }
        }

    }
}

CFMutableDictionaryRef KCLDetectMac::createMatchingDictionary(UInt32 pUsagePage, UInt32 pUsage)
{
    CFMutableDictionaryRef matchDict = CFDictionaryCreateMutable(kCFAllocatorDefault, 1, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
    CFNumberRef usagePage = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &pUsagePage );
    CFNumberRef usage = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &pUsage);
    if(matchDict && usagePage && usage)
    {
        CFDictionarySetValue( matchDict, CFSTR( kIOHIDDeviceUsagePageKey ), usagePage);
        CFDictionarySetValue( matchDict, CFSTR( kIOHIDDeviceUsageKey ), usage);
        CFRelease(usagePage);
        CFRelease(usage);
        return matchDict;
    }
    else 
    {
        return NULL;
    }

    
}

#include "kcldetectmac.moc"
