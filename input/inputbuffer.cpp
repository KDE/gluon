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

#include "inputbuffer.h"

#include"inputbuffer_p.h"

using namespace GluonInput;

InputBuffer::InputBuffer()
    : d( new InputBufferPrivate )
{
}

InputBuffer::~InputBuffer()
{
}

bool InputBuffer::buttonState( int button )
{
    if( d->buttonState[button].isEmpty() )
        return false;

    bool returnBool = false;
    if( d->buttonState[button].count() > 1 )
    {
        returnBool = d->buttonState[button].dequeue();
        d->buttonState[button].clear();
    }
    else
    {
        returnBool = d->buttonState[button].head();
    }

    return returnBool;
}

void InputBuffer::setButtonState( int button, bool pressed )
{
    if( pressed && d->buttonState[button].isEmpty() )
    {
        d->buttonState[button].enqueue( pressed );
    }
    else if( !pressed && d->buttonState[button].count() == 1 )
    {
        d->buttonState[button].enqueue( pressed );
    }
}
