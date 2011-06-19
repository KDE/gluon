/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Shantanu Tushar <jhahoneyk@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "extractor.h"

#include <QDir>
#include <QFile>
#include <QStringList>

Extractor::Extractor (const QString& sourceArchivePath, const QString& destinationDirectoryPath)
    : m_sourceArchivePath(sourceArchivePath), m_destinationDirectoryPath(destinationDirectoryPath)
{

}

void Extractor::start()
{
    QFile sourceArchiveFile(m_sourceArchivePath);
    sourceArchiveFile.open(QIODevice::ReadOnly);

    QDataStream stream(&sourceArchiveFile);
    stream.setVersion(QDataStream::Qt_4_7);
    int fileCount;
    stream >> fileCount;

    QStringList filesList;
    QList<qint64> sizes;
    qint64 totalSize = 0;

    //Read header for details of filenames and sizes
    for (int i=0; i<fileCount; i++) {
        QString file;
        qint64 size;
        stream >> file;
        stream >> size;
        filesList.append(file);
        sizes.append(size);
        totalSize += size;
    }

    sourceArchiveFile.seek(sourceArchiveFile.size()-totalSize);

    //Read and write actual file data, starting from the last file
    for (int i=0; i<fileCount; i++) {
        QFile file(QDir(m_destinationDirectoryPath).absoluteFilePath(filesList[i]));
        file.open(QIODevice::WriteOnly);
        file.write(sourceArchiveFile.read(sizes[i]));
        file.close();
    }
}
