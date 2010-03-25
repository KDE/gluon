#include "gameloop.h"

#include <QtCore/QDebug>
#include <QtCore/QCoreApplication>
#include <QtCore/QObject>

#include "input/keyboard.h"
#include "input/inputmanager.h"

using namespace std;
using namespace GluonInput;

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);
	
	if(InputManager::instance()->keyboardList().count() > 0)
	{
	  qDebug() <<"creating test gameloop";
	  Keyboard * keyboard = InputManager::instance()->keyboard();
	  keyboard->setEnabled(true);
	  GameLoop * gameLoop = new GameLoop(keyboard);
	  gameLoop->run();
	}
	
	qDebug() << "starting event loop";
	app.exec();
  
	/*QApplication app(argc, argv);

	if (GluonInput::InputManager::instance()->mouseList().size() > 0)
	{
	    GluonInputWidget * widget = new GluonInputWidget(GluonInput::InputManager::instance()->mouse());
	    widget->show();
	    widget->stuff();
	}

	if (GluonInput::InputManager::instance()->joystickList().size() > 0)
	{
	    GluonInputWidget * widget = new GluonInputWidget(GluonInput::InputManager::instance()->joystick());
	    widget->show();
	}
	qDebug() << "showing";

	return app.exec();*/

}
