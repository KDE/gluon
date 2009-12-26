#include "kcldetectlinux.h"

#include <QDir>
#include <QtCore/QCoreApplication>
#include <QMessageBox>


KCLDetectLinux::KCLDetectLinux(QObject * parent)
: KCLDetectAbstract(parent)
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
                    qDebug() << "Kesyboard found";
                    detect->addKeyboard(temp);
                    break;
                    
                case KCL::Mouse:
                    qDebug() << "Mouse found";
                    detect->addMouse(temp);
                    break;
                    
                case KCL::Touchpad:
                    qDebug() << "Touchpad found";
                    detect->addMouse(temp);
                    break;
                    
                case KCL::Joystick:
                    qDebug() << "Joystick found";
                    detect->addJoystick(temp);
                    break;
                    
                case KCL::Tablet:
                    qDebug() << "Tablet found";
                    detect->addTablet(temp);
                    break;
                    
                case KCL::Unknown:
                    qDebug() << "Unknown device found";
                    detect->addUnknown(temp);
                    break;
            }
        }
    }
    detect->setAllEnabled();
}

void KCLDetectLinux::setAllEnabled()
{
    qDebug() << "Enabling all devices";
    foreach(KCLInput *input, this->getInputList()) {
        input->setEnable();
    }
}

void KCLDetectLinux::setAllDisabled()
{
    foreach(KCLInput *input, this->getInputList()) {
        input->setDisable();
    }
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

#include "kcldetectlinux.moc"
