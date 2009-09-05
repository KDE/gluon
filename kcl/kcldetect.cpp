#include "kcldetect.h"
#include <QDir>
KCLDetect::KCLDetect(QObject * parent)
    :QObject(parent)
{
    searchDevice();
}
KCLDetect::~KCLDetect()
  {
kDebug()<<"clear device...";
    foreach ( KCLInput * input, m_inputList)
    {
        delete input;
    }
m_inputList.clear();

  }
void KCLDetect::searchDevice()
{
    QString path("/dev/input/by-path/");
    QDir event(path);

    foreach  ( QString name, event.entryList(QDir::Files))
    {

        KCLInput * temp = new KCLInput(path+name);


        if (!temp->error())
        {
  m_inputList.append(temp);

        switch( temp->deviceType() )
        {
        case KCL_KEYBOARD: kDebug()<<"keyboard found...";
            m_keyboardList.append(temp);
            break;

        case KCL_MOUSE: kDebug()<<"mouse found...";
            m_mouseList.append(temp);
            break;

        case KCL_TOUCHPAD: kDebug()<<"touchpad found...";
            m_mouseList.append(temp);
            break;


        case KCL_JOYSTICK: kDebug()<<"joystick found...";
            m_joystickList.append(temp);
            break;


        case KCL_TABLET: kDebug()<<"tablet found...";
            m_tabletList.append(temp);
            break;


        case KCL_UNKNOWN: kDebug()<<"unknow device found...";
            m_unknownList.append(temp);
            break;
      }
    }

    }


}







