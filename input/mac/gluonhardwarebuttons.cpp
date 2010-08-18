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
#include "gluonhardwarebuttons.h"

#include <QtCore/QMetaEnum>

using namespace GluonInput;

template<> GLUON_INPUT_EXPORT GluonHardwareButtons *GluonCore::Singleton<GluonHardwareButtons>::m_instance = 0;

GluonHardwareButtons::GluonHardwareButtons()
{
}

GluonHardwareButtons::~GluonHardwareButtons()
{
}

int GluonHardwareButtons::hardwareToGluon(DeviceFlag deviceType, int code)
{
	switch (deviceType)
	{
		case KeyboardDevice:
			return keyboardMapping.contains(code) ? keyboardMapping.value(code) : -1;
		case MouseDevice:
			return mouseButtonMapping.contains(code) ? mouseButtonMapping.value(code) : -1;
		case JoystickDevice:
			return joystickButtonMapping.contains(code) ? joystickButtonMapping.value(code) : -1;
		default:
			return -1;
	}
}

#include "gluonhardwarebuttons.moc"
