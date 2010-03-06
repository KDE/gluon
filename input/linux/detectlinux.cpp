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
      m_inputList.clear();
      m_keyboardList.clear();
      m_mouseList.clear();
      m_joystickList.clear();
      m_tabletList.clear();
      m_unknownList.clear();
  }
}
#include "detectlinux.moc"
