#ifndef DETECTLINUX_H
#define DETECTLINUX_H

#include "code.h"
#include "inputdevice.h"
#include "joystick.h"
#include "keyboard.h"
#include "mouse.h"
#include "tablet.h"
#include "detect.h"

#include <QtCore/QObject>
#include <QtCore/QList>

namespace GluonInput
{
  class GLUON_INPUT_EXPORT DetectLinux : public Detect
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
	  KeyBoard * keybd = (KeyBoard*)i;
	  m_keyboardList.append(keybd);
      }

      void addMouse(InputDevice *i) {
	  Mouse * mouse = (Mouse*)i;
	  m_mouseList.append(mouse);
      }

      void addJoystick(InputDevice *i) {
	  Joystick * joy = (Joystick*)i;
	  m_joystickList.append(joy);

      }

      void addTablet(InputDevice *i) {
	  Tablet * tablet = (Tablet*)i;
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
