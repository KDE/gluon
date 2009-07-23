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

#ifndef KGLPHYSICSITEM_H
#define KGLPHYSICSITEM_H

#include "kglitem.h"
#include "Box2D/Box2D.h"
#include <KDebug>

class KGLPhysicsEngine;
class KGLItem;

class KGLPhysicsItem : public KGLItem
{
    Q_OBJECT
    public:
        enum SHAPE_TYPE{POLYGON_SHAPE=0, CIRCLE_SHAPE=1};
        KGLPhysicsItem(KGLEngine* parent=0);
        void setup(b2World *world);
        void setupParam();
        void updatePhysics();
        b2Body * body();

        void setPolygonDef(b2PolygonDef p)
        {
            m_polygonDef = p;
        }

        void setBodyDef(b2BodyDef b)
        {
            m_bodyDef = b;
        }

        void initDensity(const float32 &d )
        {
            m_polygonDef.density = d;
        }

        void initFriction(const float32 &f)
        {
            m_polygonDef.friction = f;
        }

        void initRestitution(const float32 &r)
        {
            m_polygonDef.restitution = r;
        }

        void initSensor(bool b)
        {
            m_polygonDef.isSensor = b;
        }

        void setMass(const float32 &m)
        {
            m_bodyDef.massData.mass = m;
        }

        void initLinearDamping(const float32 &l)
        {
            m_bodyDef.linearDamping = l;
        }

        void initAngularDamping(const float32 &a)
        {
            m_bodyDef.angularDamping = a;
        }

        void initCategoryBits(const uint16 &c)
        {
            m_polygonDef.filter.categoryBits = c;
        }

        void initMaskBits(const uint16 &c)
        {
            m_polygonDef.filter.maskBits = c;
        }

        void setMassFromShape(bool b)
        {
            m_isMassFromShape=b;
        }

        void setStatic()
        {
            setMassFromShape(0);setMass(0);
        }

        void setShapeType(SHAPE_TYPE t = POLYGON_SHAPE)
        {
            m_shapeType = t;
        }

        b2PolygonDef *polygonDef()
        {
            return &m_polygonDef;
        }

        b2BodyDef * bodyDef()
        {
            return &m_bodyDef;
        }

        inline const float32 &density()
        {
            return m_polygonDef.density;
        }

        inline const float32 &friction()
        {
            return m_polygonDef.friction;
        }

        inline const float32 &restition()
        {
            return m_polygonDef.restitution;
        }

        inline const float32 &mass()
        {
            return m_bodyDef.massData.mass;
        }

        inline bool isSensor()
        {
            return m_polygonDef.isSensor;
        }

        inline const float32 &linearDamping()
        {
            return m_bodyDef.linearDamping;
        }

        inline const float32 &angularDamping()
        {
            return m_bodyDef.angularDamping;
        }

        inline const uint16 &categoryBits()
        {
            return m_polygonDef.filter.categoryBits;
        }

        inline const uint16 &maskBits()
        {
            return m_polygonDef.filter.maskBits;
        }

        virtual void collidesWithItem(KGLPhysicsItem * other)
        {
            emit collided(other); emit collided();
        }

    signals:
        void collided(KGLPhysicsItem * other);
        void collided();

    private:
        b2PolygonDef m_polygonDef;
        b2CircleDef m_circleDef;
        b2BodyDef m_bodyDef;
        b2Body *m_body;
        bool m_isMassFromShape;
        SHAPE_TYPE m_shapeType;
};

#endif // KGLPHYSICSITEM_H
