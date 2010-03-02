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

    #include <QWidget>
    #include "../../widgets/gluoninputwidget.h"
    #include "input/detect.h"
    #include <QtGui>
    #include <QtCore/QDebug>
    using namespace std;

    int main(int argc, char *argv[])
    {
	QApplication app(argc, argv);
    
	if ( GluonInput::Detect::instance()->mouseList().size() > 0)
	{
	  GluonInputWidget * widget = new GluonInputWidget(GluonInput::Detect::instance()->mouse());
	  widget->show();
	}
	
	if ( GluonInput::Detect::instance()->joystickList().size() > 0)
	{
	  GluonInputWidget * widget = new GluonInputWidget(GluonInput::Detect::instance()->joystick(0));
	  widget->show();
	}	
	
	app.exec();

    }
