#ifndef KALSOUNDREADER_H
#define KALSOUNDREADER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QFileInfo>
#include "kalbuffer.h"
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
    const QString& fileName() {
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
