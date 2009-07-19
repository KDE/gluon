#include "myWidget.h"
#include <KDebug>
#include <QVBoxLayout>
MyWidget::MyWidget(QWidget *parent)
  :QWidget(parent)
  {
timer = new QTimer;
timer->setInterval(20);
timer->start();

connect(timer,SIGNAL(timeout()),this, SLOT(mainLoop()));

input = new KCLInput("/dev/input/event3");
mouse = new KCLMouse("/dev/input/event4",this);


kcl = new KCLEngine;

kcl->addInput(mouse);
kcl->addInput(input);

  }

void MyWidget::mainLoop()
{

 if ( kcl->lastButton() != "NULL")
 kDebug()<<"HERE : "<<kcl->lastButton();

  
  
}


 