#include "kclinput.h"
#include <KDebug>
#include <QFile>

KCLInputEvent::KCLInputEvent(unsigned long tvSec_,unsigned long tvUsec_,unsigned short type_, unsigned short code_, unsigned short value_)
{
    struct timeval time;
    time.tv_sec = tvSec_;
    time.tv_usec= tvUsec_;

    m_inputEvent.time = time;
    m_inputEvent.type = type_;
    m_inputEvent.code=code_;
    m_inputEvent.value = value_;
}

KCLInputEvent::KCLInputEvent(struct input_event ev)
{
    m_inputEvent=ev;
}

//=================================================================
KCLThread::KCLThread(const QString &name, QObject * parent)
    :QThread(parent)
{
    openDevice(name);
}

void KCLThread::run()
{
   while (1)
    {
        struct input_event ev;
        int rd = read(m_fd, &ev, sizeof(struct input_event));
        if (rd < (int) sizeof(struct input_event))
            kDebug()<<"cannot read input...";
        else
        {
            KCLInputEvent * event= new KCLInputEvent(ev);
            emitInputEvent(event);
        }
    }
}

bool KCLThread::openDevice(const QString& device)
{
    m_fd = -1;
    if ((m_fd = open(device.toUtf8(), O_RDONLY)) < 0)
    {
        kDebug()<<"cannot read  device";
        return false;
    }
    return true;
}
//===================================================================

KCLInput::KCLInput(const QString& device,QObject * parent)
    :QObject(parent),m_device(device)
{
    m_error = false;
    m_move  = false;
    readInformation();
    inputListener = new KCLThread(device,parent);
    if (!error())
        inputListener->start();
    connect(inputListener,SIGNAL(emitInputEvent(KCLInputEvent*)),this, SLOT( slotInputEvent(KCLInputEvent*)));


}
void KCLInput:: slotInputEvent(KCLInputEvent * event)
{
    switch ( event->type())
    {
    case EV_KEY :
        if ( event->value() == 1)  // if click
        {
            m_buttons.append(event->code());
            kDebug()<<KCLCode::keyName(event->code())<<" pressed...";

        }

        if ( event->value() ==0) //if release
        {
            m_buttons.removeOne(event->code());
            kDebug()<<KCLCode::keyName(event->code())<<" release...";
        }
        break;

    case EV_REL:
        m_move = true;
        if (!m_axisPositions.contains(event->code()))
        m_axisPositions[event->code()] = event->value();
        else
     m_axisPositions[event->code()] += event->value();
        break;

  case EV_ABS:
          m_move = true;
          kDebug()<<KCLCode::absoluName(event->code())<<"="<< event->value();
        m_axisAbsolus[event->code()] = event->value();
        break;


   }


   inputEventFilter(event);

}
void KCLInput::readInformation()
{
    if (!QFile::exists(m_device))
    {
        kDebug()<<"m_device don't exist....";
        m_error = true;
        return;
    }

    int m_fd = -1;
    if ((m_fd = open(m_device.toUtf8(), O_RDONLY)) < 0)
    {
        kDebug()<<"cannot read  information device";
        m_error = true;
        return;
    }

    if(ioctl(m_fd, EVIOCGID, &m_device_info))
    {
        kDebug()<<"cannot retrieve information of device";
        m_error = true;
        return;
    }
    char name[256]= "Unknown";
    if(ioctl(m_fd, EVIOCGNAME(sizeof(name)), name) < 0)
    {
        kDebug()<<"cannot retrieve name of device";
        m_error = true;
    }
    m_deviceName = QString(name);
    close(m_fd);
}
void KCLInput::inputEventFilter(KCLInputEvent * event)
{


}
