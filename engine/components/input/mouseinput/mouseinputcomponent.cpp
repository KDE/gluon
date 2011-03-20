/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2010 Laszlo Papp <djszapi@archlinux.us>
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
#include <core/debughelper.h>

#include <QtCore/QEvent>
#include <QtCore/QDebug>

REGISTER_OBJECTTYPE( GluonEngine, MouseInputComponent );

using namespace GluonEngine;

class MouseInputComponent::MouseInputComponentPrivate
{
    public:
        MouseInputComponentPrivate()
            : actionHeld( false )
            , actionStarted( false )
            , actionStopped( false )
            , mouseButton( GluonInput::Mouse::MOUSE_BUTTON_UNKNOWN )
            , mouse( 0 )
            , lastX( 0 )
            , lastY( 0 )
            , lastZ( 0 )
        {
        }

        ~MouseInputComponentPrivate()
        {
        }

        bool actionHeld;
        bool actionStarted;
        bool actionStopped;

        GluonInput::Mouse::MouseButton mouseButton;

        GluonInput::Mouse* mouse;

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
        d->mouse = GluonInput::InputManager::instance()->mouse();
    }
}

void
MouseInputComponent::start()
{
    if( d->mouse )
    {
        d->mouse->setEnabled( true );
    }
    else
    {
        debug( "WARNING! No mouse found!" );
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
    if( d->mouse && d->mouseButton && d->mouse->buttonPressed( d->mouseButton + d->mouseButtonOffset ) )
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

    d->relX = d->mouse->position().x() - d->lastX;
    d->relY = d->mouse->position().y() - d->lastY;
    d->relZ = d->mouse->wheelPosition() - d->lastZ;

    d->lastX = d->mouse->position().x();
    d->lastY = d->mouse->position().y();
    d->lastZ = d->mouse->wheelPosition();
}

void MouseInputComponent::stop()
{
    if( d->mouse )
    {
        d->mouse->setEnabled( false );
    }

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

GluonInput::Mouse::MouseButton MouseInputComponent::mouseButton() const
{
    return d->mouseButton;
}

void MouseInputComponent::setMouseButton( GluonInput::Mouse::MouseButton button )
{
    d->mouseButton = button;
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
    return d->mouse->position().x();
}

int MouseInputComponent::yAxis()
{
    return d->mouse->position().y();
}

int MouseInputComponent::zAxis()
{
    return d->mouse->wheelPosition();
}

float MouseInputComponent::normalizedXAxis()
{
    QWidget* filter = qobject_cast<QWidget*>(GluonInput::InputManager::instance()->filteredObject());
    if(filter)
    {
        return (d->mouse->position().x() / float(filter->width())) * 2.f -1.f;
    }
    return 0.f;
}

float MouseInputComponent::normalizedYAxis()
{
    QWidget* filter = qobject_cast<QWidget*>(GluonInput::InputManager::instance()->filteredObject());
    if(filter)
    {
        return (d->mouse->position().y() / float(filter->height())) * 2.f - 1.f;
    }
    return 0.f;
}

Q_EXPORT_PLUGIN2( gluon_component_mouseinput, GluonEngine::MouseInputComponent );

#include "mouseinputcomponent.moc"
