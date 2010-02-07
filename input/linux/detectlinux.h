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

      QList<InputDevice *> getInputList() {
	  return m_inputList;
      }

      QList<KeyBoard *> getKeyboardList() {
	  return m_keyboardList;
      }

      QList<Mouse *> getMouseList() {
	  return m_mouseList;
      }

      QList<Joystick *> getJoystickList() {
	  return m_joystickList;
      }

      QList<Tablet *> getTabletList() {
	  return m_tabletList;
      }

      QList<InputDevice *> getUnknownDeviceList() {
	  return m_unknownList;
      }


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
      QList<InputDevice *> m_inputList;
      QList<KeyBoard *> m_keyboardList;
      QList<Mouse *> m_mouseList;
      QList<Joystick *> m_joystickList;
      QList<Tablet *> m_tabletList;
      QList<InputDevice *> m_unknownList;
  };
}
#endif
