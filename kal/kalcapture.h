#ifndef KALCAPTURE_H
#define KALCAPTURE_H

#include "kalbuffer.h"

#include <QObject>
#include <QStringList>
#include <QTimeLine>
#include <QVector>

#include <alc.h>
#include <alut.h>

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
    KALCapturePrivate * d;

};

//@}
#endif // KALCAPTURE_H
