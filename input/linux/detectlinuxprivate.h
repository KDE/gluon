#ifndef DETECTLINUXPRIVATE_H
#define DETECTLINUXPRIVATE_H

#include <QtCore/QList>
#include <QtCore/QSharedData>

namespace GluonInput
{
  class InputDevice;
  class KeyBoard;
  class Mouse;
  class Joystick;
  class Tablet;
  
  class DetectLinuxPrivate : public QSharedData
  {
  public:
      DetectLinuxPrivate();
      DetectLinuxPrivate(DetectLinuxPrivate &other);
      
      QList<InputDevice *> m_inputList;
      QList<KeyBoard *> m_keyboardList;
      QList<Mouse *> m_mouseList;
      QList<Joystick *> m_joystickList;
      QList<Tablet *> m_tabletList;
      QList<InputDevice *> m_unknownList;
  };
}
#endif