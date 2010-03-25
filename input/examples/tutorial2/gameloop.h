#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <QtCore/QObject>
#include "input/keyboard.h"

using namespace GluonInput;

class GameLoop : public QObject
{
  Q_OBJECT
  public:
    GameLoop(Keyboard * keyb);
    void run();
    
  signals:
    void startGameLoop();
    
  public slots:
    void gameLoop();
    
  private:
    Keyboard * keyboard;
};

#endif // GAMELOOP_H
