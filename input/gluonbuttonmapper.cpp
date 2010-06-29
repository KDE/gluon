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
#include "gluonbuttonmapper.h"

#include "inputdevice.h"
#include "gluonbuttonmapperprivate.h"

#include <QtCore/QDebug>
#include <QtCore/QMetaEnum>

using namespace GluonInput;

template<> GLUON_INPUT_EXPORT GluonButtonMapper *GluonCore::Singleton<GluonButtonMapper>::m_instance = 0;

GluonButtonMapper::GluonButtonMapper()
{
	d = new GluonButtonMapperPrivate();
}

GluonButtonMapper::~GluonButtonMapper()
{
}


QString GluonButtonMapper::buttonName(DeviceFlag deviceType, int code)
{
	QString value = "";
	switch (deviceType)
	{
		case KeyboardDevice:
			value = this->metaObject()->enumerator(this->metaObject()->indexOfEnumerator("KeyboardButton")).valueToKey(code);
			return value != "" ? value : "Reserved";
			break;
		case MouseDevice:
			value = this->metaObject()->enumerator(this->metaObject()->indexOfEnumerator("MouseButton")).valueToKey(code);
			return value != "" ? value : "Unknown";
			break;
		case JoystickDevice:
			value = this->metaObject()->enumerator(this->metaObject()->indexOfEnumerator("JoystickButton")).valueToKey(code);
			return value != "" ? value : "Unknown";
			break;
		default:
			return "Unknown";
	}
}

QString GluonButtonMapper::axisName(DeviceFlag deviceType,int code)
{
	QString value = "";
	switch (deviceType)
	{
		case MouseDevice:
			value = this->metaObject()->enumerator(this->metaObject()->indexOfEnumerator("RelAbs")).valueToKey(code);
			return value != "" ? value : "Unknown";
			break;
		case JoystickDevice:
			value = this->metaObject()->enumerator(this->metaObject()->indexOfEnumerator("RelAbs")).valueToKey(code);
			return value != "" ? value : "Unknown";
			break;
		default:
			return "Unknown";
	}
}

#include "gluonbuttonmapper.moc"
