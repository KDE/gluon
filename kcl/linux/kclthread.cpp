
#include "kclthread.h"

#include "kclinputevent.h"

#include <QCoreApplication>
#include <QDebug>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/input.h>

KCLThread::KCLThread(const QString &devicePath, QObject * parent)
    : QThread(parent)
{
    openDevice(devicePath);
}

void KCLThread::run()
{
    while (1) {
        struct input_event ev;
        int rd = read(m_fd, &ev, sizeof(struct input_event));
        if (rd < (int) sizeof(struct input_event)) {
            qDebug() << "Could not read input";
        } else {
            KCLInputEvent *event = new KCLInputEvent(ev);
            QCoreApplication::sendEvent(parent(),event);
        }
    }
}

bool KCLThread::openDevice(const QString& devicePath)
{
    m_fd = -1;
    if ((m_fd = open(devicePath.toUtf8(), O_RDONLY)) < 0) {
        qDebug() << "Could not read device";
        return false;
    }
    return true;
}

#include "kclthread.moc"
