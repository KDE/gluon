#ifndef JOYSTICKEVENT_H
#define JOYSTICKEVENT_H

#include <QEvent>



class JoystickEvent : public QEvent
{
public:
    JoystickEvent(QEvent::Type type_,int time_, int value_, int number_);

    enum {JoystickPressEvent=1666, JoystickMoveEvent=1667};

int value(){return m_value;}
int number(){return m_number;}

    private:
    int m_time;
    int m_value;
    int m_type;
    int m_number;
};

#endif // JOYSTICKEVENT_H
