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
#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "core/singleton.h"
#include "gluon_input_export.h"

#include "inputdevice.h"
#include "mouse.h"
#include "keyboard.h"
#include "joystick.h"
#include "touch.h"

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QSharedData>

namespace GluonInput
{
    typedef QList<InputDevice *> InputList;
    class InputManagerPrivate;

    class GLUON_INPUT_EXPORT InputManager : public GluonCore::Singleton<InputManager>
    {
        Q_OBJECT

        public:
            InputManager();
            void detectDevices();
            void setAllEnabled(bool enable);

            unsigned int deviceCount();
            unsigned int keyboardCount();
            unsigned int mouseCount();
            unsigned int joystickCount();
            unsigned int touchCount();
            unsigned int unknownDeviceCount();

            QList<Keyboard *> keyboardList();
            QList<Mouse *> mouseList();
            QList<Joystick *> joystickList();
            QList<Touch *> touchList();
            QList <InputDevice *> unknownDeviceList();

            InputList inputList();

            Keyboard *keyboard(int id = 0);
            Mouse *mouse(int id = 0);
            Joystick *joystick(int id = 0);
            Touch *touch(int id = 0);
            InputDevice *input(int id = 0);

        private:
            ~InputManager();
            void init();

            QSharedDataPointer<InputManagerPrivate> d;
    };
}

#endif
