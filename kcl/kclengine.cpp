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
    m_joyThread = new JoyThread("/dev/input/js0",this);
    m_joyThread->start();
    connect(m_joyThread,SIGNAL(sendJoystickEvent(JoystickEvent*)),this, SLOT(receiveJoyEvent(JoystickEvent*)));
    resetInput();
}
void KCLEngine::receiveJoyEvent(JoystickEvent * event)
{

    kDebug()<<event->value();
    kDebug()<<event->number();

    emitJoyEvent(event);
    if ( event->type() == JoystickEvent::JoystickButtonPress)
    {
        if ( event->value())
        {
            QString id = "JOY_"+QString::number(event->number());
            m_buttonList.append(id);
            kDebug()<<id;
        }
        else
        {
            QString id = "JOY_"+QString::number(event->number());
            m_buttonList.removeOne(id);
        }
    }

    if ( event->type() == JoystickEvent::JoystickMove)
    {

        QString id = "JOYAXIS"+QString::number(event->number());

        m_axisList[id] = event->value();

    }



}

void KCLEngine::resetInput()
{
    
    //    m_mouseButton = Qt::NoButton;
    //    m_mousePos = QPoint(0,0);
    //    m_button = QString();
}

bool KCLEngine::eventFilter(QObject *obj, QEvent *event)
{ 
    if ((event->type() == QEvent::MouseButtonPress))
    {
        QMouseEvent * e = static_cast<QMouseEvent*>(event);
        QString id = "MOUSE_"+QString::number(e->button());
        m_buttonList.append(id);
        kDebug()<<id;
    }

    if ((event->type() == QEvent::QEvent::MouseMove))
    {
        m_mousePos= (static_cast<QMouseEvent*>(event))->pos();
    }

    if ((event->type() == QEvent::MouseButtonRelease))
    {
        QMouseEvent * e = static_cast<QMouseEvent*>(event);
        QString id  = "MOUSE_"+QString::number(e->button());
        m_buttonList.removeOne(id);
    }
    if ((event->type() == QEvent::KeyPress))
    {
        QKeyEvent * e = static_cast<QKeyEvent*>(event);
        QString id = keyName(e->key());

        m_buttonList.append(id);
        kDebug()<<"id="<<id;

    }

    if ((event->type() == QEvent::KeyRelease))
    {
        QKeyEvent * e = static_cast<QKeyEvent*>(event);
        QString id = keyName(e->key());
        m_buttonList.removeOne(id);
    }


    return QObject::eventFilter(obj, event);


}

QString KCLEngine::keyName(int key)
{

    if ( key == Qt::Key_Control  )
        return "KEY_CONTROL";

    if ( key ==   Qt::Key_Alt )
        return "KEY_ALT";

    if ( key ==  Qt::Key_Shift )
        return "KEY_SHIFT";

    if ( key == Qt::Key_AltGr )
        return "KEY_ALTGR";


    if ( key == Qt::Key_Meta)
        return "KEY_META";

    QKeySequence seq(key);
    return "KEY_"+seq.toString();



}
