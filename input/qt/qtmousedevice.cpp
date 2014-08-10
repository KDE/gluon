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
#include <QtCore/QMetaEnum>
#include <QtGui/QGuiApplication>
#include <QtGui/QMouseEvent>
#include <QtGui/QScreen>
#include <QtGui/QWindow>

#include <QtCore/QDebug>

#include <input/inputparameter.h>
#include <input/inputmanager.h>

using namespace GluonInput;

class QtMouseDevice::Private
{
    public:
        QHash< int, InputParameter* > buttons;

        InputParameter* xAxis = nullptr;
        InputParameter* yAxis = nullptr;

        InputParameter* wheelVertical = nullptr;
        InputParameter* wheelHorizontal = nullptr;
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
    QMetaEnum buttons = staticQtMetaObject.enumerator( staticQtMetaObject.indexOfEnumerator( "MouseButtons" ) );

    const int buttonCount = buttons.keyCount();
    for( int i = 0; i < buttonCount; ++i )
    {
        InputParameter* parameter = new InputParameter( InputParameter::Button, this );
        parameter->setName( QString( buttons.key( i ) ) );
        parameter->setButtonCode( buttons.value( i ) );
        d->buttons.insert( buttons.value( i ), parameter );
    }

    d->xAxis = new InputParameter( InputParameter::Axis, this );
    d->xAxis->setName( "X Axis" );

    d->yAxis = new InputParameter( InputParameter::Axis, this );
    d->yAxis->setName( "Y Axis" );

    d->wheelVertical = new InputParameter( InputParameter::Axis, this );
    d->wheelVertical->setName( "Wheel Vertical" );

    d->wheelHorizontal = new InputParameter( InputParameter::Button, this );
    d->wheelHorizontal->setName( "Wheel Horizontal" );

    setParameters( QList< InputParameter* >() << d->buttons.values() << d->xAxis << d->yAxis << d->wheelVertical << d->wheelHorizontal );

    InputManager::instance()->filterObject()->installEventFilter( this );
}

bool QtMouseDevice::eventFilter( QObject* target, QEvent* event )
{
    switch( event->type() ) {
        case QEvent::MouseButtonPress: {
            auto mevent = static_cast< QMouseEvent* >( event );
            if( d->buttons.contains( mevent->button() ) )
            {
                d->buttons.value( mevent->button() )->setButtonState( InputParameter::ButtonPressed );
                return true;
            }
            break;
        }
        case QEvent::MouseButtonRelease: {
            auto mevent = static_cast< QMouseEvent* >( event );
            if( d->buttons.contains( mevent->button() ) )
            {
                d->buttons.value( mevent->button() )->setButtonState( InputParameter::ButtonReleased );
                return true;
            }
            break;
        }
        case QEvent::MouseMove: {
            auto mevent = static_cast< QMouseEvent* >( event );
            auto pos = mevent->windowPos();
            auto windowSize = QGuiApplication::focusWindow()->size();

            d->xAxis->setAxisValue( -1.f + 2.f * ( pos.x() / windowSize.width() ) );
            d->yAxis->setAxisValue( -1.f + 2.f * ( pos.y() / windowSize.height() ) );

            return true;
        }
        case QEvent::Wheel: {
            auto wevent = static_cast< QWheelEvent* >( event );
            auto pos = wevent->angleDelta();

            if( pos.y() > 0 )
            {
                d->wheelVertical->setAxisValue( 1.0f );
                QMetaObject::invokeMethod( d->wheelVertical, "setAxisValue", Qt::QueuedConnection, Q_ARG( float, 0.f ) );
            }
            else if( pos.y() < 0 )
            {
                d->wheelVertical->setAxisValue( -1.0f );
                QMetaObject::invokeMethod( d->wheelVertical, "setAxisValue", Qt::QueuedConnection, Q_ARG( float, 0.f ) );
            }
            else if( pos.x() > 0 )
            {
                d->wheelHorizontal->setAxisValue( 1.0f );
                QMetaObject::invokeMethod( d->wheelHorizontal, "setAxisValue", Qt::QueuedConnection, Q_ARG( float, 0.f ) );
            }
            else if( pos.x() < 0 )
            {
                d->wheelHorizontal->setAxisValue( -1.0f );
                QMetaObject::invokeMethod( d->wheelHorizontal, "setAxisValue", Qt::QueuedConnection, Q_ARG( float, 0.f ) );
            }

            return true;
        }
        default:
            break;
    }

    return QObject::eventFilter(target, event);
}
