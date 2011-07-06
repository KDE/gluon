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

#include "inputdevice.h"
#include "inputdevice_p.h"

#include "absval.h"
#include "inputbuffer.h"
#include "gluondevices.h"

#include <QtGui/QKeySequence>
#include <QtCore/QDebug>

REGISTER_OBJECTTYPE( GluonInput, InputDevice )

using namespace GluonInput;

InputDevice::InputDevice( InputThread* inputThread, QObject* parent )
    : GluonCore::GluonObject( parent )
    , d( new InputDevicePrivate )
{
    d->inputBuffer = new InputBuffer();
    d->inputBuffer->setParent( this );

    if( inputThread )
    {
        d->inputThread = inputThread;
        d->inputThread->setParent( this );

        connect( inputThread, SIGNAL( buttonStateChanged( int, int ) ), SLOT( buttonStateChanged( int, int ) ), Qt::DirectConnection );
    }
}

InputDevice::InputDevice( const InputDevice& other, QObject* parent )
    : GluonObject( parent )
    , d( other.d )
{
}

InputDevice::~InputDevice()
{
    setEnabled( false );
    if( d )
    {
        if( d->inputThread )
            qDebug() << "Close the device:" << deviceName();

        delete d->inputThread;
        d->inputThread = 0;

        delete d->inputBuffer;
        d->inputBuffer = 0;
    }
}

int InputDevice::vendor() const
{
    return d->inputThread->vendor();
}

int InputDevice::product() const
{
    return d->inputThread->product();
}

int InputDevice::version() const
{
    return d->inputThread->version();
}

int InputDevice::bustype() const
{
    return d->inputThread->bustype();
}

const QString InputDevice::deviceName() const
{
    return d->inputThread->deviceName();
}

GluonInput::DeviceFlag InputDevice::deviceType() const
{
    return d->inputThread->deviceType();
}

QList<int> InputDevice::buttonCapabilities() const
{
    return d->inputThread->buttonCapabilities();
}

QList<int> InputDevice::absAxisCapabilities() const
{
    return d->inputThread->absAxisCapabilities();
}

QList<int> InputDevice::relAxisCapabilities() const
{
    return d->inputThread->relAxisCapabilities();
}

AbsVal InputDevice::axisInfo( int axisCode ) const
{
    return d->inputThread->axisInfo( axisCode );
}

bool InputDevice::error() const
{
    return d->inputThread->error();
}

QString InputDevice::msgError() const
{
    return d->inputThread->msgError();
}

bool InputDevice::isEnabled() const
{
    return d->inputThread->isEnabled();
}

void InputDevice::setEnabled( bool enable )
{
    if( !d || !d->inputThread )
        return;

    if( enable && !d->inputThread->isEnabled() )
    {
        d->inputThread->start();
    }
    else if( !enable && d->inputThread->isEnabled() )
    {
        d->inputThread->stop();
    }
}

void InputDevice::setInputThread( InputThread* inputThread )
{
    d->inputThread->stop();
    delete d->inputThread;
    d->inputThread = inputThread;
}

InputThread* InputDevice::inputThread() const
{
    return d->inputThread;
}

bool InputDevice::buttonPressed( int code ) const
{
    return d->inputBuffer->buttonState( code );
}

QString InputDevice::buttonName( int code ) const
{
    switch( deviceType() )
    {
        case KeyboardDevice:
            return QKeySequence( code ).toString();
        default:
            return "Unknown";
    }
}

QString InputDevice::axisName( int code ) const
{
    switch( deviceType() )
    {
        case MouseDevice:
        case JoystickDevice:
            return GluonButtons::instance()->axisName( deviceType(), code );
        default:
            return "Unknown";
    }
}

void InputDevice::setButtonState( int button, int value )
{
    // qDebug() << "WRITE - KEYCODE:  " << button << "PRESSED: " << value;
    d->inputBuffer->setButtonState( button, value );
}

void InputDevice::buttonStateChanged( int button, int value )
{
    d->inputBuffer->setButtonState( button, value );
}

#include "inputdevice.moc"
