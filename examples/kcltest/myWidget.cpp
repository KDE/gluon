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

KCLInput * joy = new KCLInput("/dev/input/event5");
KCLInput * mouse = new KCLInput("/dev/input/event4");
kcl = new KCLEngine;

kcl->setButton("Left",BTN_TRIGGER,joy);
kcl->setButton("Action",BTN_LEFT,mouse);


pos = QPoint(0,0);
  }
void MyWidget::mainLoop()
{


 if (( kcl->button("Left")) &&(kcl->button("Action")))
   kDebug()<<"Je t'aime perrine!!!!!!!!!!!!!!!!!";
  
 
//    pix->fill(Qt::white);
// QPainter paint(pix);
// paint.setPen(QPen(Qt::green));
// 
//  
//  if ( input->anyButton())
//  {
//    
//    
// kDebug()<<input->axisAbsolu(ABS_GAS);
//    pos = QPoint(  input->axisAbsolu(ABS_X), input->axisAbsolu(ABS_Y) );
// paint.drawLine(QPoint(width()/2,height()/2),pos);
//    
//  }
//   


 
 
 update();
}


     void MyWidget::paintEvent(QPaintEvent * event)
    {
      
      QPainter paint(this);
      
      paint.drawPixmap(0,0,*pix);
      
      
      
    }