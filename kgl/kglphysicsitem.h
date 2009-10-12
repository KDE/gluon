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

#include "kgl_export.h"
#include "kglitem.h"
#include "Box2D/Box2D.h"
#include <KDebug>

/**
 * \defgroup KGL KGL
 */
//@{

class KGLPhysicsEngine;
class KGLItem;

class KGL_EXPORT KGLPhysicsItem : public KGLItem
{
    Q_OBJECT
public:
    enum ShapeType{PolygonShape, CircleShape};

    KGLPhysicsItem(KGLEngine* parent=0, ShapeType shapType=PolygonShape);
    void setup(b2World *world);
    void createShape();
    void updatePhysics();
    b2Body * body();


    void setPolygonDef(b2PolygonDef p)
    {
        m_polygonDef = p;
    }
    void setCircleDef(b2CircleDef p)
    {
        m_circleDef = p;
    }

    void setBodyDef(b2BodyDef b)
    {
        m_bodyDef = b;
    }

    void setDensity(const float32 &d )
    {
        m_polygonDef.density = d;
        m_circleDef.density = d;
    }

    void setFriction(const float32 &f)
    {
        m_polygonDef.friction = f;
        m_circleDef.friction = f;
    }

    void setRestitution(const float32 &r)
    {
        m_polygonDef.restitution = r;
        m_circleDef.restitution = r;
    }

    void setSensor(bool b)
    {
        m_polygonDef.isSensor = b;
        m_circleDef.isSensor = b;
    }

    void setMass(const float32 &m)
    {
        m_bodyDef.massData.mass = m;
    }

    void setLinearDamping(const float32 &l)
    {
        m_bodyDef.linearDamping = l;
    }

    void setAngularDamping(const float32 &a)
    {
        m_bodyDef.angularDamping = a;
    }

    void setCategoryBits(const uint16 &c)
    {
        m_polygonDef.filter.categoryBits = c;
        m_circleDef.filter.categoryBits = c;
    }

    void setMaskBits(const uint16 &c)
    {
        m_polygonDef.filter.maskBits = c;
        m_circleDef.filter.maskBits  = c;
    }

    void setMassFromShape(bool b)
    {
        m_isMassFromShape=b;
    }

    void setStatic(bool s=true)
    {
        if ( s)
        {
            setMassFromShape(0);
            setMass(0);
        }
        else setMassFromShape(true);
    }
    b2PolygonDef *polygonDef()
    {
        return &m_polygonDef;
    }

    b2CircleDef * circleDef()
    {
        return &m_circleDef;
    }
    b2BodyDef * bodyDef()
    {
        return &m_bodyDef;
    }

    inline const float32 &density()
    {
        if ( m_shapeType == PolygonShape)
            return m_polygonDef.density;
        else
            return m_circleDef.density;
    }

    inline const float32 &friction()
    {
        if ( m_shapeType == PolygonShape)
            return m_polygonDef.friction;
        else return m_circleDef.friction;
    }

    inline const float32 &restition()
    {
        if ( m_shapeType == PolygonShape)
            return m_polygonDef.restitution;
        else return m_circleDef.restitution;
    }

    inline const float32 &mass()
    {
        return m_bodyDef.massData.mass;
    }

    inline bool isSensor()
    {
        if ( m_shapeType == PolygonShape)
            return m_polygonDef.isSensor;
        else return m_circleDef.isSensor;
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
        if ( m_shapeType== PolygonShape)
            return m_polygonDef.filter.categoryBits;
        else return m_circleDef.filter.categoryBits;
    }

    inline const uint16 &maskBits()
    {
        if ( m_shapeType==PolygonShape)
            return m_polygonDef.filter.maskBits;
        else return m_circleDef.filter.maskBits;
    }

    virtual void collidesWithItem(KGLPhysicsItem * other)
    {
        emit collided(other);
        emit collided();
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
    ShapeType m_shapeType;
};

//@}
#endif // KGLPHYSICSITEM_H
