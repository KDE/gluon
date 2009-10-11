#ifndef KALCAPTURE_H
#define KALCAPTURE_H

#include <QObject>
#include <QStringList>

#include "kal_export.h"

/**
 * \defgroup KAL KAL
 */
//@{
class KALCapturePrivate;
class KAL_EXPORT KALCapture : public QObject
{
    Q_OBJECT

public:
    KALCapture(QString deviceName = QString(), QObject *parent = 0);
    ~KALCapture();

    bool isAvailable() const;

    static QStringList deviceList();

    void record(int duration = 1000);
    void save(const QString &fileName);

private:
    Q_DISABLE_COPY(KALCapture)
    
    KALCapturePrivate * d;
};

//@}
#endif // KALCAPTURE_H
