#include "paintwidget.h"
#include <QDebug>
#include <QApplication>
 #include <gluon/kcl/kcldetect.h>
PaintWidget::PaintWidget(QWidget * parent)
        :QWidget(parent)
{
timer = new QTimer;
connect(timer,SIGNAL(timeout()),this,SLOT(mainLoop()));
timer->start(20);
showFullScreen();

}


void PaintWidget::mainLoop()
{
KCLMouse * mouse = KCLDetect::mouse();

if (( mouse->button(BTN_LEFT)) && mouse->button(BTN_RIGHT) )
{
    qDebug()<<"You press on 2 button simultaneous";
}

if ( mouse->button(BTN_LEFT))
    QApplication::setOverrideCursor(( QCursor( Qt::BlankCursor )));

if ( mouse->button(BTN_RIGHT))
    QApplication::setOverrideCursor(( QCursor( Qt::ArrowCursor )));

if ( mouse->button(BTN_MIDDLE))
    QApplication::quit();

mouse->setSensibility(3);


update();
}
void PaintWidget::paintEvent(QPaintEvent * event)
{


    QPainter paint(this);

    paint.drawText(event->rect(),"Press Left Button to hide Kde cursor. Middle Mouse to quit. ");


KCLMouse * mouse = KCLDetect::mouse();
paint.drawPixmap(mouse->position(),KIcon("kde").pixmap(32,32));

if ( KCLDetect::mouseCount()>=2)
  paint.drawPixmap(KCLDetect::mouse(1)->position(),KIcon("kde").pixmap(32,32));




QWidget::paintEvent(event);

}
