#ifndef KGLPHYSICSENGINE_H
#define KGLPHYSICSENGINE_H

#include <QMouseEvent>
#include <QList>
#include "kglengine.h"
#include "kgltextitem.h"
#include "kglphysicsitem.h"

#include "Box2D/Box2D.h"
class KGLPhysicsEngine : public KGLEngine
{
    Q_OBJECT
public:
    KGLPhysicsEngine();
    ~KGLPhysicsEngine();
    virtual void mainLoop(float fps);
    void createWorld();
    void computeSimulation(int32 iterations = 10, float fps=60);
    void addPhysicsItem(KGLPhysicsItem *  item);
    void remPhysicsItem(KGLPhysicsItem * item);
    KGLPhysicsItem * physicsItemAt(QPointF pos);
    QList<KGLPhysicsItem*> physicsItemList(){return m_list;}
   KGLPhysicsItem* itemAt(QPointF pos);
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

        b2MouseJoint* m_mouseJoint;
};

#endif // KGLPHYSICSENGINE_H
