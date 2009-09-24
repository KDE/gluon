#include "kcldetect.h"

#include <QDir>
#include <QtCore/QCoreApplication>
#include <QMessageBox>

KCLDetect *KCLDetect::m_instance = NULL;


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

KCLDetect *KCLDetect::instance()
{
    if (!m_instance) {
        QObject *parent = QCoreApplication::instance();
        if (!parent) {
            kWarning() << "No QCoreApplication instance found, the KCLDetect instance may be leaked when leaving";
        }
        m_instance = new KCLDetect(parent);
        m_instance->searchDevice();
    }

    return m_instance;
}

void KCLDetect::searchDevice()
{
    KCLDetect *detect = instance();
    detect->clear();
    QString path("/dev/input/by-path/");
    QDir event(path);

    foreach(QString name, event.entryList(QDir::Files)) {
        KCLInput *temp = new KCLInput(path + name);
        if (!temp->error()) {

            detect->addInput(temp);
            switch (temp->deviceType()) {
            case KCL::KeyBoard:
                kDebug() << "Keyboard found";
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

void KCLDetect::setAllEnable()
{
    foreach(KCLInput *input, instance()->inputList()) {
        input->setEnable();
    }
}

void KCLDetect::setAllDisable()
{
    foreach(KCLInput *input, instance()->inputList()) {
        input->setDisable();
    }
}   

void KCLDetect::clear()
{
    m_inputList.clear();
    m_keyboardList.clear();
    m_mouseList.clear();
    m_joystickList.clear();
    m_tabletList.clear();
    m_unknownList.clear();
}



