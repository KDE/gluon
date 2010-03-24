/*
* This file is part of the KGLEngine2D project.
* Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
* Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
* Copyright (C) 2008 Charles Huet <packadal@gmail.com>
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

/*#include <QWidget>
#include "../../widgets/gluoninputwidget.h"
#include "input/inputmanager.h"
#include <QtGui>*/
//#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QThread>
#include <QtCore/QTime>
#include <QtCore/QPoint>
#include <QtCore/QCoreApplication>

#include "input/keyboard.h"
#include "input/mouse.h"
#include "input/inputmanager.h"

using namespace std;
using namespace GluonInput;

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);
	
	QTime time;
	int millisecondsPerUpdate = 1000 / 25;
	int maxFrameSkip = 5;
	
	int nextTick = 0, loops = 0;
	int timeLapse = 0;
	time.start();
	
	QPoint old(0,0);
	
	Keyboard * keyboard = InputManager::instance()->keyboard();
	Mouse * mouse = InputManager::instance()->mouse();
	
	foreach(Mouse* m, InputManager::instance()->mouseList())
	{
		qDebug() << m->deviceName();
		if(m->deviceName() == "Trackball")
		{
			qDebug() << "found my mouse";
			mouse = m;
			mouse->enable();
			break;
		}
	}
	
	/*while (true)
	{	
		loops = 0;
		QCoreApplication::processEvents();
		while (time.elapsed() > nextTick && loops < maxFrameSkip)
		{
			foreach(const int button, mouse->buttonCapabilities())
			{
				if(mouse->buttonPressed(button))
					qDebug() << "button : " << mouse->buttonName(button) << " pressed";
			}
			
			if(old != mouse->position())
			{
				old = mouse->position();
				qDebug() << "mouse pos: " << old;
			}
			
			nextTick += millisecondsPerUpdate;
			loops++;
		}
		
		timeLapse = (time.elapsed() + millisecondsPerUpdate - nextTick) / millisecondsPerUpdate;
		
	}//*/
	
	app.exec();
	
    /*QApplication app(argc, argv);

    if (GluonInput::InputManager::instance()->mouseList().size() > 0)
    {
        GluonInputWidget * widget = new GluonInputWidget(GluonInput::InputManager::instance()->mouse());
        widget->show();
    }

    if (GluonInput::InputManager::instance()->joystickList().size() > 0)
    {
        GluonInputWidget * widget = new GluonInputWidget(GluonInput::InputManager::instance()->joystick());
        widget->show();
    }

    app.exec();*/
	
	return 0;

}
