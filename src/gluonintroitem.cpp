#include "gluonintroitem.h"

GluonIntroItem::GluonIntroItem(QSizeF size)
{
createBox(size);
init();
}
GluonIntroItem::GluonIntroItem(float w, float h)
{

createBox(QSizeF(w,h));
init();

}

void GluonIntroItem::init()
{
  setTexture(":logo.png");
  m_angle=0;
  m_alpha=0;
  m_d=0.01;
  l=0;
  b=0;
  m_timer = new QTimer(this);
  m_timer->start(10);
  connect(this, SIGNAL(painted()),this, SLOT(anim()));
}

void GluonIntroItem::anim()
{
b+=0.01;
blurFx()->setBlur(b);


rotate(0.01);
l+=0.005;

if ( l>=1)
    l=0;



if ( b>2)
    b=0;
m_lightFx->setLight(l);


   updateTransform();


//    setPosition(-center());updateTransform();
//    setAngle(m_angle);updateTransform();
//    setPosition(-center());updateTransform();





//setTranslate(-QPointF(0.5,0));
//setAngle(m_angle);
//setTranslate(QPointF(0.5,0));
//   updateTransform();
}
