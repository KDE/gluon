#ifndef KALENGINE2_H
#define KALENGINE2_H

#include "kalsource.h"
#include "kalbuffer.h"
#include "kalphonon.h"

#include <Phonon/Global>
#include <KDebug>

#include <QtCore/QObject>
#include <QtCore/QStringList>
#include <QtCore/QList>

#include <alc.h>
#include <alut.h>

class KALSource;
class KALBuffer;

class KALEngine : public QObject
{
private:
    KALEngine(QString deviceName = QString(), QObject *parent = 0);
    KALEngine(Phonon::Category category, QObject *parent = 0);
    ~KALEngine();

public:
    bool setDevice(QString deviceName);

    ALCcontext * context() {
        return m_context;
    }

    ALCdevice* device() {
        return m_device;
    }

    static QStringList deviceList();

    static KALEngine *getInstance(QString deviceName = QString());
    static KALEngine *getInstance(Phonon::Category category);

    static void kill();

    int sourceCount() {
        return m_sourceList.size();
    }

    void addSource(KALSource * source) {
        m_sourceList.append(source);
    }
    void removeSource(KALSource * source) {
        m_sourceList.removeOne(source);
    }

    void addBuffer(KALBuffer * buffer) {
        m_bufferList.append(buffer);
    }
    void removeBuffer(KALBuffer * buffer) {
        m_bufferList.removeOne(buffer);
    }

private:
    static KALEngine *instance;
    ALCcontext *m_context;
    ALCdevice *m_device;
    KALPhonon *m_phonon;
    QList<KALSource *> m_sourceList;
    QList<KALBuffer *> m_bufferList;
};

#endif // KALENGINE2_H
