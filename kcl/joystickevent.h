#ifndef JOYSTICKEVENT_H
#define JOYSTICKEVENT_H

#include <QEvent>



class JoystickEvent : public QEvent
{
public:
    JoystickEvent(int type_,int time_, int value_, int number_);

int value(){return m_value;}
int number(){return m_number;}
int time(){return m_time;}
int type(){return m_type;}


enum {JoystickButtonPress=0x01 ,JoystickMove=0x02, JoystickInit=0x80 };

    private:
    int m_time;
    int m_value;
    int m_type;
    int m_number;
};

#endif // JOYSTICKEVENT_H
