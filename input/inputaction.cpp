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

#include "inputaction.h"
#include "inputparameter.h"

using namespace GluonInput;

class InputAction::Private
{
    public:
        InputDevice* device = nullptr;
        InputParameter* parameter = nullptr;

        bool pressed = false;
};

InputAction::InputAction(QObject* parent)
    : QObject( parent )
{
}

InputAction::~InputAction()
{
}

InputDevice* InputAction::device() const
{
    return d->device;
}

InputParameter* InputAction::parameter() const
{
    return d->parameter;
}

float InputAction::value() const
{
    if( d->parameter && d->parameter->hasAxisValue() )
        return d->parameter->axisValue();

    return qQNaN();
}

bool InputAction::isPressed() const
{
    return d->pressed;
}

void InputAction::setDevice( InputDevice* device )
{
    if( device != d->device )
    {
        d->device = device;
        emit deviceChanged();
    }
}

void InputAction::setParameter( InputParameter* parameter )
{
    if( parameter != d->parameter )
    {
        if( d->parameter )
            d->parameter->disconnect( this );

        d->parameter = parameter;

        connect( d->parameter, &InputParameter::axisValueChanged, this, &InputAction::axisValueChanged );
        connect( d->parameter, &InputParameter::buttonStateChanged, this, &InputAction::buttonStateChanged );

        emit parameterChanged();
    }
}

void InputAction::axisValueChanged()
{
    emit valueChanged();
}

void InputAction::buttonStateChanged()
{
    if( d->parameter->buttonState() == InputParameter::ButtonPressed )
    {
        d->pressed = true;
        emit pressed();
    }
    else
    {
        if( d->pressed )
            emit triggered();

        d->pressed = false;
        emit released();
    }
}
