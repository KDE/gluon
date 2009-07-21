#include "kclinput.h"
#include <KDebug>
#include <QFile>
#define BITS_PER_LONG (sizeof(long) * 8)
#define NBITS(x) ((((x)-1)/BITS_PER_LONG)+1)
#define OFF(x)  ((x)%BITS_PER_LONG)
#define BIT(x)  (1UL<<OFF(x))
#define LONG(x) ((x)/BITS_PER_LONG)
#define test_bit(bit, array)	((array[LONG(bit)] >> OFF(bit)) & 1)

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
        kDebug()<<"cannot read  information device "<<m_device;;
        m_error = true;
        return;
    }

    if(ioctl(m_fd, EVIOCGID, &m_device_info))
    {
        kDebug()<<"cannot retrieve information of device "<<m_device;;
        m_error = true;
        return;
    }
    char name[256]= "Unknown";
    if(ioctl(m_fd, EVIOCGNAME(sizeof(name)), name) < 0)
    {
        kDebug()<<"cannot retrieve name of device "<<m_device;
        m_error = true;
    }
    m_deviceName = QString(name);




    unsigned long bit[EV_MAX][NBITS(KEY_MAX)];
    int abs[5];
    memset(bit, 0, sizeof(bit));
    ioctl(m_fd, EVIOCGBIT(0, EV_MAX), bit[0]);

    m_buttonCapabilities.clear();
    m_axisCapabilities.clear();

    for (int i = 0; i < EV_MAX; i++)
        if (test_bit(i, bit[0])) {

        if (!i) continue;
        ioctl(m_fd, EVIOCGBIT(i, KEY_MAX), bit[i]);
        for (int j = 0; j < KEY_MAX; j++)
            if (test_bit(j, bit[i])) {
            if ( i == EV_KEY)
                m_buttonCapabilities.append(j);

            if (i == EV_ABS) {
                ioctl(m_fd, EVIOCGABS(j), abs);
                AbsVal cabs(0,0,0,0);
                for (int k = 0; k < 5; k++)
                    if ((k < 3) || abs[k])
                    {

                    switch (k)
                    {
                        case 0:cabs.value = abs[k];break;
                        case 1:cabs.min = abs[k];break;
                        case 2:cabs.max = abs[k];break;
                        case 3:cabs.fuzz = abs[k];break;
                        case 4: cabs.flat = abs[k];break;
                    }
                }
                m_axisCapabilities[j] = cabs;

            }
        }
    }
    close(m_fd);

m_device = KCL_UNKNOWN;

if ( m_buttonCapabilities.contains( BTN_STYLUS ))
    m_deviceType  =KCL_TABLET;

if ((m_buttonCapabilities.contains( BTN_STYLUS )) || (m_buttonCapabilities.contains(ABS_PRESSURE)))
    m_deviceType  =KCL_TOUCHPAD;

if ( m_buttonCapabilities.contains( BTN_TRIGGER ))
    m_deviceType  =KCL_JOYSTICK;

if ( m_buttonCapabilities.contains( BTN_MOUSE ))
    m_deviceType  = KCL_MOUSE;

if ( m_buttonCapabilities.contains( KEY_ESC))
    m_deviceType  = KCL_KEYBOARD;

}
void KCLInput::inputEventFilter(KCLInputEvent * event)
{


}
