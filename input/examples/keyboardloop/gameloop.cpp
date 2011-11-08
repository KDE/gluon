/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Kim Jung Nissen <jungnissen@gmail.com>
 * Copyright (C) 2010 Laszlo Papp <lpapp@kde.org>
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

#include "gameloop.h"

#include "input/inputdevice.h"
#include "input/keyboard.h"

#include <QtCore/QTime>
#include <QtCore/QDebug>
#include <QtCore/QCoreApplication>

GameLoop::GameLoop( Keyboard* keyb )
{
    keyboard = keyb;
    connect( this, SIGNAL(startGameLoop()), SLOT(gameLoop()), Qt::QueuedConnection );
}

void GameLoop::run()
{
    emit startGameLoop();
}

void GameLoop::gameLoop()
{
    int nextTick = 0;
    int loops = 0;
    QTime timer;
    int updatesPerSecond = 25;
    int maxFrameSkip = 5;
    int millisecondsPerUpdate = 1000 / updatesPerSecond;
    timer.start();

    qDebug() << "starting gameloop";
    while( true )
    {
        QCoreApplication::processEvents();
        loops = 0;
        while( timer.elapsed() > nextTick && loops < maxFrameSkip )
        {
            foreach( int button, keyboard->buttonCapabilities() )
            {
                if( keyboard->buttonPressed( button ) )
                    qDebug() << keyboard->buttonName( button ) << " is pressed ";

            }

            nextTick += millisecondsPerUpdate;
            ++loops;
        }
    }
}

#include "gameloop.moc"
