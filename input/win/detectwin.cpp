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

#include "detectwin.h"

#include <QtCore/QDir>
#include <QtCore/QCoreApplication>
#include <QtGui/QMessageBox>
#include <QtCore/QDebug>

#include <core/debughelper.h>

#include "inputthread.h"

using namespace GluonInput;

class DetectWin::DetectWinPrivate
{
    public:
        QList<InputDevice *> inputList;
        QList<Keyboard *> keyboardList;
        QList<Mouse *> mouseList;
        QList<Joystick *> joystickList;
        QList<Tablet *> tabletList;
        QList<InputDevice *> unknownList;
};

DetectWin::DetectWin(QObject * parent)
        : Detect(parent),
          d(new DetectWinPrivate)
{
}

DetectWin::~DetectWin()
{
}

void DetectWin::detectDevices()
{

}

void DetectWin::setAllEnabled(bool enable)
{
    foreach(InputDevice *input, this->getInputList())
    {
        input->setEnabled(enable);
    }
}

void DetectWin::clear()
{
    d->inputList.clear();
    d->keyboardList.clear();
    d->mouseList.clear();
    d->joystickList.clear();
    d->tabletList.clear();
    d->unknownList.clear();
}

void DetectWin::addInput(InputDevice *i)
{
    d->inputList.append(i);
}

void DetectWin::addKeyboard(InputDevice *i)
{
    Keyboard * keybd = qobject_cast<Keyboard*>(i);
    d->keyboardList.append(keybd);
}

void DetectWin::addMouse(InputDevice *i)
{
    Mouse * mouse = (Mouse*)i;
    d->mouseList.append(mouse);
}

void DetectWin::addJoystick(InputDevice *i)
{
    Joystick * joy = (Joystick*)i;
    d->joystickList.append(joy);
}

void DetectWin::addTablet(InputDevice *i)
{
    Tablet * tablet = (Tablet*)i;
    d->tabletList.append(tablet);
}

void DetectWin::addUnknown(InputDevice *i)
{
    d->unknownList.append(i);
}

QList<InputDevice *> DetectWin::getInputList()
{
    return d->inputList;
}

QList<Keyboard *> DetectWin::getKeyboardList()
{
    return d->keyboardList;
}

QList<Mouse *> DetectWin::getMouseList()
{
    return d->mouseList;
}

QList<Joystick *> DetectWin::getJoystickList()
{
    return d->joystickList;
}

QList<Tablet *> DetectWin::getTabletList()
{
    return d->tabletList;
}

QList<InputDevice *> DetectWin::getUnknownDeviceList()
{
    return d->unknownList;
}
