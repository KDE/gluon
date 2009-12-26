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

#ifndef KGLPHYSICSENGINEPRIVATE_H
#define KGLPHYSICSENGINEPRIVATE_H

#include "Box2D/Box2D.h"

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

class KGLPhysicsEnginePrivate
{
    public:
        b2World *m_world;
        KGLContactListener * m_contactListener;
        GLuint tex;
        QList <KGLPhysicsItem*> m_list;
        b2MouseJoint* m_mouseJoint;
};

#endif
