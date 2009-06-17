#ifndef KGLPHYSICS_WIDGET_H
#define KGLPHYSICS_WIDGET_H
#include <QMouseEvent>
#include <QList>
#include "kgltextitem.h"
#include "kglwidget.h"
#include "kglphysicsitem.h"

#include "Box2D/Box2D.h"

class KGLPhysicsWidget : public KGLWidget
{
    Q_OBJECT
public:
    KGLPhysicsWidget(QWidget * parent=0);
    ~KGLPhysicsWidget();
    void mainLoop();
    void createWorld();
    void computeSimulation(int32 iterations = 10);
    void addPhysicsItem(KGLPhysicsItem *  item);
    void remPhysicsItem(KGLPhysicsItem * item);
    KGLPhysicsItem * itemAt(QPointF pos);
    QList<KGLPhysicsItem*> physicsItemList(){return m_list;}
    void setGravity(const QPointF& g)
{
 m_gravity.x = g.x();
 m_gravity.y = g.y();
}
public slots:
    void clearPhysicsItem();

    b2World *world(){return m_world;}
private:
    b2World *m_world;
    b2Vec2 m_gravity;
    GLuint tex;
    QList <KGLPhysicsItem*> m_list;
    KGLBoxItem * box;
        b2MouseJoint* m_mouseJoint;
};

#endif
