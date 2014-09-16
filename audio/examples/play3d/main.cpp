/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 * Copyright (C) 2011-2012 Laszlo Papp <lpapp@kde.org>
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
#include "audio/audiofile.h"
#include "audio/playlists/singlefile.h"

#include <core/directoryprovider.h>

#include <QtCore/QDebug>
#include <QTimer>
#include <QtGui/QGuiApplication>

int main( int argc, char* argv[] )
{
    QGuiApplication app(argc, argv);
    
    QString shareInstallDir = GluonCore::DirectoryProvider::instance()->dataDirectory();
    GluonAudio::AudioFile* leftF = new GluonAudio::AudioFile( shareInstallDir + "/gluon/examples/audio/Front_Left.wav" );
    GluonAudio::AudioFile* rightF = new GluonAudio::AudioFile( shareInstallDir + "/gluon/examples/audio/Front_Right.wav" );
    GluonAudio::AudioFile* centerF = new GluonAudio::AudioFile( shareInstallDir + "/gluon/examples/audio/Front_Center.wav" );
    
    GluonAudio::SingleFile* leftPlaylist = new GluonAudio::SingleFile();
    GluonAudio::SingleFile* rightPlaylist = new GluonAudio::SingleFile();
    GluonAudio::SingleFile* centerPlaylist = new GluonAudio::SingleFile();
    
    GluonAudio::Source* leftSource = new GluonAudio::Source();
    GluonAudio::Source* rightSource = new GluonAudio::Source();
    GluonAudio::Source* centerSource = new GluonAudio::Source();

    leftSource->setPosition( Eigen::Vector3f(-1.f, 0.f, 0.f) );
    rightSource->setPosition( Eigen::Vector3f(1.f, 0.f, 0.f) );
    
    leftSource->setPlaylist( leftPlaylist );
    rightSource->setPlaylist( rightPlaylist );
    centerSource->setPlaylist( centerPlaylist );
    
    leftPlaylist->setFile( leftF );
    rightPlaylist->setFile( rightF );
    centerPlaylist->setFile( centerF );
    
    QObject::connect( leftPlaylist, SIGNAL(stopped()), rightPlaylist, SLOT(start()) );
    QObject::connect( rightPlaylist, SIGNAL(stopped()), centerPlaylist, SLOT(start()) );
    QObject::connect( centerPlaylist, SIGNAL(stopped()), &app, SLOT(quit()) );
    
    leftPlaylist->start();
    
    app.exec();

    delete leftF;
    delete rightF;
    delete centerF;
    delete leftSource;
    delete rightSource;
    delete centerSource;
    delete leftPlaylist;
    delete rightPlaylist;
    delete centerPlaylist;
}
