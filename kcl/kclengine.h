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

#ifndef KCLENGINE_H
#define KCLENGINE_H

#include <QObject>
#include <QEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QList>
#include "joythread.h"
#include "joystickevent.h"
class KCLEngine : public QObject
{
    Q_OBJECT
public:
    KCLEngine(QObject * parent = 0);

//    Qt::MouseButton getMouseButton(){return m_mouseButton;}
//    QPoint getMousePos(){return m_mousePos;}
//    QList<int> getKeys(){return m_keys;}



    bool button(const QString& id){return m_buttonList.contains(id);}
    QString button()
    {
        if (!m_buttonList.isEmpty())
            return m_buttonList.last();
        else return QString();
    }

    public slots:
    void receiveJoyEvent(JoystickEvent * event);

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void resetInput();

private:

    QList<QString> m_buttonList;







    JoyThread * m_joyThread;

};

#endif // KCLENGINE_H
