/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Laszlo Papp <lpapp@kde.org>
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
#include "gluonqtbuttons.h"

#include <QtCore/QMetaEnum>

using namespace GluonInput;

GLUON_DEFINE_SINGLETON( GluonQtButtons )

GluonQtButtons::GluonQtButtons( QObject* parent )
    : GluonCore::Singleton< GluonInput::GluonQtButtons >( parent )
{
}

GluonQtButtons::~GluonQtButtons()
{
}

QString GluonQtButtons::buttonName( DeviceQtFlag deviceType, int code )
{
    return metaObject()->enumerator( metaObject()->indexOfEnumerator( "Qt::Key" ) ).valueToKey( code );
}

QString GluonQtButtons::axisName( DeviceQtFlag deviceType, int code )
{
    QString value = "";
    switch( deviceType )
    {
        case MouseDevice:
            value = metaObject()->enumerator( metaObject()->indexOfEnumerator( "Relative" ) ).valueToKey( code );
            value != "" ? value : "Unknown";
            break;
        case JoystickDevice:
            value = metaObject()->enumerator( metaObject()->indexOfEnumerator( "Absolute" ) ).valueToKey( code );
            value != "" ? value : "Unknown";
            break;
        default:
            value = "Unknown";
            break;
    }
    return value;
}

#include "gluonqtbuttons.moc"
