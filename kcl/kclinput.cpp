#include "kclinput.h"
#include <KDebug>


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

    //    if(ioctl(m_fd, EVIOCGID, &m_device_info))
    //        kDebug()<<"cannot retrieve information of device";
    //
    //    char name[256]= "Unknown";
    //
    //    if(ioctl(m_fd, EVIOCGNAME(sizeof(name)), name) < 0)
    //        kDebug()<<"cannot retrieve name of device";
    //
    //    m_deviceName = QString(name);
    return true;
}














//===================================================================

KCLInput::KCLInput(const QString& device,QObject * parent)
    :QObject(parent),m_device(device)
{
    readInformation();
    inputListener = new KCLThread(device,parent);
    inputListener->start();
    connect(inputListener,SIGNAL(emitInputEvent(KCLInputEvent*)),this, SLOT(inputEvent(KCLInputEvent*)));
}
void KCLInput::inputEvent(KCLInputEvent * event)
{

switch ( event->type())
{





}



}

void KCLInput::readInformation()
{
    int m_fd = -1;
    if ((m_fd = open(m_device.toUtf8(), O_RDONLY)) < 0)
    {
        kDebug()<<"cannot read  information device";
        return;
    }

    if(ioctl(m_fd, EVIOCGID, &m_device_info))
        kDebug()<<"cannot retrieve information of device";
    char name[256]= "Unknown";
    if(ioctl(m_fd, EVIOCGNAME(sizeof(name)), name) < 0)
        kDebug()<<"cannot retrieve name of device";
    m_deviceName = QString(name);
close(m_fd);
}
