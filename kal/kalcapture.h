#ifndef KALCAPTURE_H
#define KALCAPTURE_H

#include <QObject>
#include <QStringList>
#include <QVector>
#include <QTimeLine>
#include <QVector>
#include <alc.h>
#include <alut.h>
#include "kalbuffer.h"
class KALCapture : public QObject
{
    Q_OBJECT
public:
    KALCapture(QString deviceName = QString(), QObject * parent=0);
  ~KALCapture();
    bool isAvaible();
    static QStringList captureDeviceList();
    void record(int duration = 1000);
    void save(const QString& filename);


private:
    ALCdevice* Device;
    ALCdevice* CaptureDevice;
QVector<ALshort> samples;
ALuint buffer;
};

#endif // KALCAPTURE_H
