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
#include <QCoreApplication>
KCLEngine::KCLEngine(QObject * parent)
    :QObject(parent)
{
//if (registerEventType (JoystickEvent::JoystickMoveEvent))
//    kDebug()<<"cannot init JoystickMoveEvent";
//
//if (registerEventType (JoystickEvent::JoystickPressEvent))
//      kDebug()<<"cannot init JoystickPressEvent";

    m_joyThread = new JoyThread(this);
    resetInput();
    m_joyThread->start();
    connect(m_joyThread,SIGNAL(sendJoystickEvent(JoystickEvent*)),this, SLOT(receiveJoyEvent(JoystickEvent*)));
    
}
 void KCLEngine::receiveJoyEvent(JoystickEvent * event)
 {
     if ( event->value() == 0)
         resetInput();
     else
m_button = "JOY"+QString::number(event->number());

QCoreApplication::sendEvent(this,event);
 }

void KCLEngine::resetInput()
{
    
    m_mouseButton = Qt::NoButton;
    m_mousePos = QPoint(0,0);
    m_button = QString();
}

bool KCLEngine::eventFilter(QObject *obj, QEvent *event)
{ 
    if ((event->type() == QEvent::MouseButtonPress))
    {
        m_mouseButton = (static_cast<QMouseEvent*>(event))->button();
        m_button = "MOUSE:"+QString::number((static_cast<QMouseEvent*>(event))->button());
    }

    if ((event->type() == QEvent::QEvent::MouseMove))
    {
        m_mousePos= (static_cast<QMouseEvent*>(event))->pos();
        m_mouseButton = (static_cast<QMouseEvent*>(event))->button();
        m_button = "MOUSE:"+QString::number((static_cast<QMouseEvent*>(event))->button());
        resetInput();
 }

    if ((event->type() == QEvent::MouseButtonRelease))
    {
        m_mouseButton= Qt::NoButton;
        resetInput();
    }
  if ((event->type() == QEvent::KeyPress))
    {
        m_keys.append(static_cast<QKeyEvent*>(event)->key());
        m_button = "KEY:"+QString::number(static_cast<QKeyEvent*>(event)->key());
    }

    if ((event->type() == QEvent::KeyRelease))
    {
        m_keys.removeOne(static_cast<QKeyEvent*>(event)->key());
        resetInput();
    }

    return QObject::eventFilter(obj, event);


}
