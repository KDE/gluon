#ifndef KALSOUNDREADER_H
#define KALSOUNDREADER_H

#include <al.h>

#include "kal_export.h"

#include <QtCore/QString>
#include <QtCore/QStringList>

class KALBuffer;

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
    ~KALSoundReader();

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
    Q_DISABLE_COPY(KALSoundReader)
    KALSoundReaderPrivate *d;

};

//@}
#endif // KALSOUNDREADER_H
