/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Laszlo Papp <lpapp@kde.org>
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

#include "audio/source.h"
#include "audio/abstractfile.h"
#include "audio/musicfile.h"
#include "audio/playlists/linearplaylist.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QObject>
// #include <QtCore/QDebug>

QList<GluonAudio::AbstractFile*> readFilesFromFile( char* file )
{
    QList<GluonAudio::AbstractFile*> files;
    
    QFile qfile( file );
    if( !qfile.open( QIODevice::ReadOnly ) )
        return files;
    while (!qfile.atEnd()) {
        QString line = QString::fromUtf8( qfile.readLine() );
        if( !line.trimmed().isEmpty() )
            files << new GluonAudio::MusicFile( line.trimmed() );
    }
    return files;
}

int main( int argc, char* argv[] )
{
    QCoreApplication app( argc, argv );
    
    GluonAudio::Source source;
    
    QList<GluonAudio::AbstractFile*> files;
    
    if( argc == 1 )
    {
        files << new GluonAudio::MusicFile( "/usr/share/sounds/KDE-Sys-Log-In.ogg" );
        files << new GluonAudio::MusicFile( "/usr/share/sounds/KDE-Sys-Log-Out.ogg" );
    }
    else
    {
        files = readFilesFromFile(argv[1]);
    }
    
    GluonAudio::LinearPlaylist playlist;
    playlist.setFiles(files);
    source.setPlaylist(&playlist);
    
    QObject::connect( &playlist, SIGNAL(stopped()), &app, SLOT(quit()) );
    
    playlist.start();

    app.exec();
}

