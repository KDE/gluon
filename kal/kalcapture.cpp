#include "kalcapture.h"
#include <KDebug>
#include <QTime>
#include <QFile>
KALCapture::KALCapture(QString deviceName , QObject * parent)
        : QObject(parent)
{

    if (isAvaible()) {
        CaptureDevice = alcCaptureOpenDevice(deviceName.toUtf8(), 44100, AL_FORMAT_MONO16, 44100);
        if (!CaptureDevice)
            kDebug() << "cannot set the capture device";
    } else kDebug() << "cannot find avaible capture device";

}

KALCapture::~KALCapture()
{
    alcCaptureCloseDevice(CaptureDevice);
}

bool KALCapture::isAvaible()
{

    if (alcIsExtensionPresent(Device, "ALC_EXT_CAPTURE") == AL_FALSE)
        return false;
    else return true;
}
QStringList KALCapture::captureDeviceList()
{
    QStringList list;
    // Récupération des devices de capture disponibles
    const ALCchar* DeviceList = alcGetString(NULL, ALC_CAPTURE_DEVICE_SPECIFIER);

    if (DeviceList) {
        // Extraction des devices contenus dans la chaîne renvoyée
        while (strlen(DeviceList) > 0) {
            list.append(DeviceList);
            DeviceList += strlen(DeviceList) + 1;
        }
    }
    return list;
}

void KALCapture::record(int duration)
{

    QTime now;
    now.start();
    while (now.elapsed() < duration) {

        ALCint SamplesAvailable;
        alcGetIntegerv(CaptureDevice, ALC_CAPTURE_SAMPLES, 1, &SamplesAvailable);
        if (SamplesAvailable > 0) {
            samples.append(SamplesAvailable);
            alcCaptureSamples(CaptureDevice, &samples.last(), SamplesAvailable);
        }
    }
    alcCaptureStop(CaptureDevice);


    ALCint SamplesAvailable;
    alcGetIntegerv(CaptureDevice, ALC_CAPTURE_SAMPLES, 1, &SamplesAvailable);
    if (SamplesAvailable > 0) {
        samples.append(SamplesAvailable);
        alcCaptureSamples(CaptureDevice, &samples.last(), SamplesAvailable);
    }

}


void KALCapture::save(const QString& filename)
{

    SF_INFO FileInfos;
    FileInfos.channels   = 1;
    FileInfos.samplerate = 44100;
    FileInfos.format     = SF_FORMAT_PCM_16 | SF_FORMAT_WAV;

    SNDFILE* File = sf_open(filename.toStdString().c_str(), SFM_WRITE, &FileInfos);
    if (!File)
        return;

    // Ecriture des échantillons audio
    sf_write_short(File, &samples[0], samples.size());

    // Fermeture du fichier
    sf_close(File);






}
