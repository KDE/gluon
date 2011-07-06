/******************************************************************************
 * This file is part of the Gluon Development Platform
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

#include "input/inputmanager.h"

#include <QtGui/QApplication>
#include <QtCore/QDebug>

using namespace GluonInput;

int main( int argc, char* argv[] )
{
    QApplication app( argc, argv );

    if( InputManager::instance()->inputList().count() > 0 )
    {
        qDebug() << "creating generic test game loop";
        QList<InputDevice*> inputList = InputManager::instance()->inputList();
        foreach( InputDevice * input, inputList )
        input->setEnabled( true );
        GameLoop* gameLoop = new GameLoop( inputList );
        gameLoop->run();
    }

    qDebug() << "starting generic game event loop";
    app.exec();
}
