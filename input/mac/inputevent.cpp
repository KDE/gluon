/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Kim Jung Nissen <jungnissen@gmail.com>
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
#include "inputevent.h"
#include "inputeventprivate.h"

namespace GluonInput
{
    InputEvent::InputEvent(int code, int value, QEvent::Type eventType)
            : QEvent(eventType)
    {
        d = new InputEventPrivate();
        d->m_code = code;
        d->m_value = value;
    }

    int InputEvent::code() const
    {
        return d->m_code;
    }

    int InputEvent::value() const
    {
        return d->m_value;
    }
}
