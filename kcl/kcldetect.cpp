#include "kcldetect.h"

#include <QtCore/QCoreApplication>
#include <QMessageBox>
#include <QDebug>;

#include "kclinput.h"
#include "kclmouse.h"
#include "kclkeyboard.h"
#include "kcljoystick.h"
#include "kcltablet.h"

/*#ifdef _LINUX_
KCLDetectLinux * KCLDetect::m_instance = NULL;
#endif
#ifdef _APPLE_
KCLDetectMac * KCLDetect::m_instance = NULL;
#endif
#ifdef _WIN32
KCLDetectWin * KCLDetect::m_instance = NULL;
#endif*/

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
    if (!m_instance) {
        QObject *parent = QCoreApplication::instance();
        if (!parent) {
            qDebug() << "No QCoreApplication instance found, the KCLDetect instance may be leaked when leaving";
        }
#ifdef _LINUX_
        m_instance = new KCLDetectLinux(parent);
#elseifdef _APPLE_
        m_instance = new KCLDetectMac(parent);
#elseifdef _WIN32
        m_instance = new KCLDetectWin(parent);
#endif
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
    foreach(KCLInput *input, m_instance->getInputList()) {
        input->setEnable();
    }
}

void KCLDetect::setAllDisable()
{
    init();
    foreach(KCLInput *input, m_instance->getInputList()) {
        input->setDisable();
    }
}   

unsigned int KCLDetect::deviceCount() 
{
    init();
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
