#include "myWidget.h"
#include <KDebug>
#include <QVBoxLayout>

MyWidget::MyWidget(QWidget *parent)
  :QWidget(parent)
  {
timer = new QTimer;
timer->setInterval(20);
timer->start();

KCLButtonWidget * widget = new KCLButtonWidget(0);

widget->show();

connect(timer,SIGNAL(timeout()),this, SLOT(mainLoop()));

// input = new KCLInput("/dev/input/event3");
// mouse = new KCLMouse("/dev/input/event4",this);

pix = new QPixmap(width(),height());
pix->fill(Qt::white);


detect  = new KCLDetect(this);

foreach ( KCLInput * input, detect->deviceList())
{
 kDebug()<<"DEVICE : "<<input->name()<<"error :"<<input->error()<<"-"<<input->msgError(); 
}




pos = QPoint(0,0);

  }
void MyWidget::mainLoop()
{

/*   
kDebug()<<"detected...";*/

 update();
}


//      void MyWidget::paintEvent(QPaintEvent * event)
//     {
//       
//       QPainter paint(this);
//         paint.drawPixmap(0,0,*pix);
//    
//     }