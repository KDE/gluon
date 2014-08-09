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

#ifndef GLUONINPUT_QTKEYBOARDDEVICE_H
#define GLUONINPUT_QTKEYBOARDDEVICE_H

#include <core/privatepointer.h>
#include <input/inputdevice.h>

namespace GluonInput
{
    class QtKeyboardDevice : public GluonInput::InputDevice
    {
        Q_OBJECT

        public:
            explicit QtKeyboardDevice( QObject* parent = 0 );
            ~QtKeyboardDevice();

            virtual void initialize() override;
            virtual InputParameter* parameter(int id) const override;

            bool eventFilter( QObject* target, QEvent* event ) override;

        GLUON_PRIVATE_POINTER;
    };
}

#endif // GLUONINPUT_QTKEYBOARDDEVICE_H
