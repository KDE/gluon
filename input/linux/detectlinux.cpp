#include "detectlinux.h"

#include <QtCore/QDir>
#include <QtCore/QCoreApplication>
#include <QtGui/QMessageBox>
#include <QtCore/QDebug>

#include "linuxthread.h"

namespace GluonInput
{
  DetectLinux::DetectLinux(QObject * parent)
  : DetectAbstract(parent)
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
      DetectLinux *detect = this;
      detect->clear();
      QString path("/dev/input/by-path/");
      QDir event(path);
      
      foreach(const QString &name, event.entryList(QDir::Files)) {
	  InputDevice *temp = new InputDevice(new LinuxThread(path + name));
	  if (!temp->error()) {
	      
	      detect->addInput(temp);
	      switch (temp->deviceType()) {
		  case GluonInput::KeyBoardDevice:
		      qDebug() << "Kesyboard found";
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
