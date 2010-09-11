/******************************************************************************
 * This file is part of the Gluon Development Platform
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
#include "gameloop.h"

#include <QtCore/QDebug>
#include <QtCore/QObject>
#include <QtCore/QPointer>
#include <QtGui/QApplication>

#include "input/keyboard.h"
#include "input/mouse.h"
#include "input/inputmanager.h"

using namespace std;
using namespace GluonInput;

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	if(InputManager::instance()->keyboardList().count() > 0)
	{
		qDebug() <<"creating test gameloop";
		Keyboard * keyboard = InputManager::instance()->keyboard();
		Mouse * mouse = InputManager::instance()->mouse();
		keyboard->setEnabled(true);
		GameLoop * gameLoop = new GameLoop(keyboard, mouse);
		gameLoop->run();
	}

	qDebug() << "starting event loop";
	app.exec();
}
