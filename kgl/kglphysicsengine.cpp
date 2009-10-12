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

#include "kglphysicsengine.h"
#include "kglphysicsengine_p.h"

#include "kglphysicsitem.h"

#include <KDebug>

KGLPhysicsEngine::KGLPhysicsEngine(QObject * parent)
    : KGLEngine(parent)
{
    d = new KGLPhysicsEnginePrivate();
    createWorld();
}

KGLPhysicsEngine::~KGLPhysicsEngine()
{
    delete d->m_world;
    delete d;
}

void KGLPhysicsEngine::createWorld(const QPointF &gravity, bool sleep)
{
    b2AABB worldAABB;
    worldAABB.lowerBound.Set(-100.0f, -100.0f);
    worldAABB.upperBound.Set(100.0f, 100.0f);
    d->m_world = new b2World(worldAABB, b2Vec2(gravity.x(),gravity.y()), sleep);

    KGLContactListener * l = new KGLContactListener;
    d->m_world->SetContactListener(l);
}

b2World *KGLPhysicsEngine::world() const
{
    return d->m_world;
}

QList<KGLPhysicsItem*> KGLPhysicsEngine::physicsItems() const
{
    return d->m_list;
}

void KGLPhysicsEngine::mainLoop(float fps)
{
    computeSimulation(10,fps);
}

void KGLPhysicsEngine::addItem(KGLPhysicsItem *  item)
{
    kDebug()<<"added OK";
    d->m_list.append(item);
    KGLEngine::addItem(item);
    item->setup(d->m_world);
}

void KGLPhysicsEngine::addItem(KGLItem *  item)
{
    KGLEngine::addItem(item);
}

bool KGLPhysicsEngine::removeItem(KGLPhysicsItem * item)
{
    d->m_list.removeOne(item);
    d->m_world->DestroyBody(item->body());
    return KGLEngine::removeItem(item);
}

bool KGLPhysicsEngine::removeItem(KGLItem * item)
{
    return KGLEngine::removeItem(item);
}

void KGLPhysicsEngine::clearPhysicsItems()
{
    foreach ( KGLPhysicsItem * item, d->m_list)
    {
        d->m_world->DestroyBody(item->body());
        removeItem(item);
    }
    d->m_list.clear();
}

void KGLPhysicsEngine::computeSimulation(int32 iterations,float fps)
{
    float32 timeStep = 1.0f / fps;
    d->m_world->Step(timeStep, iterations);

    b2Body* node = d->m_world->GetBodyList();
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

KGLPhysicsItem * KGLPhysicsEngine::itemAt(const QPointF &pos) const
{
    b2AABB aabb;
    b2Vec2 dVec;
    b2Vec2 pVec(pos.x(),pos.y());
    dVec.Set(0.1, 0.1);
    aabb.lowerBound = pVec - dVec;
    aabb.upperBound = pVec + dVec;

    // Query the world for overlapping shapes.
    const int32 k_maxCount = 10;
    b2Shape* shapes[k_maxCount];
    int32 count = d->m_world->Query(aabb, shapes, k_maxCount);
    b2Body* body = NULL;
    for (int32 i = 0; i < count; ++i)
    {
        b2Body* shapeBody = shapes[i]->GetBody();
        if (shapeBody->IsStatic() == false && shapeBody->GetMass() > 0.0f)
        {
            bool inside = shapes[i]->TestPoint(shapeBody->GetXForm(), pVec);
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

//==========================KGLCOntactListener=======================================

void KGLContactListener::Add(const b2ContactPoint* point) 
{
    KGLPhysicsItem * item1 = (KGLPhysicsItem*)(point->shape1->GetBody()->GetUserData());
    KGLPhysicsItem * item2 = (KGLPhysicsItem*)(point->shape2->GetBody()->GetUserData());

    if (item1 && item2)
    {
        item1->collidesWithItem(item2);
        item2->collidesWithItem(item1);
    }
}
