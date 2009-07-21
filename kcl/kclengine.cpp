/*
* This file is part of the KALEngine project.
* Copyright (C) 2007 Laurent Gomila <laurent.gom@gmail.com>
* Copyright (C) 2009 Sacha Schutz <istdasklar@free.fr>
* Copyright (C) 2009 Guillaume Martres <smarter@ubuntu.com>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; see the file COPYING.  If not, write to
* the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
* Boston, MA 02110-1301, USA.
*/
#include "kclengine.h"
#include <KDebug>
#include <QApplication>
#include <QFile>
#include <QDir>
KCLEngine::KCLEngine(QObject * parent)
    :QObject(parent)
{
 searchDevice();
}
void KCLEngine::addInput(KCLInput * input)
{
    if ( input->error()) return;

    if ( m_inputList.contains(input))
    {
        kDebug()<<"input is alreasy attached...";
        return;
    }
    m_inputList.append(input);
    kDebug()<<input->name()<<" at "<<input->device();
}
void KCLEngine::addInput(const QString &deviceName)
{
    KCLInput * input = new KCLInput(deviceName);
    if (input->error()) return;
    addInput(input);
}
void KCLEngine::addInput(DEVICE device, int id)
{

    if ( device == MOUSE)
    {
        if ( id >= m_mouseDevicePath.size())
            kDebug()<<"mouse id don't exist...";
        else
        {
            KCLMouse * mouse = new KCLMouse(m_mouseDevicePath.at(id));
            addInput(mouse);
        }
    }
    if ( device == KEYBOARD)
    {
        if ( id >= m_kbdDevicePath.size())
            kDebug()<<"keyboard id don't exist...";
        else
        {
            KCLKeyBoard * keyboard = new KCLKeyBoard(m_kbdDevicePath.at(id));
            addInput(keyboard);
        }
    }
    if ( device == JOYSTICK)
    {
        if ( id >= m_joystickDevicePath.size())
            kDebug()<<"joystick id don't exist...";
        else
        {
            KCLJoystick * joystick= new KCLJoystick(m_joystickDevicePath.at(id));
            addInput(joystick);
        }
    }
    if ( device == UNKNOWN)
    {
        if ( id >= m_unknownDevicePath.size())
            kDebug()<<"unknown device id don't exist...";
        else
        {
            KCLInput * unknownInput= new KCLInput(m_unknownDevicePath.at(id));
            addInput(unknownInput);
        }
    }
}

void KCLEngine::remAll()
{
    foreach ( KCLInput * input, m_inputList)
        delete input;

    m_inputList.clear();
}

bool KCLEngine::button(int code)
{
    foreach ( KCLInput * input, m_inputList)
    {
        if ( input->button(code))
            return true;
    }
    return false;
}
bool KCLEngine::anyButton()
{
    foreach ( KCLInput * input, m_inputList)
    {
        if ( input->anyButton())
            return true;
    }
    return false;
}
bool KCLEngine::anyMove()
{
    foreach ( KCLInput * input, m_inputList)
    {
        if ( input->anyMove())
            return true;
    }
    return false;
}



void KCLEngine::searchDevice()
{
    m_mouseDevicePath.clear();
    m_kbdDevicePath.clear();
    m_joystickDevicePath.clear();
    m_unknownDevicePath.clear();

    QString path("/dev/input/by-path/");
    QDir event(path);

    foreach  ( QString name, event.entryList(QDir::Files))
    {
        if ( name.contains("event-mouse"))
            m_mouseDevicePath<<path+name;

        if ( name.contains("event-joystick"))
            m_joystickDevicePath<<path+name;

        if ( name.contains("event-kbd"))
            m_kbdDevicePath<<path+name;

        if ( name.contains("event-*"))
            m_unknownDevicePath<<path+name;
    }


    if (m_mouseDevicePath.size()>0)
        kDebug()<<m_mouseDevicePath.size()<< " mouse(s) detected...";

    if (m_joystickDevicePath.size()>0)
        kDebug()<<m_joystickDevicePath.size()<< " joystick(s) detected...";

    if (m_kbdDevicePath.size()>0)
        kDebug()<<m_kbdDevicePath.size()<< " keyboard(s) detected...";

    if (m_unknownDevicePath.size()>0)
        kDebug()<<m_unknownDevicePath.size()<< " unknow input device(s) detected...";
}

//======================================================

