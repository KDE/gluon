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

#ifndef ARCHIVER_H
#define ARCHIVER_H

#include "gluon_player_export.h"
#include <QStringList>

class GLUON_PLAYER_EXPORT Archiver
{

public:
    Archiver (const QString& sourceDirectoryPath, const QString& destinationArchivePath);
    void start();
private:
    QStringList m_files;
    QString m_sourceDirectoryPath;
    QString m_destinationArchivePath;
    QString m_sourceParentDirectoryPath;
    qint64 m_totalSize;

    void addFilesInDir (QString path);
    void addFileToList (QString relativePath);
    void writeArchiveToFile();
};

#endif // ARCHIVER_H
