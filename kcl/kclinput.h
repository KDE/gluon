#ifndef KCLINPUT_H
#define KCLINPUT_H

#include <QThread>
#include <QMap>
#include <QPair>
#include <QPoint>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <linux/input.h>
#include <KDebug>
#include "kclcode.h"

class KCLInput;
class KCLThread;
class KCLInputEvent;

class AbsVal
{
public:
    AbsVal(int v=0,int m=0, int M=0, int f=0, int F=0)
    {
        value = v;
        min =m;
        max = M;
        flat = f;
        fuzz = F;
    }
    int value;
    int min;
    int max;
    int flat;
    int fuzz;
};

class KCLInputEvent
{
public:
    KCLInputEvent(unsigned long tvSec_,unsigned long tvUsec_,unsigned short type_, unsigned short code_, unsigned short value_);
    KCLInputEvent(struct input_event ev);
    unsigned long tvSec(){return m_inputEvent.time.tv_sec;}
    unsigned long tvUsec(){return m_inputEvent.time.tv_usec;}
    unsigned short type(){return m_inputEvent.type;}
    unsigned short code(){return m_inputEvent.code;}
    unsigned int value(){return m_inputEvent.value;}
    struct input_event inputEvent(){return m_inputEvent;}
private:
    struct input_event m_inputEvent;
};

//---------------------------------------------------------------------------------------------
class KCLThread : public QThread
{
    Q_OBJECT
public:
    KCLThread(const QString& name, QObject *parent=0);
    ~KCLThread(){close(m_fd);}
    virtual void run();
signals:
    void emitInputEvent(KCLInputEvent * event);
protected:
    bool openDevice(const QString &device);
    void closeDevice(){close(m_fd);}
private:
    int m_fd;
};
//---------------------------------------------------------------------------------------------
class KCLInput : public QObject
{
    Q_OBJECT
public:
    enum DEVICE {KEYBOARD, MOUSE,JOYSTICK,TABLET,TOUCHPAD,UNKNOWN};
    KCLInput(const QString& device,QObject * parent=0);
    ~KCLInput(){inputListener->exit();}
    unsigned int vendor(){return m_device_info.vendor;}
    unsigned int product(){return m_device_info.product;}
    unsigned int version(){return m_device_info.version;}
    unsigned int bustype(){return m_device_info.bustype;}
    QString device(){return m_device;}
    QString name(){return m_deviceName;}

    bool button(int code){return m_buttons.contains(code);}
    bool anyPress(){if (m_buttons.size()>0) return true; else return false;}
    bool anyMove(){if ( m_move) {m_move=false;return true;} return false; }
    int axisPosition(int code){
        if(m_axisPositions.contains(code))
            return m_axisPositions[code] ;
        else return 0;
    }
    int axisAbsolu(int code){
        if(m_axisAbsolus.contains(code))
            return m_axisAbsolus[code] ;
        else return 0;

    }
QList<int> buttonCapabilities(){return m_buttonCapabilities;}

    bool error(){return m_error;}
    virtual void inputEventFilter(KCLInputEvent * event);

public slots:
    void slotInputEvent(KCLInputEvent * event);

protected :
        void readInformation();

private:
KCLThread * inputListener;
struct input_id m_device_info;
struct input_event m_currentEvent;
QString m_device;
QString m_deviceName;
DEVICE m_deviceType;

QList<int> m_buttons;
QMap<int,int> m_axisPositions;
QMap<int,int> m_axisAbsolus;
QList<int> m_buttonCapabilities;
QMap<int, AbsVal> m_axisCapabilities;
bool m_move;
bool m_error;
};

//---------------------------------------------------------------------------------------------






#endif // KCLINPUT_H
