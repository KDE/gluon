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

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "inputdevice.h"

#include <QtCore/QSharedDataPointer>

namespace GluonInput
{
    class KeyboardPrivate;
    class InputThread;

    class GLUON_INPUT_EXPORT Keyboard : public InputDevice
    {
            Q_OBJECT
        public:
            explicit Keyboard( InputThread* inputThread, QObject* parent = 0 );
            Keyboard( const Keyboard& other, InputThread* inputThread = 0, QObject* parent = 0 );
            virtual ~Keyboard();

        private:
            QSharedDataPointer<KeyboardPrivate> d;
    };
}

#endif // KEYBOARD_H
