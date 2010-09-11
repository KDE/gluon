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
#include "inputdevice.h"

#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QMetaObject>
#include <QtCore/QMetaEnum>

#include "absval.h"
#include "inputdeviceprivate.h"
#include "inputbuffer.h"
#include "gluondevices.h"

#include <core/debughelper.h>

using namespace GluonInput;

InputDevice::InputDevice(InputThread * inputThread, QObject * parent)
	: QObject(parent)
{
	d = new InputDevicePrivate();
	d->inputThread = inputThread;
	d->inputThread->setParent(this);	
	d->inputBuffer = new InputBuffer();
	d->inputBuffer->setParent(this);
	
	connect(inputThread, SIGNAL(buttonStateChanged(int, int)), this, SLOT(buttonStateChanged(int, int)), Qt::DirectConnection);
}

InputDevice::InputDevice()
{
}

InputDevice::~InputDevice()
{
	this->setEnabled(false);
	delete d->inputThread;
	delete d->inputBuffer;

	qDebug() << "Closed device :" << deviceName();
}

int InputDevice::vendor()const
{
	return d->inputThread->vendor();
}

int InputDevice::product()const
{
	return d->inputThread->product();
}

int InputDevice::version()const
{
	return d->inputThread->version();
}

int InputDevice::bustype()const
{
	return d->inputThread->bustype();
}

const QString InputDevice::deviceName() const
{
	return d->inputThread->deviceName();
}

GluonInput::DeviceFlag InputDevice::deviceType()const
{
	return d->inputThread->deviceType();
}

QList<int> InputDevice::buttonCapabilities()const
{
	return d->inputThread->buttonCapabilities();
}

QList<int> InputDevice::axisCapabilities() const
{
	return d->inputThread->axisCapabilities();
}

/*QList<int> InputDevice::relAxisCapabilities()const
{
	return d->inputThread->relAxisCapabilities();
}*/

AbsVal InputDevice::axisInfo(int axisCode)const
{
	return d->inputThread->axisInfo(axisCode);
}

bool InputDevice::error()const
{
	return d->inputThread->error();
}

QString InputDevice::msgError()const
{
	return d->inputThread->msgError();
}

bool InputDevice::isEnabled() const
{
	return d->inputThread->isEnabled();
}

void InputDevice::setEnabled(bool enable)
{
  if(enable && !d->inputThread->isEnabled())
  {
	d->inputThread->start();
  }
  else if (!enable && d->inputThread->isEnabled())
  {
	d->inputThread->stop();
  }
}

void InputDevice::setInputThread(InputThread * inputThread)
{
	d->inputThread->stop();
	delete d->inputThread;
	d->inputThread = inputThread;
}

InputThread * InputDevice::inputThread() const
{
	return d->inputThread;
}

bool InputDevice::buttonPressed(int code) const
{
	return d->inputBuffer->buttonState(code);
}

QString InputDevice::buttonName(int code) const
{
	return GluonButtons::instance()->buttonName(this->deviceType(), code);
}

QString InputDevice::axisName(int code) const
{
	switch (this->deviceType())
	{
		case MouseDevice:
		case JoystickDevice:
			return GluonButtons::instance()->axisName(this->deviceType(), code);
			break;
		default:
			return "Unknown";
			break;
	}		
}

void InputDevice::buttonStateChanged(int code, int value)
{
	d->inputBuffer->setButtonState(code, value);
}

#include "inputdevice.moc"
