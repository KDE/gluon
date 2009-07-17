#include "joystickevent.h"



JoystickEvent::JoystickEvent(QEvent::Type type_,int time_, int value_, int number_)
        :QEvent(type_)
{



m_time = time_;
m_value = value_;
m_number = number_;

}
