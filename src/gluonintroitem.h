#ifndef GLUONINTROITEM_H
#define GLUONINTROITEM_H
#include "kgl/kglitem.h"
#include "kgl/kglshadowitem.h"
#include <QTimer>
class GluonIntroItem : public KGLItem
{
    Q_OBJECT
public:
    GluonIntroItem(QSizeF size);
    GluonIntroItem(float w, float h);
    void init();
    public slots:
    void anim();
    private:
    QTimer * m_timer;
    float m_angle;
    float m_alpha;
    float m_d;
float l;
float b;
};

#endif // GLUONINTROITEM_H
