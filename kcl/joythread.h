#ifndef JOYTHREAD_H
#define JOYTHREAD_H

#include <QThread>
#include <QTimer>
#include <linux/joystick.h>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "joystickevent.h"
class JoyThread : public QThread
{
    Q_OBJECT
public:
    JoyThread(QObject * parent=0);
    virtual void run();
    int button(){return m_jsev.value;}

    signals:
    void sendJoystickEvent(JoystickEvent * event);

private:
    struct js_event m_jsev;


    int m_fd;
QTimer * m_readTimer;




};













#endif
