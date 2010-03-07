#include "detectlinux.h"

#include <QtCore/QDir>
#include <QtCore/QCoreApplication>
#include <QtGui/QMessageBox>
#include <QtCore/QDebug>

#include <core/debughelper.h>

#include "inputthread.h"

namespace GluonInput
{
  DetectLinux::DetectLinux(QObject * parent)
  : Detect(parent)
  {
    d = new DetectLinuxPrivate();
  }

  DetectLinux::~DetectLinux()
  {
      //    kDebug()<<"clear device...";
      //    foreach ( KCLInput * input, m_inputList)
      //    {
      //        delete input;
      //    }
  }

  void DetectLinux::searchDevice()
  {
      DEBUG_FUNC_NAME
      DetectLinux *detect = this;
      detect->clear();
      QString path("/dev/input/by-path/");
      QDir event(path);

      DEBUG_TEXT("Starting search...");
      foreach(const QString &name, event.entryList(QDir::Files)) {
          DEBUG_TEXT(QString("Creating device for: %1").arg(path + name));

        InputDevice *temp = new InputDevice(new InputThread(path + name));
        if (!temp->error()) {

            detect->addInput(temp);
            switch (temp->deviceType()) {
            case GluonInput::KeyBoardDevice:
                qDebug() << "Keyboard found";
                detect->addKeyboard(temp);
                break;

            case GluonInput::MouseDevice:
                qDebug() << "Mouse found";
                detect->addMouse(temp);
                break;

            case GluonInput::TouchpadDevice:
                qDebug() << "Touchpad found";
                detect->addMouse(temp);
                break;

            case GluonInput::JoystickDevice:
                qDebug() << "Joystick found";
                detect->addJoystick(temp);
                break;

            case GluonInput::TabletDevice:
                qDebug() << "Tablet found";
                detect->addTablet(temp);
                break;

            case GluonInput::UnknownDevice:
                qDebug() << "Unknown device found";
                detect->addUnknown(temp);
                break;
            default:
                DEBUG_TEXT("Fail! Device has no type?!");
                DEBUG_TEXT(QString("Actual type sent is: %1").arg(temp->deviceType()));
            }
        }
    }
    detect->setAllEnabled();
  }

  void DetectLinux::setAllEnabled()
  {
      qDebug() << "Enabling all devices";
      foreach(InputDevice *input, this->getInputList()) {
	  input->setEnabled();
      }
  }

  void DetectLinux::setAllDisabled()
  {
      foreach(InputDevice *input, this->getInputList()) {
	  input->setDisabled();
      }
  }

  void DetectLinux::clear()
  {
      d->m_inputList.clear();
      d->m_keyboardList.clear();
      d->m_mouseList.clear();
      d->m_joystickList.clear();
      d->m_tabletList.clear();
      d->m_unknownList.clear();
  }
  
  void DetectLinux::addInput(InputDevice *i) 
  {
    d->m_inputList.append(i);
  }

  void DetectLinux::addKeyboard(InputDevice *i) 
  {
    KeyBoard * keybd = (KeyBoard*)i;
    d->m_keyboardList.append(keybd);
  }

  void DetectLinux::addMouse(InputDevice *i) 
  {
    Mouse * mouse = (Mouse*)i;
    d->m_mouseList.append(mouse);
  }
  
  void DetectLinux::addJoystick(InputDevice *i) 
  {
    Joystick * joy = (Joystick*)i;
    d->m_joystickList.append(joy);
  }

  void DetectLinux::addTablet(InputDevice *i) 
  {
    Tablet * tablet = (Tablet*)i;
    d->m_tabletList.append(tablet);
  }

  void DetectLinux::addUnknown(InputDevice *i)
  {
    d->m_unknownList.append(i);
  }
  
  QList<InputDevice *> DetectLinux::getInputList() 
  {
	  return d->m_inputList;
  }

  QList<KeyBoard *> DetectLinux::getKeyboardList() 
  {
	  return d->m_keyboardList;
  }

  QList<Mouse *> DetectLinux::getMouseList() 
  {
	  return d->m_mouseList;
  }

  QList<Joystick *> DetectLinux::getJoystickList() 
  {
	  return d->m_joystickList;
  }

  QList<Tablet *> DetectLinux::getTabletList() 
  {
	  return d->m_tabletList;
  }

  QList<InputDevice *> DetectLinux::getUnknownDeviceList() 
  {
	  return d->m_unknownList;
  }
}
#include "detectlinux.moc"
