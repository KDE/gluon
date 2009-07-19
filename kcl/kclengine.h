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
#include <QList>
#include "kclinput.h"


class KCLEngine : public QObject
{
    Q_OBJECT
public:
    KCLEngine(QObject * parent = 0);
    void addInput(KCLInput * input);
    void addInput(const QString &deviceName);

    bool button(const QString& codeName);
    QString lastButton();
private:

    QList<KCLInput*> m_inputList;

};

#endif // KCLENGINE_H
