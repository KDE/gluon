/*
* This file is part of the KGLEngine2D project.
* Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
* Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
* Copyright (C) 2008 Charles Huet <packadal@gmail.com>
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

#include <QDebug>

#include <gluon/input/code.h>
#include <gluon/input/detect.h>

using namespace std;

int main(int argc, char *argv[])
{
	qDebug()<<"Number of devices available : "         << GluonInput::Detect::deviceCount();
	qDebug()<<"Number of keyboards available : "       << GluonInput::Detect::keyboardCount();
	qDebug()<<"Number of mice available : "          << GluonInput::Detect::mouseCount();
	qDebug()<<"Number of joysticks available : "       << GluonInput::Detect::joystickCount();
	qDebug()<<"Number of tablets available : "         << GluonInput::Detect::tabletCount();
	qDebug()<<"Number of unknown devices available : "  << GluonInput::Detect::unknownDeviceCount();

	foreach(GluonInput::InputDevice * input, GluonInput::Detect::inputList())
	{
        qDebug() << input->deviceName();

        switch ( input->deviceType())
        {
            case GluonInput::KeyBoardDevice : qDebug()<<"this is a keyboard"; break;
            case GluonInput::MouseDevice : qDebug()<<"this is a mouse"; break;
            case GluonInput::JoystickDevice : qDebug()<<"this is a joystick"; break;
            case GluonInput::TabletDevice : qDebug()<<"this is a tablet"; break;
            case GluonInput::UnknownDevice: qDebug()<<"this is an unknown device"; break;
            default:break;
        }
        // Now we can show the capability of inputs...This example show the buttons capabilities
        foreach (int buttonCode, input->buttonCapabilities())
        qDebug()<<"BUTTON : "<<buttonCode<<"->"<< GluonInput::Code::buttonName(buttonCode);

        foreach (int axis, input->absAxisCapabilities())
        qDebug()<<"ABSOLUTE AXIS "<<axis<<"->"<< GluonInput::Code::absAxisName(axis);

        foreach (int axis, input->relAxisCapabilities())
        qDebug()<<"RELATIF AXIS" <<axis<<"->"<< GluonInput::Code::relAxisName(axis);



        qDebug()<<"===========================================================";

    }

}
