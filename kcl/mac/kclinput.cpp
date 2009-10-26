#include "kclinput.h"

#include <QtCore/QDebug>
#include <QtGui/QApplication>
#include <QtCore/QFile>
#include <QtGui/QMessageBox>
#include <QtGui/QMouseEvent>

KCLInput::KCLInput(IOHIDDeviceRef device, QObject * parent)
: QObject(parent)
{
    this->init();
    
    m_device = device;
    readInformation();
    inputListener = new KCLThread(m_device, m_deviceType, this);
}

KCLInput::KCLInput()
{
    this->init();
}

KCLInput::~KCLInput()
{
    setDisable();
    IOHIDDeviceClose(m_device, kIOHIDOptionsTypeNone);
    CFRelease(m_device);
    delete inputListener;
    
    qDebug() << "Closed device :" << deviceName();
}

void KCLInput::init()
{
    m_error = false;
    m_enable = true;
    m_absMove  = false;
    m_relMove = false;
    m_lastAbsAxis = 0;
    m_lastRelAxis = 0;
    m_msgError = QString();
    m_deviceName = "Unknown";
}

int KCLInput::vendor()const 
{
    return m_vendor;
}

int KCLInput::product()const 
{
    return m_product;
}

int KCLInput::version()const 
{
    return m_version;
}

int KCLInput::bustype()const 
{
    return m_bustype;
}

const IOHIDDeviceRef KCLInput::device()const 
{
    return m_device;
}

const QString KCLInput::deviceName() const
{
    return m_deviceName;
}

KCL::DeviceFlag KCLInput::deviceType()const 
{
    return m_deviceType;
}

bool KCLInput::button(int code)const 
{
    return m_buttons.contains(code);
}

int KCLInput::anyPress() const 
{
    if (m_buttons.size() > 0) 
    {
        return m_buttons.last();
    } else {
        return 0;
    }
}

bool KCLInput::anyAbsMove() 
{
    if (m_absMove) 
    {
        m_absMove = false;
        return true;
    }
    return false;
}

bool KCLInput::anyRelMove() 
{
    if (m_relMove) 
    {
        m_relMove = false;
        return true;
    }
    return false;
}

int KCLInput::lastAbsAxis()const 
{
    return m_lastAbsAxis;
}

int KCLInput::lastRelAxis()const 
{
    return m_lastRelAxis;
}

int KCLInput::relAxisValue(int code)const 
{
    if (m_relAxis.contains(code)) 
    {
        return m_relAxis[code];
    } else {
        return 0;
    }
}

int KCLInput::absAxisValue(int code)const
{
    if (m_absAxis.contains(code)) 
    {
        return m_absAxis[code];
    } else {
        return 0;
    }
}

QList<int> KCLInput::buttonCapabilities()const 
{
    return m_buttonCapabilities;
}

QList<int> KCLInput::absAxisCapabilities()const 
{
    return m_absAxisCapabilities;
}

QList<int> KCLInput::relAxisCapabilities()const 
{
    return m_relAxisCapabilities;
}

AbsVal KCLInput::axisInfo(int axisCode)const 
{
    return m_absAxisInfos[axisCode];
}

bool KCLInput::error()const 
{
    return m_error;
}

QString KCLInput::msgError()const
{
    return m_msgError;
}




bool KCLInput::isEnable() const
{
    return m_enable;
}


bool KCLInput::event(QEvent * evt)
{
    KCLInputEvent * event = (KCLInputEvent*)evt;
    emit eventSent(event);

    switch (event->type()) 
    {
        case KCL::Key:
            
            if (event->value() == 1) 
            { // if click
                m_buttons.append(event->code());
                emit buttonPressed(event->code());
                emit pressed();
            }
            
            if (event->value() == 0) 
            { //if release
                m_buttons.removeOne(event->code());
                emit buttonReleased(event->code());
            }
            return true;
            break;
            
        case KCL::RelativeAxis:
            emit moved();
            m_relMove = true;
            m_lastRelAxis = event->code();
            m_relAxis[event->code()] = event->value();
            emit relAxisChanged(event->code(), event->value());
            return true;
            break;
            
        case KCL::AbsoluAxis:
            emit moved();
            m_absMove = true;
            m_lastAbsAxis = event->code();
            m_absAxis[event->code()] = event->value();
            emit absAxisChanged(event->code(), event->value());
            return true;
            break;
        
        default:
            break;
    }
    
    return QObject::event(evt);
}


void KCLInput::readInformation()
{
    CFStringRef deviceNameRef = (CFStringRef)IOHIDDeviceGetProperty(m_device, CFSTR(kIOHIDProductKey));
    if(CFGetTypeID(deviceNameRef) == CFStringGetTypeID())
    {
        m_deviceName = CFStringGetCStringPtr(deviceNameRef, kCFStringEncodingMacRoman);
    }
    
    CFTypeRef type  = IOHIDDeviceGetProperty(m_device, CFSTR( kIOHIDVendorIDKey));
    if(type)
    {
        CFNumberGetValue( ( CFNumberRef ) type, kCFNumberSInt32Type, &m_vendor );
        CFRelease(type);
    }
    else 
    {
        m_vendor = -1;
    }

    type  = IOHIDDeviceGetProperty(m_device, CFSTR( kIOHIDProductIDKey));
    if(type)
    {
        CFNumberGetValue( ( CFNumberRef ) type, kCFNumberSInt32Type, &m_product );
        CFRelease(type);
    }
    else 
    {
        m_product = -1;  
    }

    
    type  = IOHIDDeviceGetProperty(m_device, CFSTR( kIOHIDTransportKey));
    if(type)
    {
        if(CFGetTypeID(type) == CFNumberGetTypeID())
        {
            CFNumberGetValue( ( CFNumberRef ) type, kCFNumberSInt32Type, &m_bustype );
            CFRelease(type);            
        }
        else if(CFGetTypeID(type) == CFStringGetTypeID())
        {
            m_bustype = -1;
        }
        else 
        {
            m_bustype = -1;
        }

    }
    
    type = IOHIDDeviceGetProperty(m_device, CFSTR( kIOHIDVersionNumberKey));
    if(type)
    {
        CFNumberGetValue( ( CFNumberRef ) type, kCFNumberSInt32Type, &m_version );
        CFRelease(type);
    }
    else 
    {
        m_version = -1;
    }

    m_buttonCapabilities.clear();
    m_absAxisCapabilities.clear();
    m_relAxisCapabilities.clear();
    m_absAxisInfos.clear();
    
    CFArrayRef elements = IOHIDDeviceCopyMatchingElements(m_device, NULL, kIOHIDOptionsTypeNone);
    
    if(elements)
    {
        for(int i = 0; i < CFArrayGetCount(elements); i++)
        {
            IOHIDElementRef elementRef = (IOHIDElementRef)CFArrayGetValueAtIndex(elements,(CFIndex)i);
            if(CFGetTypeID(elementRef) == IOHIDElementGetTypeID())
            {
                int usagePage = IOHIDElementGetUsagePage( elementRef );
                int usage = IOHIDElementGetUsage( elementRef );
                
                if(usagePage == kHIDPage_Button)
                {
                    m_buttonCapabilities.append(usage);
                }
                else if(usagePage == kHIDPage_KeyboardOrKeypad)
                {
                    if(usage > 3 && usage <= 231 && !m_buttonCapabilities.contains(usage))
                        m_buttonCapabilities.append(usage);
                }
                else if (usagePage == kHIDPage_GenericDesktop)
                {
                    if(usage <= 47 || usage == 60)
                        continue;
                    
                    if(IOHIDElementIsRelative(elementRef))
                    {
                        m_relAxisCapabilities.append(usage);
                    }
                    else
                    {
                        m_absAxisCapabilities.append(usage);
                        AbsVal val(0,0,0,0);
                        val.max = (int)IOHIDElementGetLogicalMax(elementRef);
                        val.min = (int)IOHIDElementGetLogicalMin(elementRef);
                        IOHIDValueRef valRef = NULL;
                        IOHIDDeviceGetValue(m_device, elementRef, &valRef); 
                        val.value = (int) valRef;
                        m_absAxisInfos[usage] = val;
                        if(usage == kHIDUsage_GD_X)
                        {
                            m_xAbsUsage = usage;
                        }
                        else if (usage == kHIDUsage_GD_Y)
                        {
                            m_yAbsUsage = usage;
                        }
                        else if(usage == kHIDUsage_GD_Z)
                        {
                            m_zAbsUsage = usage;
                        }
                    }
                }
            }
        }
    }
    
    CFRelease(elements);
    
    int deviceUsage = NULL;
    
    type = IOHIDDeviceGetProperty( m_device, CFSTR( kIOHIDPrimaryUsageKey));
    
    if(type)
    {
        CFNumberGetValue((CFNumberRef) type, kCFNumberSInt32Type, &deviceUsage);
        CFRelease(type);
    }
    else 
    {
        type = IOHIDDeviceGetProperty( m_device, CFSTR( kIOHIDDeviceUsageKey));
        CFNumberGetValue((CFNumberRef) type, kCFNumberSInt32Type, &deviceUsage);
        CFRelease(type);
    }

    switch (deviceUsage)
    {
        case KCL::KeyBoard:
            m_deviceType = KCL::KeyBoard;
            break;
        case KCL::Mouse:
            m_deviceType = KCL::Mouse;
            break;
        case KCL::Joystick:
            m_deviceType = KCL::Joystick;
            break;
        case KCL::Tablet:
            m_deviceType = KCL::Tablet;
            break;
        case KCL::Touchpad:
            m_deviceType = KCL::Touchpad;
            break;
        default:
            m_deviceType = KCL::Unknown;
            break;
    }
}

void KCLInput::setEnable()
{
    m_enable = true;
    if (!error()) 
    {
        if(inputListener != NULL)
        {
            inputListener->terminate();
            delete inputListener;
        }
        inputListener = new KCLThread(m_device, m_deviceType,this);
        inputListener->start();
    }
}

void KCLInput::setDisable()
{
    m_enable = false;
    m_buttons.clear();
    m_relAxis.clear();
    m_absAxis.clear();
    m_relMove = false;
    m_absMove = false;
    inputListener->terminate();
    delete inputListener;
}

QString KCLInput::buttonName(int code) const
{
    if(m_deviceType == KCL::KeyBoard)
    {
        return KCLCode::buttonName(code);
    }
    else
    {
        return "Button " + QVariant(code).toString();
    }

}

#include "kclinput.moc"
