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

#include "gluonhardwarebuttonsprivate.h"
#include "gluonbuttons.h"

#include <QtCore/QMetaEnum>
#include <QtCore/QMetaObject>
#include <QtCore/QDebug>

using namespace GluonInput;

template<> GLUON_INPUT_EXPORT GluonHardwareButtons *GluonCore::Singleton<GluonHardwareButtons>::m_instance = 0;

GluonHardwareButtons::GluonHardwareButtons()
{
	d = new GluonHardwareButtonsPrivate();
	
	d->keyboardButtonMapping = this->initMapping("KeyboardButton");
	d->joystickButtonMapping = this->initMapping("JoystickButton");
	d->joystickAxisMapping = this->initMapping("JoystickAxis");
	d->mouseAxisMapping = this->initMapping("MouseAxis");
	d->mouseButtonMapping = this->initMapping("MouseButton");
	
}

GluonHardwareButtons::~GluonHardwareButtons()
{
}

QHash<int, int> GluonHardwareButtons::initMapping(const char * enumName)
{
	QHash<int, int> mapping;
	int gluonButtonsEnumIndex = GluonButtons::instance()->metaObject()->indexOfEnumerator(enumName);
	int gluonHardwareEnumIndex = this->metaObject()->indexOfEnumerator(enumName);
	if(gluonButtonsEnumIndex > -1 && gluonHardwareEnumIndex > -1)
	{
		QMetaEnum gluonButtonsEnum = GluonButtons::instance()->metaObject()->enumerator(gluonButtonsEnumIndex);
		QMetaEnum gluonHardwareEnum = this->metaObject()->enumerator(gluonHardwareEnumIndex);
		int gluonHardwareEnumKeyCount = gluonHardwareEnum.keyCount();
		
		for(int i = 0; i < gluonHardwareEnumKeyCount; i++)
		{
			int gluonButtonVal = gluonButtonsEnum.keyToValue(gluonHardwareEnum.key(i));
			if(gluonButtonVal > -1)
			{
				mapping.insert(gluonHardwareEnum.keyToValue(gluonHardwareEnum.key(i)), gluonButtonVal);
			}
		}
	}
	
	return mapping;
}

int GluonHardwareButtons::hardwareButtonsToGluonButtons(DeviceFlag deviceType, int code)
{
	switch (deviceType)
	{
		case KeyboardDevice:
			return d->keyboardButtonMapping.contains(code) ? d->keyboardButtonMapping.value(code) : -1;
		case MouseDevice:
			return d->mouseButtonMapping.contains(code) ? d->mouseButtonMapping.value(code) : -1;
		case JoystickDevice:
			return d->joystickButtonMapping.contains(code) ? d->joystickButtonMapping.value(code) : -1;
		default:
			return -1;
	}
}

int GluonHardwareButtons::hardwareMovementToGluonAxis(DeviceFlag deviceType, int code)
{
	switch (deviceType)
	{
		case MouseDevice:
			return d->mouseAxisMapping.contains(code) ? d->mouseAxisMapping.value(code) : -1;
		case JoystickDevice:
			return d->joystickAxisMapping.contains(code) ? d->joystickAxisMapping.value(code) : -1;
		default:
			return -1;
	}	
}

#include "gluonhardwarebuttons.moc"
