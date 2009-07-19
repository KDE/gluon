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
kcl = new KCLEngine;
kcl->addInput(KCLEngine::MOUSE,0);
kcl->addInput(KCLEngine::MOUSE,1);
kcl->addInput(KCLEngine::KEYBOARD);
kcl->addInput(KCLEngine::JOYSTICK);
pos = QPoint(0,0);
  }
void MyWidget::mainLoop()
{

 if ( kcl->lastButton() != "NULL")
 {
 
   pix->fill(Qt::white);
QPainter paint(pix);
paint.setPen(QPen(Qt::green));
pos = 50*kcl->relPosition();
paint.drawLine(QPoint(width()/2,height()/2),pos);
  
 

 }
 
 
 update();
}


     void MyWidget::paintEvent(QPaintEvent * event)
    {
      
      QPainter paint(this);
      
      paint.drawPixmap(0,0,*pix);
      
      
      
    }