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
\
#include "gluonbuttons.h"

#include <QtCore/QMetaEnum>

using namespace GluonInput;

GLUON_DEFINE_SINGLETON(GluonButtons)

GluonButtons::GluonButtons()
{
}

GluonButtons::~GluonButtons()
{
}

QString GluonButtons::buttonName( DeviceFlag deviceType, int code )
{
    QString value = "";
    switch( deviceType )
    {
        case KeyboardDevice:
            value = metaObject()->enumerator( this->metaObject()->indexOfEnumerator( "KeyboardButton" ) ).valueToKey( code );
            return value != "" ? value : "Reserved";
            break;
        case MouseDevice:
            value = metaObject()->enumerator( this->metaObject()->indexOfEnumerator( "MouseButton" ) ).valueToKey( code );
            return value != "" ? value : "Unknown";
            break;
        case JoystickDevice:
            value = metaObject()->enumerator( this->metaObject()->indexOfEnumerator( "JoystickButton" ) ).valueToKey( code );
            return value != "" ? value : "Unknown";
            break;
        default:
            return "Unknown";
    }
}

QString GluonButtons::axisName( DeviceFlag deviceType, int code )
{
    QString value = "";
    switch( deviceType )
    {
        case MouseDevice:
            value = metaObject()->enumerator( metaObject()->indexOfEnumerator( "RelAbs" ) ).valueToKey( code );
            return value != "" ? value : "Unknown";
            break;
        case JoystickDevice:
            value = metaObject()->enumerator( metaObject()->indexOfEnumerator( "RelAbs" ) ).valueToKey( code );
            return value != "" ? value : "Unknown";
            break;
        default:
            return "Unknown";
    }
}

#include "gluonbuttons.moc"
