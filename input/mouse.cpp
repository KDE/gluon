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

#include "mouse.h"
#include "mouse_p.h"

REGISTER_OBJECTTYPE( GluonInput, Mouse )

using namespace GluonInput;

Mouse::Mouse( InputThread* inputThread, QObject* parent )
    : InputDevice( inputThread, parent )
    , d( new MousePrivate )
{
    d->originalPosition = d->position = QPoint( 0, 0 );
    d->sensibility = 1;

    if( inputThread )
        connect( inputThread, SIGNAL(relAxisMoved(int,int)), SLOT(mouseMoved(int,int)), Qt::DirectConnection );
}

Mouse::Mouse( const Mouse& other, InputThread* inputThread, QObject* parent )
    : InputDevice( inputThread, parent )
    , d( other.d )
{
}

Mouse::~Mouse()
{
}

QPoint Mouse::position()
{
    return d->position;
}

void  Mouse::setPosition( const QPoint& p )
{
    d->position = p;
}

void Mouse::setSensibility( double s )
{
    d->sensibility = s;
}

void Mouse::setOrigin( const QPoint p )
{
    d->originalPosition = p;
}

int Mouse::wheelPosition() const
{
    return d->wheelPos; //relAxisValue(lastRelAxis());
}

void Mouse::setWheelPosition( int wp )
{
    d->wheelPos = wp;
}

int Mouse::hWheelPosition() const
{
    return d->hWheelPos; //relAxisValue(lastRelAxis());
}

void Mouse::setHWheelPosition( int hwp )
{
    d->hWheelPos = hwp;
}

double Mouse::sensibility() const
{
    return d->sensibility;
}

void Mouse::mouseMoved( int axis, int distance )
{
    switch( axis )
    {
        case GluonButtons::X_REL:
            d->position.setX( d->position.x() + distance );
            break;

        case GluonButtons::Y_REL:
            d->position.setY( d->position.y() - distance );
            break;
        case GluonButtons::HWHEEL:
            d->hWheelPos = distance;
            break;
        case GluonButtons::WHEEL_REL:
            d->wheelPos = distance;
            break;
    }
}

 
