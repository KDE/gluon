#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>
#include <KLocale>
 
#include "mainwindow.h"
 
int main (int argc, char *argv[])
{
	KAboutData aboutData( "gluonplayerdesktop", 0,
		ki18n("Gluon Player"), "0.72",
		ki18n("Gluon Player Desktop"),
		KAboutData::License_GPL,
		ki18n("Copyright (c) 2013 Gluon Project developers") );
	KCmdLineArgs::init( argc, argv, &aboutData );

	KApplication app;
	
	MainWindow* window = new MainWindow();
	window->show();

	return app.exec();
}

