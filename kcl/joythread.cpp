
#include "joythread.h"
#include <KDebug>
#include <QCoreApplication>

#include <QMouseEvent>
JoyThread::JoyThread(QString device, QObject * parent)
    :QThread(parent)
{
    m_fd = open(device.toUtf8(), O_RDONLY);

    if (m_fd < 0) 
        kDebug() << "No Joystick found... Cannot open " ;
    else
        kDebug()<<"Joystick found...";
}
void JoyThread::run()
{
    while ( 1==1)
    {
        int res = read(m_fd, &m_jsev, sizeof(struct js_event)); //bloquante
        if (!res) {
            kDebug() << "cannot read joystick input...";
        }
        else
        {
            JoystickEvent* event = new JoystickEvent(m_jsev.type,m_jsev.time,m_jsev.value,m_jsev.number);
            sendJoystickEvent(event);
        }

    }
}

