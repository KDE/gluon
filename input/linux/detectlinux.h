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
#include <QtCore/QSharedData>

namespace GluonInput
{
	class DetectLinuxPrivate;
	
  class GLUON_INPUT_EXPORT DetectLinux : public Detect
  {
      Q_OBJECT

  public:
      DetectLinux(QObject * parent);
      ~DetectLinux();

      void searchDevice();
      void setAllEnabled();
      void setAllDisabled();
      
      QList<InputDevice *> getInputList();
      QList<KeyBoard *> getKeyboardList();
      QList<Mouse *> getMouseList();
      QList<Joystick *> getJoystickList();
      QList<Tablet *> getTabletList();
      QList<InputDevice *> getUnknownDeviceList();

      void addInput(InputDevice *i);
      void addKeyboard(InputDevice *i);
      void addMouse(InputDevice *i);
      void addJoystick(InputDevice *i);
      void addTablet(InputDevice *i);
      void addUnknown(InputDevice *i);

      void clear();

  private:
    QSharedDataPointer<DetectLinuxPrivate> d;
  };
}
#endif
