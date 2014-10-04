/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2010 Laszlo Papp <lpapp@kde.org>
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

#include "mouseinputcomponent.h"

#include <input/inputmanager.h>
#include <input/inputdevice.h>
#include <input/inputparameter.h>
#include <core/log.h>

REGISTER_OBJECTTYPE( GluonEngine, MouseInputComponent );

using namespace GluonEngine;

class MouseInputComponent::MouseInputComponentPrivate
{
    public:
        MouseInputComponentPrivate()
            : actionHeld( false )
            , actionStarted( false )
            , actionStopped( false )
            , buttonCode( Qt::NoButton )
            , mouse( 0 )
            , mouseButton( 0 )
            , xAxis( 0 )
            , yAxis( 0 )
            , lastX( 0 )
            , lastY( 0 )
            , lastZ( 0 )
            , mouseTrack( false )
        {
        }

        ~MouseInputComponentPrivate()
        {
        }

        bool actionHeld;
        bool actionStarted;
        bool actionStopped;

        Qt::MouseButton buttonCode;

        GluonInput::InputDevice* mouse;
        GluonInput::InputParameter* mouseButton;
        GluonInput::InputParameter* xAxis;
        GluonInput::InputParameter* yAxis;
        GluonInput::InputParameter* wheel;

        int lastX;
        int lastY;
        int lastZ;

        int relX;
        int relY;
        int relZ;

        bool mouseTrack;

        static const int mouseButtonOffset;
};

const int MouseInputComponent::MouseInputComponentPrivate::mouseButtonOffset = 271;

MouseInputComponent::MouseInputComponent( QObject* parent )
    : Component( parent )
    , d( new MouseInputComponentPrivate )
{
}

MouseInputComponent::~MouseInputComponent()
{
    delete d;
}

QString
MouseInputComponent::category() const
{
    return QString( "Input" );
}

void MouseInputComponent::initialize()
{
    if( !d->mouse )
    {
        GluonInput::InputManager::instance()->initialize();
        d->mouse = GluonInput::InputManager::instance()->device( "qt_mouse" );
        if( !d->mouse )
        {
            ERROR() << "Could not find qt_mouse";
            return;
        }
        if( d->buttonCode != Qt::NoButton )
        {
            d->mouseButton = d->mouse->parameter( d->buttonCode );
        }
        d->xAxis = d->mouse->parameter( "X Axis" );
        d->yAxis = d->mouse->parameter( "Y Axis" );
        d->wheel = d->mouse->parameter( "Wheel Vertical" );
    }
}

void
MouseInputComponent::update( int elapsedMilliseconds )
{
    DEBUG_BLOCK
    if( d->actionStarted )
        d->actionStarted = false;

    if( d->actionStopped )
        d->actionStopped = false;

    // qDebug() << "READ - KEYCODE - OFFSET:  " << d->mouseButton << d->mouseButtonOffset << "PRESSED: " << d->mouse->buttonPressed( d->mouseButton + d->mouseButtonOffset );
    if( d->mouseButton && d->mouseButton->buttonState() == GluonInput::InputParameter::ButtonPressed )
    {
        if( !d->actionHeld )
        {
            d->actionStarted = true;
            d->actionHeld = true;
        }
    }
    else
    {
        if( d->actionHeld )
        {
            d->actionStopped = true;
            d->actionHeld = false;
        }
    }

    d->relX = d->xAxis->axisValue() - d->lastX;
    d->relY = d->yAxis->axisValue() - d->lastY;
    d->relZ = d->wheel->axisValue() - d->lastZ;

    d->lastX = d->xAxis->axisValue();
    d->lastY = d->yAxis->axisValue();
    d->lastZ = d->wheel->axisValue();
}

void MouseInputComponent::stop()
{
    d->actionStopped = false;
    d->actionStarted = false;
    d->actionHeld = false;
}

bool
MouseInputComponent::isActionStarted()
{
    return d->actionStarted;
}

bool
MouseInputComponent::isActionHeld()
{
    return d->actionHeld;
}

bool
MouseInputComponent::isActionStopped()
{
    return d->actionStopped;
}

Qt::MouseButton MouseInputComponent::mouseButton() const
{
    return d->buttonCode;
}

void MouseInputComponent::setMouseButton( Qt::MouseButton button )
{
    d->buttonCode = button;
}

bool MouseInputComponent::mouseTrack() const
{
    return d->mouseTrack;
}

void MouseInputComponent::setMouseTrack( bool enable )
{
    d->mouseTrack = enable;
}

int MouseInputComponent::relativeXAxis()
{
    return d->relX;
}

int MouseInputComponent::relativeYAxis()
{
    return d->relY;
}

int MouseInputComponent::relativeZAxis()
{
    return d->relZ;
}

int MouseInputComponent::xAxis()
{
    return d->xAxis->axisValue();
}

int MouseInputComponent::yAxis()
{
    return d->yAxis->axisValue();
}

int MouseInputComponent::zAxis()
{
    return d->wheel->axisValue();
}

// float MouseInputComponent::normalizedXAxis()
// {
//     QWidget* filter = qobject_cast<QWidget*>( GluonInput::InputManager::instance()->filteredObject() );
//     if( filter )
//     {
//         return ( d->mouse->position().x() / float( filter->width() ) ) * 2.f - 1.f;
//     }
//     return 0.f;
// }
// 
// float MouseInputComponent::normalizedYAxis()
// {
//     QWidget* filter = qobject_cast<QWidget*>( GluonInput::InputManager::instance()->filteredObject() );
//     if( filter )
//     {
//         return ( d->mouse->position().y() / float( filter->height() ) ) * 2.f - 1.f;
//     }
//     return 0.f;
// }

 
