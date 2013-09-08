/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Shantanu Tushar <shaan7in@gmail.com>
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

#include <QtCore/QFileInfo>
#include <QtCore/QDir>

Archiver::Archiver( const QString& sourceDirectoryPath, const QString& destinationArchivePath )
    : m_sourceDirectoryPath( sourceDirectoryPath ), m_destinationArchivePath( destinationArchivePath )
{
}

void Archiver::start()
{
    QDir parentDir( m_sourceDirectoryPath );
    parentDir.cdUp();
    m_sourceParentDirectoryPath = parentDir.path();
    addFilesInDir( m_sourceDirectoryPath );
    writeArchiveToFile();
}

void Archiver::addFilesInDir( QString path )
{
    QDir dir( path );

    if( dir.count() == 0 )
        return;         //FIXME: This ain't great, empty dirs will be skipped

    foreach( const QString& file, dir.entryList( QDir::Files | QDir::Hidden ) )
    {
        if( !QFileInfo( dir.absoluteFilePath( file ) ).isDir() )
        {
            QString fullPath( dir.absoluteFilePath( file ) );
            addFileToList( QDir( m_sourceParentDirectoryPath ).relativeFilePath( fullPath ) );
        }
    }

    foreach( const QString& tdir, dir.entryList( QDir::Hidden | QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks ) )
    {
        if( QFileInfo( dir.absoluteFilePath( tdir ) ).isDir() ) //QDir::Hidden includes even hidden non-dirs, so have to check
        {
            dir.cd( tdir );
            addFilesInDir( dir.absolutePath() );
            dir.cdUp();
        }
    }
}

void Archiver::addFileToList( QString relativePath )
{
    QFileInfo info( QDir( m_sourceParentDirectoryPath ).absoluteFilePath( relativePath ) );
    m_files.append( relativePath );
    m_totalSize += info.size();
}

void Archiver::writeArchiveToFile()
{
    QFile arcFile( m_destinationArchivePath );
    arcFile.open( QIODevice::WriteOnly );
    QDataStream stream( &arcFile );
    stream.setVersion( QDataStream::Qt_4_7 );
    stream << m_files.count();

    //Write headers into the stream
    foreach( const QString& file, m_files )
    {
        QFileInfo info( QDir( m_sourceParentDirectoryPath ).absoluteFilePath( file ) );
        stream << file;
        stream << info.size();
    }

    //Append actual file contents
    foreach( const QString& filename, m_files )
    {
        QFile file( QDir( m_sourceParentDirectoryPath ).absoluteFilePath( filename ) );
        file.open( QIODevice::ReadOnly );
        arcFile.write( file.readAll() );
        file.close();
    }

    arcFile.close();
}
