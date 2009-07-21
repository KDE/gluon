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

// input = new KCLInput("/dev/input/event3");
// mouse = new KCLMouse("/dev/input/event4",this);

pix = new QPixmap(width(),height());
pix->fill(Qt::white);

input = new KCLJoystick("/dev/input/event5");

kcl = new KCLEngine;
/*
kcl->addInput(KCLEngine::MOUSE);
kcl->addInput(KCLEngine::MOUSE,1);
kcl->addInput(KCLEngine::JOYSTICK);*/
pos = QPoint(0,0);
  }
void MyWidget::mainLoop()
{


 
   pix->fill(Qt::white);
QPainter paint(pix);
paint.setPen(QPen(Qt::green));

 
 if ( input->anyButton())
 {
   
   
kDebug()<<input->axisAbsolu(ABS_GAS);
   pos = QPoint(  input->axisAbsolu(ABS_X), input->axisAbsolu(ABS_Y) );
paint.drawLine(QPoint(width()/2,height()/2),pos);
   
 }
  


 
 
 update();
}


     void MyWidget::paintEvent(QPaintEvent * event)
    {
      
      QPainter paint(this);
      
      paint.drawPixmap(0,0,*pix);
      
      
      
    }