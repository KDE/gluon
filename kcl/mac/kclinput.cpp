#include "kclinput.h"

#include <QDebug>
#include <QApplication>
#include <QFile>
#include <QMessageBox>
#include <QMouseEvent>

KCLInput::KCLInput(IOHIDDeviceRef device, QObject * parent)
: QObject(parent)
{
    this->init();
    
    m_device = device;
    readInformation();
    inputListener = new KCLThread(m_device, this);
}

KCLInput::KCLInput()
{
    this->init();
}

KCLInput::~KCLInput()
{
    IOHIDDeviceClose(m_device, kIOHIDOptionsTypeNone);
    CFRelease(m_device);
    setDisable();
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
    m_deviceName = "no name";
}

int KCLInput::vendor()const 
{
    return CFStringGetIntValue( (CFStringRef) IOHIDDeviceGetProperty(m_device, CFSTR( kIOHIDVendorIDKey)));
}

int KCLInput::product()const 
{
    return CFStringGetIntValue( (CFStringRef) IOHIDDeviceGetProperty(m_device, CFSTR( kIOHIDProductIDKey)));
}

int KCLInput::version()const 
{
    return CFStringGetIntValue( (CFStringRef) IOHIDDeviceGetProperty(m_device, CFSTR( kIOHIDVersionNumberKey)));
}

int KCLInput::bustype()const 
{
    return CFStringGetIntValue( (CFStringRef) IOHIDDeviceGetProperty(m_device, CFSTR( kIOHIDTransportKey)));
}

const IOHIDDeviceRef KCLInput::device()const 
{
    return m_device;
}

const QString KCLInput::deviceName() const
{
    const char * deviceNameChar = CFStringGetCStringPtr((CFStringRef) IOHIDDeviceGetProperty(m_device, CFSTR( kIOHIDVendorIDKey)), kCFStringEncodingMacRoman);
    QString deviceName( deviceNameChar);
    return  deviceName;
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
    /*if (!QFile::exists(m_devicePath)) {
        qDebug() << "m_devicePath does not exist";
        m_error = true;
        m_msgError += "device url does not exist \n";
        return;
    }

    int m_fd = -1;
    if ((m_fd = open(m_devicePath.toUtf8(), O_RDONLY)) < 0) {
        qDebug() << "Could not open device" << m_devicePath;
        m_error = true;
        m_msgError += "could not open the device \n";
        return;
    }

    if (ioctl(m_fd, EVIOCGID, &m_device_info)) {
        qDebug() << "Could not retrieve information of device" << m_devicePath;
        m_msgError += "could not retrieve information of device\n";
        m_error = true;
        return;
    }

    char name[256] = "Unknown";
    if (ioctl(m_fd, EVIOCGNAME(sizeof(name)), name) < 0) {
        qDebug() << "could not retrieve name of device" << m_devicePath;
        //        m_msgError += "cannot retrieve name of device\n";
        //        m_error = true;
    }

    m_deviceName = QString(name);
    ///this next bit can be shared across platform
    unsigned long bit[EV_MAX][NBITS(KEY_MAX)];
    int abs[5];
    memset(bit, 0, sizeof(bit));
    ioctl(m_fd, EVIOCGBIT(0, EV_MAX), bit[0]);

    m_buttonCapabilities.clear();
    m_absAxisInfos.clear();

    for (int i = 0; i < EV_MAX; i++) {
        if (test_bit(i, bit[0])) {
            if (!i) {
                continue;
            }

            ioctl(m_fd, EVIOCGBIT(i, KEY_MAX), bit[i]);
            for (int j = 0; j < KEY_MAX; j++) {
                if (test_bit(j, bit[i])) {
                    if (i == EV_KEY) {
                        m_buttonCapabilities.append(j);
                    }

                    if (i == EV_REL) {
                        m_relAxisCapabilities.append(j);
                    }

                    if (i == EV_ABS) {
                        ioctl(m_fd, EVIOCGABS(j), abs);
                        AbsVal cabs(0, 0, 0, 0);
                        for (int k = 0; k < 5; k++) {
                            if ((k < 3) || abs[k]) {
                                switch (k) {
                                case 0:
                                    cabs.value = abs[k];
                                    break;
                                case 1:
                                    cabs.min = abs[k];
                                    break;
                                case 2:
                                    cabs.max = abs[k];
                                    break;
                                case 3:
                                    cabs.fuzz = abs[k];
                                    break;
                                case 4:
                                    cabs.flat = abs[k];
                                    break;
                                }
                            }
                        }
                        m_absAxisCapabilities.append(j);
                        m_absAxisInfos[j] = cabs;
                    }
                }
            }
        }
    }

    //===============Find Force feedback ?? ===============





    close(m_fd);

    m_deviceType = KCL::Unknown;

    if (m_buttonCapabilities.contains(BTN_STYLUS)) 
    {
        m_deviceType  = KCL::Tablet;
    }

    if (m_buttonCapabilities.contains(BTN_STYLUS) || m_buttonCapabilities.contains(ABS_PRESSURE)) 
    {
        m_deviceType  = KCL::Mouse;
    }

    if (m_buttonCapabilities.contains(BTN_TRIGGER)) 
    {
        m_deviceType  = KCL::Joystick;
    }

    if (m_buttonCapabilities.contains(BTN_MOUSE)) 
    {
        m_deviceType  = KCL::Mouse;
    }

    if (m_buttonCapabilities.contains(KEY_ESC)) 
    {
        m_deviceType  = KCL::KeyBoard;
    }*/
}

void KCLInput::setEnable()
{
    m_enable = true;
    if (!error()) {
        inputListener = new KCLThread(m_device, this);
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
}
