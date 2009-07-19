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
KCLEngine::KCLEngine(QObject * parent)
    :QObject(parent)
{

}
void KCLEngine::addInput(KCLInput * input)
{
    if ( input->error()) return;
    m_inputList.append(input);
    kDebug()<<""<<input->device()<<")=>"<<input->name()<<" added to KCLEngine";


}
void KCLEngine::addInput(const QString &deviceName)
{
    KCLInput * input = new KCLInput(deviceName);
    if (input->error()) return;
    addInput(input);


}


bool KCLEngine::button(const QString& codeName)
{

    foreach ( KCLInput * input, m_inputList)
    {
        if ( input->button(codeName))
            return true;
    }
    return false;
}
   QString KCLEngine::lastButton()
   {
   foreach ( KCLInput * input, m_inputList)
    {
        if ( input->lastButton()!=QString("NULL"))
            return input->lastButton();
    }

   return QString("NULL");

   }
