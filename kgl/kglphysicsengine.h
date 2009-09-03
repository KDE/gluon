/*
 * This file is part of the Gluon library.
 * Copyright 2009 Gluon team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef KGLPHYSICSENGINE_H
#define KGLPHYSICSENGINE_H

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
        
        bool removeItem(KGLItem * item)
        {
            return KGLEngine::removeItem(item);
        }

        KGLPhysicsItem * physicsItemAt(QPointF pos);
        
        QList<KGLPhysicsItem*> physicsItemList()
        {
            return m_list;
        }

        KGLPhysicsItem* itemAt(QPointF pos);
        
        void setGravity(const QPointF& g)
        {
            m_gravity.x = g.x();
            m_gravity.y = g.y();
        }

    public slots:
        void clearPhysicsItem();

        b2World *world()
        {
            return m_world;
        }

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
