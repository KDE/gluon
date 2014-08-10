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

#include "inputparameter.h"

using namespace GluonInput;

class InputParameter::Private
{
    public:
        ParameterType type;
        QString name;
        ButtonState buttonState = ButtonUnknown;
        int buttonCode = -1;
        float axisValue = 0.f;
};

InputParameter::InputParameter( InputParameter::ParameterType type, QObject* parent )
    : QObject( parent )
{
    d->type = type;
}

InputParameter::~InputParameter()
{
}

QString InputParameter::name() const
{
    return d->name;
}

bool InputParameter::hasButtonState() const
{
    return d->type == Button;
}

InputParameter::ButtonState InputParameter::buttonState() const
{
    return d->buttonState;
}

int InputParameter::buttonCode() const
{
    return d->buttonCode;
}

bool InputParameter::hasAxisValue() const
{
    return d->type == Axis;
}

float InputParameter::axisValue() const
{
    return d->axisValue;
}

void InputParameter::setName( const QString& name )
{
    if( name != d->name )
    {
        d->name = name;
        emit nameChanged();
    }
}

void InputParameter::setButtonState( ButtonState state )
{
    if( state != d->buttonState )
    {
        d->buttonState = state;
        emit buttonStateChanged();
    }
}

void InputParameter::setButtonCode( int code )
{
    if( code != d->buttonCode )
    {
        d->buttonCode = code;
        emit buttonCodeChanged();
    }
}

void InputParameter::setAxisValue( float value )
{
    if( !qFuzzyCompare( value, d->axisValue ) )
    {
        d->axisValue = value;
        emit axisValueChanged();
    }
}
