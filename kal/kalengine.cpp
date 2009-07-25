#include "kalengine.h"
KALEngine *KALEngine::instance = NULL;

KALEngine::KALEngine(QString deviceName,QObject * parent)
            :QObject(parent)

{
    alutInitWithoutContext(0, 0);
    m_context = NULL;
    m_device =NULL;

    if (setDevice(deviceName))
    {
        if ( deviceName.isEmpty())
            kDebug()<<"set device to default";
        else kDebug()<<"set device to "<<deviceName;
    }
    else
        kDebug()<<"cannot set openAL device...";



    kDebug()<<alGetError();
}
KALEngine::KALEngine(Phonon::Category category, QObject *parent)
{

    m_phonon = new KALPhonon(this);
    m_phonon->setCategory(category);


}
KALEngine::~KALEngine()
{

    foreach ( KALSource * source, m_sourceList)
        delete source;

    foreach ( KALBuffer * buffer, m_bufferList)
        delete buffer;

    alcMakeContextCurrent(NULL);
    alcDestroyContext(m_context);
    alcCloseDevice(m_device);

}

KALEngine* KALEngine::getInstance(QString deviceName)
{
    if (NULL == instance)
    {
        instance=  new KALEngine(deviceName);
    }
    return instance;
}
KALEngine* KALEngine::getInstance(Phonon::Category category)
{
    if (NULL == instance)
    {
        instance=  new KALEngine(category);
    }
    return instance;
}



void KALEngine:: kill(){
    if (NULL != instance)
    {
        delete instance;
        instance = NULL;
    }
}

QStringList KALEngine::deviceList()
{
    const ALCchar* devices = alcGetString(NULL, ALC_DEVICE_SPECIFIER);

    // alcGetString returns a list of devices separated by a null char (the list itself ends with a double null char)
    // So we can't pass it directly to QStringList
    QStringList deviceStringList;
    if (devices) {
        while (strlen(devices) > 0) {
            deviceStringList << QString(devices);
            devices += strlen(devices) + 1;
        }
    }
    return deviceStringList;
}

bool KALEngine::setDevice(QString deviceName)
{

    if ( m_device)
    {
        alcMakeContextCurrent(NULL);
        alcDestroyContext(m_context);
        alcCloseDevice(m_device);
    }
    if (!deviceName.isEmpty()) {
        m_device = alcOpenDevice(deviceName.toUtf8());
    } else {
        m_device = alcOpenDevice(0);
    }

    if (!m_device) {
        return false;
    }

    m_context = alcCreateContext(m_device, 0);

    if (!m_context) {
        return false;
    }

    if (!alcMakeContextCurrent(m_context)) {
        return false;
    }
    return true;
}
