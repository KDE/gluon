/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2010 Kim Jung Nissen <jungnissen@gmail.com>
 * Copyright (C) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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
#ifndef DETECTLINUX_H
#define DETECTLINUX_H

#include "inputdevice.h"
#include "joystick.h"
#include "keyboard.h"
#include "mouse.h"
#include "tablet.h"
#include "detect.h"

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QSharedData>

namespace GluonInput
{
    class GLUON_INPUT_EXPORT DetectWin : public Detect
    {
        public:
            DetectWin(QObject * parent);
            ~DetectWin();

            void detectDevices();
            void setAllEnabled(bool enable);

            QList<InputDevice *> getInputList();
            QList<Keyboard *> getKeyboardList();
            QList<Mouse *> getMouseList();
            QList<Joystick *> getJoystickList();
            QList<Tablet *> getTabletList();
            QList<InputDevice *> getUnknownDeviceList();

            void addInput(InputDevice *i);
            void addKeyboard(InputDevice *i);
            void addMouse(InputDevice *i);
            void addJoystick(InputDevice *i);
            void addTablet(InputDevice *i);
            void addUnknown(InputDevice *i);

            void clear();

        private:
            class DetectWinPrivate;
            DetectWinPrivate * const d;
    };
}
#endif
