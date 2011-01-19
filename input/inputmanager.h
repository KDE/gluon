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

#include "gluon_input_export.h"

#include "inputdevice.h"
#include "mouse.h"
#include "keyboard.h"
#include "joystick.h"
#include "touch.h"

#include <core/singleton.h>

#include <QtCore/QObject>
#include <QtCore/QList>

namespace GluonInput
{
    typedef QList<InputDevice*> InputList;
    class InputManagerPrivate;

    class GLUON_INPUT_EXPORT InputManager : public GluonCore::Singleton<InputManager>
    {
            Q_OBJECT

        public:

            enum KeyboardManagementType
            {
                WINDOWS_KB_LOWLEVEL,
                MACOSX_KB_LOWLEVEL,
                LINUX_KB_LOWLEVEL,
                QT_HIGHLEVEL,
            };

            void detectDevices();
            void setAllEnabled( bool enable );

            unsigned int deviceCount();
            unsigned int keyboardCount();
            unsigned int mouseCount();
            unsigned int joystickCount();
            unsigned int touchCount();
            unsigned int unknownDeviceCount();

            QList<Keyboard*> keyboardList();
            QList<Mouse*> mouseList();
            QList<Joystick*> joystickList();
            QList<Touch*> touchList();
            QList<InputDevice*> unknownDeviceList();

            InputList inputList();

            Keyboard* keyboard( int id = 0 );
            Mouse* mouse( int id = 0 );
            Joystick* joystick( int id = 0 );
            Touch* touch( int id = 0 );
            InputDevice* input( int id = 0 );

            bool eventFilter(QObject* object, QEvent* event);

            void installEventFiltered(QObject *filteredObj);
            void removeEventFiltered(QObject *filteredObj);

            QObject* filteredObject();
            void setFilteredObject(QObject *filteredObj);

            // TODO: if it works we can polish, with switch usage instead of hash? Investigate more!
            KeyboardManagementType kbManagementType() const;
            void setKbManagementType( KeyboardManagementType kbManagementType );

        signals:
            void buttonStateChanged( int button, int value );

        private:
            friend class GluonCore::Singleton<InputManager>;
            InputManager( QObject* parent = 0 );
            ~InputManager();
            Q_DISABLE_COPY(InputManager);
            void init();

            QObject *m_filteredObj;
            KeyboardManagementType m_kbManagementType;

            InputManagerPrivate* d;
    };
}

#endif
