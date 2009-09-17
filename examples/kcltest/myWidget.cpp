#include "myWidget.h"
#include <KDebug>
#include <QVBoxLayout>

MyWidget::MyWidget(QWidget *parent)
  :QWidget(parent)
  {
timer = new QTimer;
timer->setInterval(20);
timer->start();


input = new KCLInput("/dev/input/by-path/pci-0000:00:1d.2-usb-0:2:1.0-event-joystick");
input->setEnable();

connect(timer,SIGNAL(timeout()),this, SLOT(mainLoop()));




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