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



VirtualButton::VirtualButton(QString id, int keyCode, KCLInput *device)
{
m_id = id;
m_keyCode = keyCode;
m_device = device;
}




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

    if ( m_devicesType.keys(device).size() < id )
        addInput(m_devicesType.keys(device).at(id));

    else
        kDebug()<<"this device don't exist...";
}

void KCLEngine::remAll()
{
    foreach ( KCLInput * input, m_inputList)
        delete input;
    m_inputList.clear();
}

bool KCLEngine::button(QString name)
{
int code = m_virtalButtonMap[name].code();
    if ( m_virtalButtonMap[name].input()->button(code))
        return true;

    else return false;


}
bool KCLEngine::anyPress()
{
    foreach ( KCLInput * input, m_inputList)
    {
        if ( input->anyPress())
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
    QString path("/dev/input/by-path/");
    QDir event(path);
    
    foreach  ( QString name, event.entryList(QDir::Files))
    {

        KCLInput * temp = new KCLInput(path+name);
        m_devicesType[path+name] = temp->deviceType();
        delete temp;
    }
      
    if (m_devicesType.keys(KCL_MOUSE).size()> 0)
        kDebug()<<m_devicesType.keys(KCL_MOUSE).size()<<" mouse(s) found...";

    if (m_devicesType.keys(KCL_KEYBOARD).size() > 0)
        kDebug()<<m_devicesType.keys(KCL_MOUSE).size() <<" keyboard(s) found...";

    if (m_devicesType.keys(KCL_JOYSTICK).size() > 0)
        kDebug()<<m_devicesType.keys(KCL_MOUSE).size() <<" joystick(s) found...";

    if (m_devicesType.keys(KCL_TABLET).size()> 0)
        kDebug()<<m_devicesType.keys(KCL_TABLET).size() <<" tablet(s) found...";

    if (m_devicesType.keys(KCL_TOUCHPAD).size() > 0)
        kDebug()<<m_devicesType.keys(KCL_TOUCHPAD).size() <<" toucpad(s) found...";

}

//======================================================
   void KCLEngine::setButton(QString name,int code, KCLInput * input)
   {

       VirtualButton button(name,code,input);
       m_virtalButtonMap[name] = button;

   }

