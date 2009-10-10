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

#include "kgl_export.h"
#include "kglengine.h"
#include "kgltextitem.h"
#include "kglphysicsitem.h"

#include "Box2D/Box2D.h"

/**
 * \defgroup KGL KGL
 */
//@{

class KGLPhysicsEngine;
class KGLContactListener;

class KGL_EXPORT KGLPhysicsEngine : public KGLEngine
{
    Q_OBJECT
public:
    KGLPhysicsEngine(QObject * parent=0);
    ~KGLPhysicsEngine();


    void computeSimulation(int32 iterations = 10, float fps=60);
    void addItem(KGLPhysicsItem *  item);
    void addItem(KGLItem* item){KGLEngine::addItem(item);}
    bool removeItem(KGLPhysicsItem * item);

    bool removeItem(KGLItem * item)
    {
        return KGLEngine::removeItem(item);
    }
    void createWorld( const QPointF &gravity=QPointF(0.0f,-10.0f), bool sleep=true);
    b2World *world()
    {
        return m_world;
    }

    KGLPhysicsItem * physicsItemAt(QPointF pos);

    QList<KGLPhysicsItem*> physicsItems() const
    {
        return m_list;
    }

    KGLPhysicsItem* itemAt(const QPointF &pos) const;


public slots:
    void clearPhysicsItems();

protected:
    virtual void mainLoop(float fps);

private:
    b2World *m_world;
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

//@}
#endif // KGLPHYSICSENGINE_H
