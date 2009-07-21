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
#include <QMap>
#include <QPair>
#include <QStringList>
#include <solid/devicenotifier.h>
#include <solid/device.h>
#include <kcomponentdata.h>



#include "kclinput.h"
#include "kclmouse.h"
#include "kcljoystick.h"
#include "kclkeyboard.h"


class KGLEngine;
class VirtualButton;

class VirtualButton
{
    public:
VirtualButton(QString id=0, int keyCode=0, KCLInput *device=NULL);
QString id(){return m_id;}
int code(){return m_keyCode;}
KCLInput * input(){return m_device;}

private:
   QString m_id;
   int m_keyCode;
   KCLInput * m_device;


};



class KCLEngine : public QObject
{
    Q_OBJECT

public:

    KCLEngine(QObject * parent = 0);
    void addInput(KCLInput * input);
    void addInput(const QString &deviceName);
    void addInput(DEVICE device, int id=0);
    void remInput(KCLInput * input){m_inputList.removeOne(input);}
    void remInput(DEVICE device, int id=0);
    KCLInput * input(int id=0){return m_inputList.at(id);}

    void setButton(QString name,int code, KCLInput * input);

    void remAll();

  void searchDevice();
  bool button(QString name);
   bool anyPress();
   bool anyMove();

private:

    QList<KCLInput*> m_inputList;

QMap <QString, int> m_customButtonMap;
QMap <QString,DEVICE> m_devicesType;

QMap <QString, VirtualButton> m_virtalButtonMap;


};

#endif // KCLENGINE_H
