/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2010 Kim Jung Nissen <jungnissen@gmail.com>
 * Copyright (C) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "inputthread.h"
#include "absval.h"

#include <QtCore/QMap>

using namespace GluonInput;

class InputThread::InputThreadPrivate
{
    public:
        int vendor;
        int product;
        int version;
        int bustype;

        QString deviceName;
        QString msgError;

        bool error;

        GluonInput::DeviceFlag deviceType;

        QList<int> buttonCapabilities;
        QList<int> relAxisCapabilities;
        QList<int> absAxisCapabilities;
        QMap<int, AbsVal> absAxisInfos;
};

InputThread::InputThread( const QString& devicePath, QObject* parent )
    : QThread( parent )
    , d( new InputThreadPrivate )
{
}

InputThread::~InputThread()
{
}

void InputThread::run()
{
}

int InputThread::joystickXAxis()
{
    return 0;
}

int InputThread::joystickYAxis()
{
    return 0;
}

int InputThread::joystickZAxis()
{
    return 0;
}

void InputThread::stop()
{
    quit();
}

int InputThread::vendor() const
{
    return d->vendor;
}

int InputThread::product() const
{
    return d->product;
}

int InputThread::version() const
{
    return d->version;
}

int InputThread::bustype() const
{
    return d->bustype;
}

QList<int> InputThread::buttonCapabilities() const
{
    return d->buttonCapabilities;
}

QList<int> InputThread::absAxisCapabilities() const
{
    return d->absAxisCapabilities;
}

QList<int> InputThread::relAxisCapabilities() const
{
    return d->relAxisCapabilities;
}

AbsVal InputThread::axisInfo( int axisCode ) const
{
    return d->absAxisInfos[axisCode];
}

const QString InputThread::deviceName() const
{
    return d->deviceName;
}

GluonInput::DeviceFlag InputThread::deviceType() const
{
    return d->deviceType;
}

bool InputThread::isEnabled() const
{
    return this->isRunning();
}

bool InputThread::error()
{
    return d->error;
}

QString InputThread::msgError()
{
    return d->msgError;
}
