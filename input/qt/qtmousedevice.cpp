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

#include "qtmousedevice.h"

#include <QtCore/QtGlobal>
#include <QtCore/QCoreApplication>
#include <QtCore/QMetaEnum>
#include <QtGui/QMouseEvent>

#include <input/inputparameter.h>
#include <input/inputmanager.h>

using namespace GluonInput;

class QtMouseDevice::Private
{
    public:
        QHash< int, InputParameter* > buttons;

};

QtMouseDevice::QtMouseDevice( QObject* parent )
    : InputDevice( parent )
{
    setName( QStringLiteral( "Qt Mouse" ) );
}

QtMouseDevice::~QtMouseDevice()
{
}

void QtMouseDevice::initialize()
{
    InputManager::instance()->filterObject()->installEventFilter( this );
}

bool QtMouseDevice::eventFilter(QObject* target, QEvent* event)
{
//     if( event->type() == QEvent::KeyPress )
//     {
//         QKeyEvent* kevent = static_cast< QKeyEvent* >( event );
//         if( d->parameters.contains( kevent->key() ) )
//         {
//             d->parameters.value( kevent->key() )->setButtonState( ButtonPressed );
//         }
//     }
//     else if( event->type() == QEvent::KeyRelease )
//     {
//         QKeyEvent* kevent = static_cast< QKeyEvent* >( event );
//         if( d->parameters.contains( kevent->key() ) )
//         {
//             d->parameters.value( kevent->key() )->setButtonState( ButtonReleased );
//         }
//     }

    return QObject::eventFilter(target, event);
}
