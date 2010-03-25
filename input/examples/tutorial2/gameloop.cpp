#include "gameloop.h"

#include "input/inputdevice.h"
#include "input/keyboard.h"

#include <QtCore/QTime>
#include <QtCore/QDebug>
#include <QtCore/QCoreApplication>

GameLoop::GameLoop(Keyboard * keyb)
{
    this->keyboard = keyb;
    connect(this, SIGNAL(startGameLoop()), this, SLOT(gameLoop()), Qt::QueuedConnection);
}

void GameLoop::run()
{
  emit this->startGameLoop();
}

void GameLoop::gameLoop()
{
    int nextTick = 0, loops = 0;
    int timeLapse = 0;
    QTime timer;
    int updatesPerSecond = 25;
    int maxFrameSkip = 5;
    int millisecondsPerUpdate = 1000 / updatesPerSecond;
    timer.start();
    
    qDebug() << "starting gameloop";
    while (true)
    {	
        loops = 0;
        while (timer.elapsed() > nextTick && loops < maxFrameSkip)
        {
	    foreach(int button, keyboard->buttonCapabilities())
	    {
		if(keyboard->buttonPressed(button))
		   qDebug() << keyboard->buttonName(button) << " is pressed ";
		  
	    }
	  
            nextTick += millisecondsPerUpdate;
            loops++;
        }

        timeLapse = (timer.elapsed() + millisecondsPerUpdate - nextTick) / millisecondsPerUpdate;
    }
}

#include "gameloop.moc"