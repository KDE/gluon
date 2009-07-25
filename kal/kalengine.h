#ifndef KALENGINE2_H
#define KALENGINE2_H

#include <QObject>
#include <KDebug>
#include <alc.h>
#include <alut.h>
#include <QtCore/QStringList>
#include <Phonon/Global>
#include <QStringList>
#include <QList>
#include "kalsource.h"
class KALSource;
class KALEngine : public QObject
{
private:
    KALEngine(QString deviceName=QString(),QObject * parent=0);
    ~KALEngine();



public:
bool setDevice(QString deviceName);
 ALCcontext * context(){return m_context;}
  ALCdevice* device(){return m_device;}
static QStringList deviceList();

static KALEngine * getInstance();

  static void kill ();


void addSource(KALSource * source){m_sourceList.append(source);}

    private:
    static KALEngine * instance;
    ALCcontext *m_context;
    ALCdevice *m_device;

   QList<KALSource*> m_sourceList;


};






#endif // KALENGINE2_H
