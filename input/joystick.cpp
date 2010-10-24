/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Kim Jung Nissen <jungnissen@gmail.com>
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

#include "joystick.h"
#include "joystickprivate.h"

using namespace GluonInput;

Joystick::Joystick(InputThread *inputThread, QObject *parent)
    : InputDevice(inputThread, parent)
    , d(new JoystickPrivate)
{
    connect(inputThread, SIGNAL(absAxisMoved(int, int)), SLOT(joystickMoved(int, int)), Qt::DirectConnection);
}

int Joystick::axisX() const
{
#ifdef __GNUC__
#warning fix the joystick thing, when I have a joystick to test with
#endif
    return -1;
}

int Joystick::axisY() const
{
    //	return absAxisValue(this->inputThread()->getJoystickYAxis());
    return -1;
}

int Joystick::axisZ() const
{
    //	return absAxisValue(this->inputThread()->getJoystickZAxis());
    return -1;
}

void Joystick::joystickMoved(int axis, int distance)
{
}

#include "joystick.moc"
