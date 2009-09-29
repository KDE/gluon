#ifndef KCLTHREAD_H
#define KCLTHREAD_H
#include <QCoreApplication>
#include <QThread>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <linux/input.h>

#include "kcl_export.h"
#include "kclinputevent.h"

/**
 * \defgroup KCL KCL
 */
//@{

class KCLThread;
class KCL_EXPORT KCLThread : public QThread
{
    Q_OBJECT

public:
    KCLThread(const QString& devicePath, QObject *parent);
 ~KCLThread() {
        close(m_fd);
    }
    virtual void run();
protected:
    bool openDevice(const QString &devicePath);
    void closeDevice() {
        close(m_fd);
    }

private:
    int m_fd;
};

//@}
#endif // KCLTHREAD_H
