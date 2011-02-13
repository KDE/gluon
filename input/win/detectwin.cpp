/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2010 Kim Jung Nissen <jungnissen@gmail.com>
 * Copyright (C) 2010 Laszlo Papp <djszapi@archlinux.us>
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

#include "detectwin.h"

#include "inputthread.h"

#include <QtGui/QMessageBox>
#include <QtCore/QDir>
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>

using namespace GluonInput;

class DetectWin::DetectWinPrivate
{
    public:
        QList<InputDevice*> inputList;
        QList<Keyboard*> keyboardList;
        QList<Mouse*> mouseList;
        QList<Joystick*> joystickList;
        QList<Touch*> touchList;
        QList<InputDevice*> unknownList;
};

DetectWin::DetectWin( QObject* parent )
    : Detect( parent )
    , d( new DetectWinPrivate )
{
}

DetectWin::~DetectWin()
{
}

bool DetectWin::isReadable()
{
    return false;
}

void DetectWin::detectDevices()
{
}

void DetectWin::setAllEnabled( bool enable )
{
    foreach( InputDevice * input, inputList() )
    {
        input->setEnabled( enable );
    }
}

void DetectWin::clear()
{
    d->inputList.clear();
    d->keyboardList.clear();
    d->mouseList.clear();
    d->joystickList.clear();
    d->touchList.clear();
    d->unknownList.clear();
}

void DetectWin::addInput( InputDevice* i )
{
    d->inputList.append( i );
}

void DetectWin::addKeyboard( Keyboard* keybd )
{
    d->keyboardList.append( keybd );
}

void DetectWin::addMouse( Mouse* mouse )
{
    d->mouseList.append( mouse );
}

void DetectWin::addJoystick( Joystick* joystick )
{
    d->joystickList.append( joystick );
}

void DetectWin::addTouch( Touch* touch )
{
    d->touchList.append( touch );
}

void DetectWin::addUnknown( InputDevice* i )
{
    d->unknownList.append( i );
}

QList<InputDevice*> DetectWin::inputList()
{
    return d->inputList;
}

QList<Keyboard*> DetectWin::keyboardList()
{
    return d->keyboardList;
}

QList<Mouse*> DetectWin::mouseList()
{
    return d->mouseList;
}

QList<Joystick*> DetectWin::joystickList()
{
    return d->joystickList;
}

QList<Touch*> DetectWin::touchList()
{
    return d->touchList;
}

QList<InputDevice*> DetectWin::unknownDeviceList()
{
    return d->unknownList;
}
