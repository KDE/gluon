/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
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
#include "detectlinux.h"

#include <QtCore/QDir>
#include <QtCore/QCoreApplication>
#include <QtGui/QMessageBox>
#include <QtCore/QDebug>

#include <core/debughelper.h>

#include "inputthread.h"
#include "detectlinuxprivate.h"

using namespace GluonInput;

DetectLinux::DetectLinux(QObject * parent)
		: Detect(parent)
{
	d = new DetectLinuxPrivate();
}

DetectLinux::~DetectLinux()
{
	//    kDebug()<<"clear device...";
	//    foreach ( KCLInput * input, m_inputList)
	//    {
	//        delete input;
	//    }
}

void DetectLinux::detectDevices()
{
	DetectLinux *detect = this;
	detect->clear();
	QString path("/dev/input/by-path/");
	QDir event(path);

	foreach(const QString &name, event.entryList(QDir::Files))
	{
		InputDevice *device = NULL;
		InputThread* thread = new InputThread(path + name);
		if (!thread->error())
		{
			switch (thread->deviceType())
			{
				case GluonInput::KeyboardDevice:
					device = new Keyboard(thread);
					detect->addKeyboard(device);
					break;

				case GluonInput::MouseDevice:
					device = new Mouse(thread);
					detect->addMouse(device);
					break;

				case GluonInput::TouchpadDevice:
					device = new Mouse(thread);
					detect->addMouse(device);
					break;

				case GluonInput::JoystickDevice:
					device = new Joystick(thread);
					detect->addJoystick(device);
					break;

				case GluonInput::TabletDevice:
					device = new Tablet(thread);
					detect->addTablet(device);
					break;

				case GluonInput::UnknownDevice:
					device = new InputDevice(thread);
					detect->addUnknown(device);
					break;
			}
			
			detect->addInput(device);
		}
	}
}

void DetectLinux::setAllEnabled(bool enable)
{
	foreach(InputDevice *input, this->getInputList())
	{
		input->setEnabled(enable);
	}
}

void DetectLinux::clear()
{
	d->inputList.clear();
	d->keyboardList.clear();
	d->mouseList.clear();
	d->joystickList.clear();
	d->tabletList.clear();
	d->unknownList.clear();
}

void DetectLinux::addInput(InputDevice *i)
{
	d->inputList.append(i);
}

void DetectLinux::addKeyboard(InputDevice *i)
{
	Keyboard * keybd = qobject_cast<Keyboard*>(i);
	d->keyboardList.append(keybd);
}

void DetectLinux::addMouse(InputDevice *i)
{
	Mouse * mouse = (Mouse*)i;
	d->mouseList.append(mouse);
}

void DetectLinux::addJoystick(InputDevice *i)
{
	Joystick * joy = (Joystick*)i;
	d->joystickList.append(joy);
}

void DetectLinux::addTablet(InputDevice *i)
{
	Tablet * tablet = (Tablet*)i;
	d->tabletList.append(tablet);
}

void DetectLinux::addUnknown(InputDevice *i)
{
	d->unknownList.append(i);
}

QList<InputDevice *> DetectLinux::getInputList()
{
	return d->inputList;
}

QList<Keyboard *> DetectLinux::getKeyboardList()
{
	return d->keyboardList;
}

QList<Mouse *> DetectLinux::getMouseList()
{
	return d->mouseList;
}

QList<Joystick *> DetectLinux::getJoystickList()
{
	return d->joystickList;
}

QList<Tablet *> DetectLinux::getTabletList()
{
	return d->tabletList;
}

QList<InputDevice *> DetectLinux::getUnknownDeviceList()
{
	return d->unknownList;
}

#include "detectlinux.moc"
