#include "myWidget.h"
#include <KDebug>
#include <QVBoxLayout>
MyWidget::MyWidget(QWidget *parent)
  :QWidget(parent)
  {
timer = new QTimer;
timer->setInterval(10);
timer->start();
connect(timer,SIGNAL(timeout()),this, SLOT(mainLoop()));

input = new KCLInput("/dev/input/event5");

kDebug()<<input->name();


  }

void MyWidget::mainLoop()
{
  

  
}