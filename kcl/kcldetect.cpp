#include "kcldetect.h"

#include <QtCore/QCoreApplication>
#include <QtGui/QMessageBox>
#include <QtCore/QDebug>;

#ifdef linux
#include "kcldetectlinux.h"
#endif

#ifdef __APPLE__
#include "kcldetectmac.h"
#endif

#ifdef _WIN32
#include "kcldetectwin.h"
#endif

KCLDetectAbstract * KCLDetect::m_instance = NULL;

KCLDetect::KCLDetect(QObject * parent)
        : QObject(parent)
{
}

KCLDetect::~KCLDetect()
{
    //    kDebug()<<"clear device...";
    //    foreach ( KCLInput * input, m_inputList)
    //    {
    //        delete input;
    //    }
}

void KCLDetect::init()
{
    if (!m_instance) 
    {
        qDebug() << "Setting parent";
        QObject *parent = QCoreApplication::instance();
        if (!parent) {
            qDebug() << "No QCoreApplication instance found, the KCLDetect instance may be leaked when leaving";
        }
        
#ifdef linux
        qDebug() << "Creating instance: Linux";
        m_instance = new KCLDetectLinux(parent);
#endif
        
#ifdef __APPLE__
        qDebug() << "Creating instance: Mac";
        KCLDetectMac* k = new KCLDetectMac(parent);
        m_instance =(KCLDetectAbstract*)k;
#endif
        
#ifdef _WIN32
        qDebug() << "Creating instance: Win";
        m_instance = new KCLDetectWin(parent);
#endif
        qDebug() << "Instance created, searching devices";
        m_instance->searchDevice();
    }
}

void KCLDetect::searchDevice()
{    
    if(!m_instance)
    {
        init();
    }
    else
    {
        m_instance->searchDevice();
    }
}

void KCLDetect::setAllEnable()
{
    init();
    m_instance->setAllEnable();
}

void KCLDetect::setAllDisable()
{
    init();
    m_instance->setAllDisable();
}   

unsigned int KCLDetect::deviceCount() 
{
    qDebug() << "Checking if instance exists";
    init();
    qDebug() << "Accessing Inputlist";
    return inputList().size();
}

unsigned int KCLDetect::keyboardCount() 
{
    init();
    return m_instance->getKeyboardList().size();
}

unsigned int KCLDetect::mouseCount() 
{
    init();
    return m_instance->getMouseList().size();
}

unsigned int KCLDetect::joystickCount() 
{
    init();
    return m_instance->getJoystickList().size();
}

unsigned int KCLDetect::tabletCount() 
{
    init();
    return m_instance->getTabletList().size();
}

unsigned int KCLDetect::unknownDeviceCount() 
{
    init();
    return m_instance->getUnknownDeviceList().size();
}

QList<KCLKeyBoard*> KCLDetect::keyboardList() 
{
    init();
    return m_instance->getKeyboardList();
}

QList<KCLMouse*> KCLDetect::mouseList()
{
    init();
    return m_instance->getMouseList();
}

QList<KCLJoystick*> KCLDetect::joystickList()
{
    init();
    return m_instance->getJoystickList();
}

QList<KCLTablet*> KCLDetect::tabletList() 
{
    init();
    return m_instance->getTabletList();
}

QList<KCLInput*> KCLDetect::unknownDeviceList() 
{
    init();
    return m_instance->getUnknownDeviceList();
}

KCLInputList KCLDetect::inputList() 
{
    init();
    return m_instance->getInputList();
}

KCLKeyBoard* KCLDetect::keyboard(int id) 
{
    init();
    return m_instance->getKeyboardList().at(id);
}

KCLMouse* KCLDetect::mouse(int id) 
{
    init();
    return m_instance->getMouseList().at(id);
}

KCLJoystick* KCLDetect::joystick(int id) 
{
    init();
    return m_instance->getJoystickList().at(id);
}

KCLTablet* KCLDetect::tablet(int id) 
{
    init();
    return m_instance->getTabletList().at(id);
}

KCLInput* KCLDetect::input(int id) 
{
    init();
    return m_instance->getInputList().at(id);
}

#include "kcldetect.moc"
