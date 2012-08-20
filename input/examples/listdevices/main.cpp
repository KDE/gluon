/*
 * This file is part of the KGLEngine2D project.
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 * Copyright (C) 2010 Laszlo Papp <lpapp@kde.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "input/inputmanager.h"
#include "input/inputdevice.h"

#include <QtCore/QDebug>

int main( int argc, char* argv[] )
{
    qDebug() << "Number of devices available : "         << GluonInput::InputManager::instance()->deviceCount();
    qDebug() << "Number of keyboards available : "       << GluonInput::InputManager::instance()->keyboardCount();
    qDebug() << "Number of mice available : "          << GluonInput::InputManager::instance()->mouseCount();
    qDebug() << "Number of joysticks available : "       << GluonInput::InputManager::instance()->joystickCount();
    qDebug() << "Number of touches available : "         << GluonInput::InputManager::instance()->touchCount();
    qDebug() << "Number of unknown devices available : "  << GluonInput::InputManager::instance()->unknownDeviceCount();

    foreach( GluonInput::InputDevice * input, GluonInput::InputManager::instance()->inputList() )
    {
        qDebug() << input->deviceName();

        switch( input->deviceType() )
        {
            case GluonInput::KeyboardDevice:
                qDebug() << "this is a keyboard";
                break;
            case GluonInput::MouseDevice:
                qDebug() << "this is a mouse";
                break;
            case GluonInput::JoystickDevice:
                qDebug() << "this is a joystick";
                break;
            case GluonInput::TouchDevice:
                qDebug() << "this is a touch";
                break;
            case GluonInput::UnknownDevice:
                qDebug() << "this is an unknown device";
                break;
            default:
                break;
        }

        // Now we can show the capability of inputs...This example show the buttons capabilities
        foreach( int buttonCode, input->buttonCapabilities() )
        qDebug() << "BUTTON : " << buttonCode << "->" << input->buttonName( buttonCode );

        foreach( int axis, input->absAxisCapabilities() )
        qDebug() << "ABSOLUTE AXIS " << axis << "->" << input->axisName( axis );

        foreach( int axis, input->relAxisCapabilities() )
        qDebug() << "RELATIVE AXIS " << axis << "->" << input->axisName( axis );

        qDebug() << "===========================================================";
    }
}
