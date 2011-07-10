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

#ifndef GLUON_INPUT_DETECTMAC_H
#define GLUON_INPUT_DETECTMAC_H

#include "gluon_input_export.h"

#include "inputdevice.h"
#include "joystick.h"
#include "detect.h"
#include "keyboard.h"
#include "mouse.h"
#include "touch.h"

#include <QtCore/QList>

#include <IOKit/hid/IOHIDLib.h>

namespace GluonInput
{
    class GLUON_INPUT_EXPORT DetectMac : public Detect
    {
            Q_OBJECT

        public:
            DetectMac( QObject* parent );
            virtual ~DetectMac();

            bool isReadable();
            void detectDevices();
            void setAllEnabled( bool enable );

            QList<InputDevice*> inputList();
            QList<Keyboard*> keyboardList();
            QList<Mouse*> mouseList();
            QList<Joystick*> joystickList();
            QList<Touch*> touchList();
            QList<InputDevice*> unknownDeviceList();

            void addInput( InputDevice* i );
            void addKeyboard( Keyboard* i );
            void addMouse( Mouse* i );
            void addJoystick( Joystick* i );
            void addTouch( Touch* i );
            void addUnknown( InputDevice* i );
            void clear();

        private:
            static void createDevices( const void* value, void* context );
            CFMutableDictionaryRef createMatchingDictionary( UInt32 pUsagePage, UInt32 pUsage );

            class Private;
            Private* const d;
    };
}

#endif // GLUON_INPUT_DETECTMAC_H
