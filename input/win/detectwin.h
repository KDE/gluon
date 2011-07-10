/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2010 Kim Jung Nissen <jungnissen@gmail.com>
 * Copyright (C) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#ifndef GLUON_INPUT_DETECTWIN_H
#define GLUON_INPUT_DETECTWIN_H

#include "inputdevice.h"
#include "joystick.h"
#include "keyboard.h"
#include "mouse.h"
#include "touch.h"
#include "detect.h"

#include <QtCore/QList>

namespace GluonInput
{
    class GLUON_INPUT_EXPORT DetectWin : public Detect
    {
        public:
            DetectWin( QObject* parent );
            virtual ~DetectWin();

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
            class DetectWinPrivate;
            DetectWinPrivate* const d;
    };
}

#endif // GLUON_INPUT_DETECTWIN_H
