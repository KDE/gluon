#ifndef KGLPHYSICSENGINE_H
#define KGLPHYSICSENGINE_H

#include <QMouseEvent>
#include <QList>
#include "kglengine.h"
#include "kgltextitem.h"
#include "kglphysicsitem.h"

#include "Box2D/Box2D.h"


class KGLPhysicsEngine;
class KGLContactListener;


class KGLPhysicsEngine : public KGLEngine
{
    Q_OBJECT
public:
    KGLPhysicsEngine(QObject * parent=0);
    ~KGLPhysicsEngine();
    virtual void mainLoop(float fps);
    void createWorld();
    void computeSimulation(int32 iterations = 10, float fps=60);
   void addItem(KGLPhysicsItem *  item);
   void addItem(KGLItem* item){KGLEngine::addItem(item);}
   bool removeItem(KGLPhysicsItem * item);
   bool removeItem(KGLItem * item){return KGLEngine::removeItem(item);}
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
    KGLContactListener * m_contactListener;
    GLuint tex;
    QList <KGLPhysicsItem*> m_list;

        b2MouseJoint* m_mouseJoint;
};




class KGLContactListener:public b2ContactListener
{
    public:
        void Add(const b2ContactPoint* point);
//        void Persist(const b2ContactPoint* point)
//    {
//        // handle persist point
//    }
//
//        void Remove(const b2ContactPoint* point)
//    {
//        // handle remove point
//    }
//
//    void Result(const b2ContactResult* point)
//    {
//        // handle results
//    }





};











#endif // KGLPHYSICSENGINE_H
