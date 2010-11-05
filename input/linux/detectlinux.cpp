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

#include "inputthread.h"
#include "detectlinuxprivate.h"

#include <core/debughelper.h>

#include <QtCore/QDir>
#include <QtCore/QCoreApplication>
#include <QtGui/QMessageBox>
#include <QtCore/QDebug>

using namespace GluonInput;

DetectLinux::DetectLinux(QObject *parent)
    : Detect(parent)
    , d(new DetectLinuxPrivate)
{
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
    QDir event("/dev/input/by-path/");
    QStringList readableInputFiles;
    QStringList unreadableInputFiles;
    QString file;
    QFileInfoList inputFileInfoList;

    inputFileInfoList = event.entryInfoList(QDir::Files);
    foreach (QFileInfo inputFileInfo, inputFileInfoList) {
        file = inputFileInfo.filePath();
        if (access(file.toUtf8(), R_OK) != -1)
            readableInputFiles.append(file);
        else
            unreadableInputFiles.append(file);
    }

    foreach (const QString &name, readableInputFiles) {
        InputDevice *device = 0;
        InputThread *thread = new InputThread(name);
        if (!thread->error()) {
            switch (thread->deviceType()) {
            case GluonInput::KeyboardDevice:
                device = new Keyboard(thread);
                detect->addKeyboard(static_cast<Keyboard *>(device));
                break;

            case GluonInput::MouseDevice:
                device = new Mouse(thread);
                detect->addMouse(static_cast<Mouse *>(device));
                break;

            case GluonInput::TouchpadDevice:
                device = new Mouse(thread);
                detect->addMouse(static_cast<Mouse *>(device));
                break;

            case GluonInput::JoystickDevice:
                device = new Joystick(thread);
                detect->addJoystick(static_cast<Joystick *>(device));
                break;

            case GluonInput::TouchDevice:
                device = new Touch(thread);
                detect->addTouch(static_cast<Touch *>(device));
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
    foreach(InputDevice *input, inputList()) {
        input->setEnabled(enable);
    }
}

void DetectLinux::clear()
{
    d->inputList.clear();
    d->keyboardList.clear();
    d->mouseList.clear();
    d->joystickList.clear();
    d->touchList.clear();
    d->unknownList.clear();
}

void DetectLinux::addInput(InputDevice *i)
{
    d->inputList.append(i);
}

void DetectLinux::addKeyboard(Keyboard *keyboard)
{
    d->keyboardList.append(keyboard);
}

void DetectLinux::addMouse(Mouse *mouse)
{
    d->mouseList.append(mouse);
}

void DetectLinux::addJoystick(Joystick *joystick)
{
    d->joystickList.append(joystick);
}

void DetectLinux::addTouch(Touch *touch)
{
    d->touchList.append(touch);
}

void DetectLinux::addUnknown(InputDevice *i)
{
    d->unknownList.append(i);
}

QList<InputDevice *> DetectLinux::inputList()
{
    return d->inputList;
}

QList<Keyboard *> DetectLinux::keyboardList()
{
    return d->keyboardList;
}

QList<Mouse *> DetectLinux::mouseList()
{
    return d->mouseList;
}

QList<Joystick *> DetectLinux::joystickList()
{
    return d->joystickList;
}

QList<Touch *> DetectLinux::touchList()
{
    return d->touchList;
}

QList<InputDevice *> DetectLinux::unknownDeviceList()
{
    return d->unknownList;
}

#include "detectlinux.moc"
