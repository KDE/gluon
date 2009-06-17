/*
 * This file is part of the KGLWidget project.
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */
#include "kglphysicswidget.h"

KGLPhysicsWidget::KGLPhysicsWidget(QWidget * parent)
          :KGLWidget(parent)
{

    setMouseTracking (true );
    m_gravity= b2Vec2(0.0f,-10.0f);
    createWorld();
    setOrthoView(-10,10,-10,10  );
    box = new KGLBoxItem(0.1,0.1);
    addItem(box);
   
}
KGLPhysicsWidget::~KGLPhysicsWidget()
{
    delete m_world;
}

void KGLPhysicsWidget::createWorld()
{
    b2AABB worldAABB;
    worldAABB.lowerBound.Set(-100.0f, -100.0f);
    worldAABB.upperBound.Set(100.0f, 100.0f);
 
    bool doSleep = true;
    m_world = new b2World(worldAABB, m_gravity, doSleep);

}
void KGLPhysicsWidget::mainLoop()
{
    computeSimulation(10);
    KGLWidget::mainLoop();
}
void KGLPhysicsWidget::addPhysicsItem(KGLPhysicsItem *  item)
{
    m_list.append(item);
    addItem(item);
    item->setup(m_world);

}

void KGLPhysicsWidget::remPhysicsItem(KGLPhysicsItem * item)
{
    m_list.removeOne(item);
    m_world->DestroyBody(item->body());
    removeItem(item);
}

void KGLPhysicsWidget::clearPhysicsItem()
{
    foreach ( KGLPhysicsItem * item, m_list)
    {
        m_world->DestroyBody(item->body());
        removeItem(item);
    }
    m_list.clear();
}
void KGLPhysicsWidget::computeSimulation(int32 iterations)
{
    float32 timeStep = 1.0f / fps();
    m_world->Step(timeStep, iterations);

    b2Body* node = m_world->GetBodyList();
    while (node)
    {
        b2Body* b = node;
        node = node->GetNext();

        if ( b->GetUserData()!=NULL)
        {
            KGLPhysicsItem* item = (KGLPhysicsItem*)b->GetUserData();
            item->updatePhysics();

        }

        //    if (myActor->IsDead())
        //    {
        //        myWorld->DestroyBody(b);
        //    }
    }



}

KGLPhysicsItem * KGLPhysicsWidget::itemAt(QPointF pos)
{
    b2AABB aabb;
    b2Vec2 d;
    b2Vec2 p(pos.x(),pos.y());
    d.Set(0.1, 0.1);
    aabb.lowerBound = p - d;
    aabb.upperBound = p + d;




    // Query the world for overlapping shapes.
    const int32 k_maxCount = 10;
    b2Shape* shapes[k_maxCount];
    int32 count = m_world->Query(aabb, shapes, k_maxCount);
    b2Body* body = NULL;
    for (int32 i = 0; i < count; ++i)
    {
        b2Body* shapeBody = shapes[i]->GetBody();
        if (shapeBody->IsStatic() == false && shapeBody->GetMass() > 0.0f)
        {
            bool inside = shapes[i]->TestPoint(shapeBody->GetXForm(), p);
            if (inside)
            {
                body = shapes[i]->GetBody();
                if (body->GetUserData()!=NULL)
                {
                    return (KGLPhysicsItem*)body->GetUserData();
                }
                break;
            }
        }
    }

    return NULL;

}



