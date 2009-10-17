#include "kclthread.h"
#include <KDebug>
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
            kError() << "Could not read input";
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
        kError() << "Could not read device";
        return false;
    }
    return true;
}
