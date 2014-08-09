/*
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2014 Arjen Hiemstra <ahiemstra@heimr.nl>
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
 *
 */

#include <QtGui/QGuiApplication>
#include <QtGui/QWindow>

#include <input/inputmanager.h>
#include <input/inputdevice.h>
#include <input/inputparameter.h>
#include <input/enums.h>

using namespace GluonInput;

int main( int argc, char** argv )
{
    QGuiApplication app( argc, argv );

    InputManager::instance()->initialize();

    InputDevice* keyboard = InputManager::instance()->device( "qt_keyboard" );

    if( !keyboard )
        qFatal( "No keyboard found!" );

    InputParameter* parameter = keyboard->parameter( Qt::Key_Return );

    if( !parameter )
        qFatal( "No return key found!" );

    QObject::connect( parameter, &InputParameter::buttonStateChanged, [parameter]() {
        if( parameter->buttonState() == GluonInput::ButtonPressed ) qDebug( "Hello World!" );
    } );

    QWindow win;
    win.show();
    app.exec();
}
