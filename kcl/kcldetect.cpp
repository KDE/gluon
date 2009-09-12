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

KCLDetect * KCLDetect::instance()
{
    if (!m_instance) {
        QObject *parent = QCoreApplication::instance();
        if (!parent) {
            kWarning() << "No QCoreApplication instance found, the KALEngine instance may be leaked when leaving";
        }
        m_instance =  new KCLDetect(parent);
        m_instance->searchDevice();

    }
    return m_instance;
}
void KCLDetect::searchDevice()
{
    KCLDetect * detect = instance();
    detect->clear();
    QString path("/dev/input/by-path/");
    QDir event(path);

    foreach(QString name, event.entryList(QDir::Files)) {
        KCLInput * temp = new KCLInput(path + name);
        if (!temp->error()) {
            detect->addInput(temp);
            switch (temp->deviceType()) {
            case KCL::KeyBoard: kDebug()<<"keyboard found...";
                detect->addKeyboard(dynamic_cast<KCLKeyBoard*>(temp));
                break;

            case KCL::Mouse: kDebug()<<"mouse found...";
                detect->addMouse(dynamic_cast<KCLMouse*>(temp));
                break;

            case KCL::Touchpad: kDebug()<<"touchpad found...";
                detect->addMouse(dynamic_cast<KCLMouse*>(temp));
                break;


            case KCL::Joystick: kDebug()<<"joystick found...";
                detect->addJoystick(dynamic_cast<KCLJoystick*>(temp));
                break;


            case KCL::Tablet: kDebug()<<"tablet found...";
                detect->addTablet(dynamic_cast<KCLTablet*>(temp));
                break;


            case KCL::Unknown: kDebug()<<"unknow device found...";
                detect->addUnkwnown(temp);
                break;
            }
        }
    }
    detect->setAllEnable();
}

void KCLDetect::setAllEnable()
{
    foreach(KCLInput * input, instance()->allInputs()) {
        input->setEnable();
    }
}
void KCLDetect::setAllDisable()
{
    foreach(KCLInput * input, instance()->allInputs()) {
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



