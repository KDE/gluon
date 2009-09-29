#ifndef KALSOUNDREADER_H
#define KALSOUNDREADER_H

#include "kalbuffer.h"

#include <QFileInfo>
#include <QString>
#include <QStringList>

/**
 * \defgroup KAL KAL
 */
//@{
class KALSoundReaderPrivate;
class KAL_EXPORT KALSoundReader
{
public:
    KALSoundReader(const QString& fileName);

    QString format();
    bool canRead();

    static QStringList supportedSoundFormats() {
        return (QStringList() << "wav" << "ogg");
    }
    QString fileName() const;
    ALuint buffer();

protected:
    ALuint fromWav();
    ALuint fromOgg();

private:
    KALSoundReaderPrivate *d;

};

//@}
#endif // KALSOUNDREADER_H
