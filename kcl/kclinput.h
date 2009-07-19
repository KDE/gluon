#ifndef KCLINPUT_H
#define KCLINPUT_H

#include <QThread>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <linux/input.h>

class KCLInput;
class KCLThread;
class KCLInputEvent;

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

private:
    struct input_event m_inputEvent;

};


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
    struct input_id m_device_info;

};

class KCLInput : public QObject
{
    Q_OBJECT
public:
    KCLInput(const QString& device,QObject * parent=0);
    unsigned int vendor(){return m_device_info.vendor;}
    unsigned int product(){return m_device_info.product;}
    unsigned int version(){return m_device_info.version;}
    unsigned int bustype(){return m_device_info.bustype;}
    QString device(){return m_device;}
    QString name(){return m_deviceName;}
public slots:
    void inputEvent(KCLInputEvent * event);

protected :
        void readInformation();



private:

KCLThread * inputListener;
struct input_id m_device_info;
QString m_device;
QString m_deviceName;


};

#endif // KCLINPUT_H
