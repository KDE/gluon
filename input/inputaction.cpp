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

using namespace GluonInput;

class InputAction::Private
{
    public:
        Private() { }

        InputDevice* device;
        InputParameter* parameter;
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
        d->parameter = parameter;
        emit parameterChanged();
    }
}
