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

#include <core/directoryprovider.h>

#include <QtCore/QDebug>
#include <QTimer>
#include <QtGui/QGuiApplication>

GluonAudio::AudioFile* leftF;
GluonAudio::AudioFile* rightF;
GluonAudio::AudioFile* centerF;

GluonAudio::Source* leftSource;
GluonAudio::Source* rightSource;
GluonAudio::Source* centerSource;

void playRight()
{
    rightF->feedSource( rightSource );
    rightSource->play();
}

void playCenter()
{
    centerF->feedSource( centerSource );
    centerSource->play();
}

int main( int argc, char* argv[] )
{
    QGuiApplication app(argc, argv);
    
    QString shareInstallDir = GluonCore::DirectoryProvider::instance()->dataDirectory();
    leftF = new GluonAudio::AudioFile( shareInstallDir + "/gluon/examples/audio/Front_Left.wav" );
    rightF = new GluonAudio::AudioFile( shareInstallDir + "/gluon/examples/audio/Front_Right.wav" );
    centerF = new GluonAudio::AudioFile( shareInstallDir + "/gluon/examples/audio/Front_Center.wav" );
    
    leftSource = new GluonAudio::Source();
    rightSource = new GluonAudio::Source();
    centerSource = new GluonAudio::Source();

    leftSource->setPosition( Eigen::Vector3f(-1.f, 0.f, 0.f) );
    rightSource->setPosition( Eigen::Vector3f(1.f, 0.f, 0.f) );
    
    QTimer timerRight;
    timerRight.setSingleShot(true);
    timerRight.setInterval(3000);
    QObject::connect( &timerRight, &QTimer::timeout, playRight );
    timerRight.start();
    
    QTimer timerCenter;
    timerCenter.setSingleShot(true);
    timerCenter.setInterval(6000);
    QObject::connect( &timerCenter, &QTimer::timeout, playCenter );
    timerCenter.start();
    
    leftF->feedSource( leftSource );
    leftSource->play();
    
    app.exec();

    delete leftF;
    delete rightF;
    delete centerF;
    delete leftSource;
    delete rightSource;
    delete centerSource;
}
