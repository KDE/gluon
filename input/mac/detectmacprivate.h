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
#ifndef DETECTMACPRIVATE_H
#define DETECTMACPRIVATE_H

#include <QtCore/QList>
#include <QtCore/QSharedData>
#include <IOKit/hid/IOHIDLib.h>

namespace GluonInput
{
	class InputDevice;
	class Keyboard;
	class Mouse;
	class Joystick;
	class Tablet;

	class DetectMacPrivate : public QSharedData
	{
		public:
			DetectMacPrivate();
			DetectMacPrivate(DetectMacPrivate &other);

			QList<InputDevice *> m_inputList;
			QList<Keyboard *> m_keyboardList;
			QList<Mouse *> m_mouseList;
			QList<Joystick *> m_joystickList;
			QList<Tablet *> m_tabletList;
			QList<InputDevice *> m_unknownList;
			IOHIDManagerRef deviceManager;
			CFSetRef devices;
	};
}
#endif
