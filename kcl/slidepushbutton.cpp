#include "slidepushbutton.h"
#include <QPaintEvent>
#include <QPainter>
SlidePushButton::SlidePushButton(QWidget * parent)
        :KPushButton(parent)
{
setText("test");
m_min=0;
m_max=10;
m_value=0;
}

  void SlidePushButton::paintEvent ( QPaintEvent * event )
  {

QPushButton::paintEvent(event);


int w  = (m_value-m_min) * event->rect().width() / (m_max-m_min);
QRect rect = event->rect();
rect.setWidth(w);

  QPainter paint(this);
     QLinearGradient gradient(QPoint(event->rect().x(),event->rect().y()),QPoint(event->rect().width(),event->rect().y()));
     gradient.setColorAt(0,QColor(0,255,0,50));
          gradient.setColorAt(0.5,QColor(255,255,0,50));
     gradient.setColorAt(1,QColor(255,0,0,50));

     QBrush brush(gradient);
paint.setPen(QPen(Qt::NoPen));
     paint.setBrush(brush);

  paint.drawRect(rect);

  }
