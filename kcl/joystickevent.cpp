#include "joystickevent.h"



JoystickEvent::JoystickEvent(int type_,int time_, int value_, int number_)
        :QEvent(QEvent::Type())
{
m_time = time_;
m_value = value_;
m_number = number_;
m_type = type_;
}
