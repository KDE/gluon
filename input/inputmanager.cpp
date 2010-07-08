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
#include "inputmanager.h"

#include <QtCore/QCoreApplication>
#include <QtGui/QMessageBox>
#include <QtCore/QDebug>

#include "inputmanagerprivate.h"
#include "gluondevices.h"

#ifdef Q_WS_X11
#include "detectlinux.h"
#endif

#ifdef Q_WS_MAC
#include "detectmac.h"
#endif

#ifdef Q_WS_WIN
#include "detectwin.h"
#endif

using namespace GluonInput;

template<> InputManager *GluonCore::Singleton<InputManager>::m_instance = 0;

InputManager::InputManager()
{
	d = new InputManagerPrivate();
	this->init();
}

InputManager::~InputManager()
{
}

void InputManager::init()
{
	QObject *parent = QCoreApplication::instance();
	if (!parent) {
		qDebug() << "No QCoreApplication instance found, the InputManager instance may be leaked when leaving";
	}

#ifdef Q_WS_X11
	d->m_instance = new DetectLinux(parent);
#endif

#ifdef Q_WS_MAC
	d->m_instance = new DetectMac(parent);
#endif

#ifdef Q_WS_WIN
	d->m_instance = new DetectWin(parent);
#endif
	if(d->m_instance)
	{
		d->m_instance->detectDevices();
	}
	else
		qDebug() << "Instance not created, fail!";
}

void InputManager::detectDevices()
{
	d->m_instance->detectDevices();
}

void InputManager::setAllEnabled(bool enable)
{
	d->m_instance->setAllEnabled(enable);
}

unsigned int InputManager::deviceCount()
{
	return inputList().size();
}

unsigned int InputManager::keyboardCount()
{
	return d->m_instance->getKeyboardList().size();
}

unsigned int InputManager::mouseCount()
{
	return d->m_instance->getMouseList().size();
}

unsigned int InputManager::joystickCount()
{
	return d->m_instance->getJoystickList().size();
}

unsigned int InputManager::tabletCount()
{
	return d->m_instance->getTabletList().size();
}

unsigned int InputManager::unknownDeviceCount()
{
	return d->m_instance->getUnknownDeviceList().size();
}

QList<Keyboard*> InputManager::keyboardList()
{
	return d->m_instance->getKeyboardList();
}

QList<Mouse*> InputManager::mouseList()
{
	return d->m_instance->getMouseList();
}

QList<Joystick*> InputManager::joystickList()
{
	return d->m_instance->getJoystickList();
}

QList<Tablet*> InputManager::tabletList()
{
	return d->m_instance->getTabletList();
}

QList<InputDevice*> InputManager::unknownDeviceList()
{
	return d->m_instance->getUnknownDeviceList();
}

InputList InputManager::inputList()
{
	return d->m_instance->getInputList();
}

Keyboard* InputManager::keyboard(int id)
{
    if(d->m_instance->getKeyboardList().count() > 0)
    {
        return d->m_instance->getKeyboardList().at(id);
    }
    return 0;
}

Mouse* InputManager::mouse(int id)
{
    if(d->m_instance->getMouseList().count() > 0)
    {
        return d->m_instance->getMouseList().at(id);
    }
    return 0;
}

Joystick* InputManager::joystick(int id)
{
    if(d->m_instance->getJoystickList().count() > 0)
    {
        return d->m_instance->getJoystickList().at(id);
    }
    return 0;
}

Tablet* InputManager::tablet(int id)
{
    if(d->m_instance->getTabletList().count() > 0)
    {
        return d->m_instance->getTabletList().at(id);
    }
    return 0;
}

InputDevice* InputManager::input(int id)
{
    if(d->m_instance->getInputList().count() > 0)
    {
        return d->m_instance->getInputList().at(id);
    }
    return 0;
}

#include "inputmanager.moc"
