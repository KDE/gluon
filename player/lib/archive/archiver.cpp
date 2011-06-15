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

#include "archiver.h"

#include <QFileInfo>
#include <QDir>

#include <QDebug>

Archiver::Archiver (const QString& sourceDirectoryPath, const QString& destinationArchivePath)
    : m_sourceDirectoryPath (sourceDirectoryPath), m_destinationArchivePath (destinationArchivePath)
{
    qDebug() << "Archiver with " << sourceDirectoryPath << " and " << destinationArchivePath;
}

void Archiver::start()
{
    addFilesInDir (m_sourceDirectoryPath);
    createData();
}

void Archiver::addFilesInDir (QString path)
{
    QDir dir (path);

    if (dir.count() == 0)
        return;         //FIXME: This ain't great, empty dirs will be skipped

    foreach (QString file, dir.entryList (QDir::Files | QDir::Hidden)) {
        if (!QFileInfo (dir.absoluteFilePath (file)).isDir()) {
            QString fullPath (dir.absoluteFilePath (file));
            addFileToList (QDir (m_sourceDirectoryPath).relativeFilePath (fullPath));
        }
    }

    foreach (QString tdir, dir.entryList (QDir::Hidden | QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks)) {
        if (QFileInfo (dir.absoluteFilePath (tdir)).isDir()) { //QDir::Hidden includes even hidden non-dirs, so have to check
            dir.cd (tdir);
            addFilesInDir (dir.absolutePath());
            dir.cdUp();
        }
    }
}

void Archiver::addFileToList (QString relativePath)
{
    QFileInfo info (QDir (m_sourceDirectoryPath).absoluteFilePath(relativePath));
    m_files.append (relativePath);
    m_totalSize += info.size();
    qDebug() << "AADDING " << relativePath << " SIZE " << info.size();
}

void Archiver::createData()
{
    QDataStream stream (&m_data, QIODevice::WriteOnly);
    stream.setVersion (QDataStream::Qt_4_7);
    stream << m_files.count();

    //Write headers into the stream
    foreach (QString file, m_files) {
        QFileInfo info (QDir (m_sourceDirectoryPath).absoluteFilePath (file));
        stream << file;
        stream << info.size();
        qDebug() << "WRITING " << file << " SIZE " << info.size();
    }

    //Append actual file contents
    foreach (QString filename, m_files) {
        QFile file (QDir (m_sourceDirectoryPath).absoluteFilePath (filename));
        file.open (QIODevice::ReadOnly);
        m_data.append (file.readAll());
        file.close();
    }

    QFile file(m_destinationArchivePath);
    file.open(QIODevice::WriteOnly);
    file.write(qCompress(m_data));
    file.close();
}
