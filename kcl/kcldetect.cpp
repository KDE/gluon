#include "kcldetect.h"

#include <QDir>
#include <QtCore/QCoreApplication>
#include <QMessageBox>
#include <QtGlobal>
KCLDetect *KCLDetect::m_instance = NULL;


KCLDetect::KCLDetect(QObject * parent)
        : QObject(parent)
{
}

KCLDetect::~KCLDetect()
{
    //    qDebug()<<"clear device...";
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
            qWarning() << "No QCoreApplication instance found, the KCLDetect instance may be leaked when leaving";
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

    foreach(const QString &name, event.entryList(QDir::Files)) {
        KCLInput *temp = new KCLInput(path + name);
        if (!temp->error()) {

            detect->addInput(temp);
            switch (temp->deviceType()) {
            case KCL::KeyBoard:
                qDebug() << "Keyboard found";
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



