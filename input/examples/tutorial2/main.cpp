#include "gameloop.h"

#include <QtCore/QDebug>
#include <QtCore/QObject>
#include <QtCore/QPointer>
#include <QtGui/QApplication>

#include "input/keyboard.h"
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
	  keyboard->setEnabled(true);
	  GameLoop * gameLoop = new GameLoop(keyboard);
	  gameLoop->run();
	}

	qDebug() << "starting event loop";
	app.exec();
}
