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

input = new KCLInput("/dev/input/event5");


KCLEngine * engine = new KCLEngine;

pos = QPoint(0,0);
  }
void MyWidget::mainLoop()
{
if ( input->anyPress())
   kDebug()<<"pressing..."; 
   
 update();
}


     void MyWidget::paintEvent(QPaintEvent * event)
    {
      
      QPainter paint(this);
        paint.drawPixmap(0,0,*pix);
   
    }