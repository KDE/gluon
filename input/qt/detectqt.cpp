/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Laszlo Papp <djszapi@archlinux.us>
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

#include "detectqt.h"

#include "detectqtprivate.h"

#include <QtGui/QMessageBox>
#include <QtCore/QDir>
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>

using namespace GluonInput;

DetectQt::DetectQt( QObject* parent )
    : Detect( parent )
    , d( new DetectQtPrivate )
{
}

DetectQt::~DetectQt()
{
}

bool DetectQt::isReadable()
{
    return false;
}

void DetectQt::setAllEnabled( bool enable )
{
}

void DetectQt::detectDevices()
{
}

void DetectQt::clear()
{
    d->inputList.clear();
    d->keyboardList.clear();
    d->mouseList.clear();
    d->joystickList.clear();
    d->touchList.clear();
    d->unknownList.clear();
}

void DetectQt::addInput( InputDevice* i )
{
    d->inputList.append( i );
}

void DetectQt::addKeyboard( Keyboard* keyboard )
{
    d->keyboardList.append( keyboard );
}

void DetectQt::addMouse( Mouse* mouse )
{
    d->mouseList.append( mouse );
}

void DetectQt::addJoystick( Joystick* joystick )
{
    d->joystickList.append( joystick );
}

void DetectQt::addTouch( Touch* touch )
{
    d->touchList.append( touch );
}

void DetectQt::addUnknown( InputDevice* i )
{
    d->unknownList.append( i );
}

QList<InputDevice*> DetectQt::inputList()
{
    return d->inputList;
}

QList<Keyboard*> DetectQt::keyboardList()
{
    return d->keyboardList;
}

QList<Mouse*> DetectQt::mouseList()
{
    return d->mouseList;
}

QList<Joystick*> DetectQt::joystickList()
{
    return d->joystickList;
}

QList<Touch*> DetectQt::touchList()
{
    return d->touchList;
}

QList<InputDevice*> DetectQt::unknownDeviceList()
{
    return d->unknownList;
}

#include "detectqt.moc"
