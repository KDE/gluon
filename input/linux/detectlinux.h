#ifndef DETECTLINUX_H
#define DETECTLINUX_H

#include "code.h"
#include "inputdevice.h"
#include "joystick.h"
#include "keyboard.h"
#include "mouse.h"
#include "tablet.h"
#include "detectabstract.h"

#include <QtCore/QObject>
#include <QtCore/QList>

namespace GluonInput
{
  class GLUON_INPUT_EXPORT DetectLinux : public DetectAbstract
  {
      Q_OBJECT

  public:
      DetectLinux(QObject * parent);
      ~DetectLinux();

      void searchDevice();
      void setAllEnabled();
      void setAllDisabled();


      void addInput(InputDevice *i) {
	  m_inputList.append(i);
      }

      void addKeyboard(InputDevice *i) {
	  //KeyBoard * keybd = new KeyBoard(i->devicePath());
	  KeyBoard * keybd = (KeyBoard*)i;
	  keybd->setEnabled();
	  m_keyboardList.append(keybd);
      }

      void addMouse(InputDevice *i) {
	  //Mouse * mouse = new Mouse(i->devicePath());
	  Mouse * mouse = (Mouse*)i;
	  mouse->setEnabled();
	  m_mouseList.append(mouse);
      }

      void addJoystick(InputDevice *i) {
	  //Joystick * joy = new Joystick(i->devicePath());
	  Joystick * joy = (Joystick*)i;
	  joy->setEnabled();
	  m_joystickList.append(joy);

      }

      void addTablet(InputDevice *i) {
	  //Tablet * tablet = new Tablet(i->devicePath());
	  Tablet * tablet = (Tablet*)i;
	  tablet->setEnabled();
	  m_tabletList.append(tablet);
      }

      void addUnknown(InputDevice *i) {
	  m_unknownList.append(i);
      }

      void clear();

  private:
  };
}
#endif
