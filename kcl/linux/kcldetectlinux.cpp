#include "kcldetectlinux.h"

#include <QDir>
#include <QtCore/QCoreApplication>
#include <QMessageBox>


KCLDetectLinux::KCLDetectLinux(QObject * parent)
: QObject(parent)
{
}

KCLDetectLinux::~KCLDetectLinux()
{
    //    kDebug()<<"clear device...";
    //    foreach ( KCLInput * input, m_inputList)
    //    {
    //        delete input;
    //    }
}

void KCLDetectLinux::searchDevice()
{
    KCLDetectLinux *detect = this;
    detect->clear();
    QString path("/dev/input/by-path/");
    QDir event(path);
    
    foreach(const QString &name, event.entryList(QDir::Files)) {
        KCLInput *temp = new KCLInput(path + name);
        if (!temp->error()) {
            
            detect->addInput(temp);
            switch (temp->deviceType()) {
                case KCL::KeyBoard:
                    kDebug() << "Kesyboard found";
                    detect->addKeyboard(temp);
                    break;
                    
                case KCL::Mouse:
                    kDebug() << "Mouse found";
                    detect->addMouse(temp);
                    break;
                    
                case KCL::Touchpad:
                    kDebug() << "Touchpad found";
                    detect->addMouse(temp);
                    break;
                    
                case KCL::Joystick:
                    kDebug() << "Joystick found";
                    detect->addJoystick(temp);
                    break;
                    
                case KCL::Tablet:
                    kDebug() << "Tablet found";
                    detect->addTablet(temp);
                    break;
                    
                case KCL::Unknown:
                    kDebug() << "Unknown device found";
                    detect->addUnknown(temp);
                    break;
            }
        }
    }
    detect->setAllEnable();
}

void KCLDetectLinux::clear()
{
    m_inputList.clear();
    m_keyboardList.clear();
    m_mouseList.clear();
    m_joystickList.clear();
    m_tabletList.clear();
    m_unknownList.clear();
}
