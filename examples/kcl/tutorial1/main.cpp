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

    #include <KApplication>
    #include <KAboutData>
    #include <KCmdLineArgs>
    #include <KDebug>
    #include <QDebug>
    #include <QWidget>
    #include <gluon/kcl/kcldetect.h>

    using namespace std;



    int main(int argc, char *argv[])
    {
	KAboutData aboutData("kcl_tutorial1", 0,
			    ki18n("gluon"), "1.0",
			    ki18n("gluon"),
			    KAboutData::License_GPL,
			    ki18n("Copyright (c) 2009 Developer"));
	KCmdLineArgs::init(argc, argv, &aboutData);

	KApplication app;

	qDebug()<<"Number of device avaible : "<<KCLDetect::deviceCount();
	qDebug()<<"Number of keyboard avaible : "<<KCLDetect::keyboardCount();
	qDebug()<<"Number of mouse avaible : "<<KCLDetect::mouseCount();
	qDebug()<<"Number of joystick avaible : "<<KCLDetect::joystickCount();
	qDebug()<<"Number of tablet avaible : "<<KCLDetect::tabletCount();
	qDebug()<<"Number of unknow device avaible : "<<KCLDetect::unknownDeviceCount();
	
	foreach ( KCLInput * input, KCLDetect::inputList())
	{
	  
	  qDebug()<<input->deviceName();
	  qDebug()<<input->devicePath();
	  
	  switch ( input->deviceType())
	  {
	    
	    case KCL::KeyBoard : qDebug()<<"this is a keyboard"; break; 
	    case KCL::Mouse : qDebug()<<"this is a mouse"; break;
	    case KCL::Joystick : qDebug()<<"this is a joystick"; break;
	    case KCL::Tablet : qDebug()<<"this is a tablet"; break;
	    case KCL::Unknown: qDebug()<<"this is an unknow device"; break;
	    default:break;
	  }
	  // Now we can show the capability of inputs...This example show the buttons capabilities
	 foreach (int buttonCode, input->buttonCapabilities())
	 qDebug()<<"BUTTON : "<<buttonCode<<"->"<<KCLCode::buttonName(buttonCode);
	
	  foreach (int axis, input->absAxisCapabilities())
	qDebug()<<"ABSOLUTE AXIS "<<axis<<"->"<<KCLCode::absAxisName(axis);
	 
	  foreach (int axis, input->relAxisCapabilities())
	 qDebug()<<"RELATIF AXIS" <<axis<<"->"<<KCLCode::relAxisName(axis);
	
	 
	  
	  qDebug()<<"===========================================================";
	  
	}
	
	
	
	
	
	
	
	
    app.exec();

    }
