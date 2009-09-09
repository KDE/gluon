#ifndef KALSOUNDREADER_H
#define KALSOUNDREADER_H

#include "kalbuffer.h"

#include <QFileInfo>
#include <QString>
#include <QStringList>

class KALSoundReader
{
public:
    KALSoundReader(const QString& fileName);

    QString format() {
        QFileInfo file(m_fileName);
        return file.completeSuffix();
    }

    bool canRead();

    static QStringList supportedSoundFormats() {
        return (QStringList() << "wav" << "ogg");
    }
    QString fileName() const {
        return m_fileName;
    }

    ALuint buffer();

protected:
    ALuint fromWav();
    ALuint fromOgg();

private:
    QString m_fileName;
};

#endif // KALSOUNDREADER_H
