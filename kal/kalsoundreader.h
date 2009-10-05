#ifndef KALSOUNDREADER_H
#define KALSOUNDREADER_H

#include "kalbuffer.h"

#include <QFileInfo>
#include <QString>
#include <QStringList>

/**
 * \defgroup KAL KAL
 */

/**
* @class KALSoundReader kal/kalsoundreader.h <KAL/KALSoundReader>
* KALSoundReader generate a buffer from a sound file. Currently it allows to read Wav and ogg file.
* Phonon output device in KALEngine
*/

//@{
class KALSoundReaderPrivate;
class KAL_EXPORT KALSoundReader
{
public:
    KALSoundReader(const QString& fileName);

    QString format() const;
    bool canRead() const;
    static QStringList supportedSoundFormats() ;
    QString fileName() const;
    ALuint alBuffer();
    KALBuffer *buffer();

protected:
    ALuint fromWav();
    ALuint fromOgg();

private:
    KALSoundReaderPrivate *d;

};

//@}
#endif // KALSOUNDREADER_H
