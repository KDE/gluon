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

#include "audio/player.h"

#include <QtCore/QCoreApplication>
// #include <QtCore/QDebug>

int main( int argc, char* argv[] )
{
    QCoreApplication app( argc, argv );

    GluonAudio::Player* player = new GluonAudio::Player;
    player->append( "/usr/share/sounds/KDE-Sys-Log-In.ogg" );
    player->append( "/usr/share/sounds/KDE-Sys-Log-Out.ogg" );
    player->setVolume( 0.9 );  //between 0 and 1

    // qDebug() << "Playing sound "<< player->currentDuration() << "seconds.";
    QObject::connect( player, SIGNAL( finished() ), &app, SLOT( quit() ) );
    player->play();

    app.exec();

    delete player;
}

