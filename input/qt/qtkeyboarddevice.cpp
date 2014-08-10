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

#include "qtkeyboarddevice.h"

#include <QtCore/QtGlobal>
#include <QtCore/QCoreApplication>
#include <QtCore/QMetaEnum>
#include <QtGui/QKeyEvent>

#include <core/debughelper.h>

#include <input/inputparameter.h>
#include <input/inputmanager.h>

using namespace GluonInput;

class QtKeyboardDevice::Private
{
    public:
        QHash< int, InputParameter* > parameters;
};

QtKeyboardDevice::QtKeyboardDevice( QObject* parent )
    : InputDevice( parent )
{
    setName( QStringLiteral( "Qt Keyboard" ) );
}

QtKeyboardDevice::~QtKeyboardDevice()
{
}

void QtKeyboardDevice::initialize()
{
    QMetaEnum keys = staticQtMetaObject.enumerator( staticQtMetaObject.indexOfEnumerator( "Key" ) );

    const int keyCount = keys.keyCount();
    for( int i = 0; i < keyCount; ++i )
    {
        InputParameter* parameter = new InputParameter( InputParameter::Button, this );
        parameter->setName( QString( keys.key( i ) ).remove( "Key_" ) );
        parameter->setButtonCode( keys.value( i ) );
        d->parameters.insert( keys.value( i ), parameter );
    }

    setParameters( d->parameters.values() );

    InputManager::instance()->filterObject()->installEventFilter( this );
}

InputParameter* QtKeyboardDevice::parameter(int id) const
{
    if( d->parameters.contains( id ) )
        return d->parameters.value( id );

    return nullptr;
}

bool QtKeyboardDevice::eventFilter(QObject* target, QEvent* event)
{
    if( event->type() == QEvent::KeyPress )
    {
        QKeyEvent* kevent = static_cast< QKeyEvent* >( event );
        if( d->parameters.contains( kevent->key() ) )
        {
            d->parameters.value( kevent->key() )->setButtonState( InputParameter::ButtonPressed );
            return true;
        }
    }
    else if( event->type() == QEvent::KeyRelease )
    {
        QKeyEvent* kevent = static_cast< QKeyEvent* >( event );
        if( d->parameters.contains( kevent->key() ) )
        {
            d->parameters.value( kevent->key() )->setButtonState( InputParameter::ButtonReleased );
            return true;
        }
    }

    return QObject::eventFilter(target, event);
}
