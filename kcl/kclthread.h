#ifndef KCLTHREAD_H
#define KCLTHREAD_H

#include <QThread>

#include "kcl_export.h"

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
