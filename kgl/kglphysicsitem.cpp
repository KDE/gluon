/*
 * This file is part of the Gluon library.
 * Copyright 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright 2008 Charles Huet <packadal@gmail.com>
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

#include "kglphysicsitem.h"
#include <QtCore/QDebug>

KGLPhysicsItem::KGLPhysicsItem(KGLEngine * parent, ShapeType shapeType)
    : KGLItem(parent)
{
    setObjectName("KGLPhysicsItem");
    m_body = NULL;
    m_isMassFromShape=true;
    m_shapeType = shapeType;
    setDensity(1.0f);
    setFriction(0.3f);
    setRestitution(0.5);
}

void KGLPhysicsItem::createShape()
{
    if ( m_shapeType == PolygonShape)
    {
        if ( polygon().size() > 8)
        {
            qDebug()<<"Error! Cannot build a physics polygon with more 8 vertex...";
            return;
        }
        m_polygonDef.vertexCount = polygon().size();
        int i=0;

        foreach (const QPointF &p, polygon())
        {
            m_polygonDef.vertices[i].Set(p.x(),p.y());
            ++i;
        }
    }
    if ( m_shapeType == CircleShape)
    {
        //CONSTRUCT A CIRCLE SHAPE
        m_circleDef.radius = radius();
        m_circleDef.localPosition.x = center().x();
        m_circleDef.localPosition.y = center().y();
    }
}

void KGLPhysicsItem::setup(b2World *world)
{
    createShape();
    m_bodyDef.userData = this;
    m_bodyDef.position.Set(position().x(), position().y());
    m_bodyDef.angle = angle();
    m_body = world->CreateBody(&m_bodyDef);

    if ( m_shapeType == PolygonShape)
    {
        m_body->CreateShape(&m_polygonDef);

    }

    if ( m_shapeType == CircleShape)
    {
        m_body->CreateShape(&m_circleDef);
    }

    if ( m_isMassFromShape == true)
    {
        m_body->SetMassFromShapes();
    }
}

void KGLPhysicsItem::updatePhysics()
{
    setPosition(body()->GetPosition().x, body()->GetPosition().y);
    setAngle(body()->GetAngle()	);
    updateTransform();
}

b2Body* KGLPhysicsItem::body()
{
    if ( m_body != NULL)
        return m_body;

    else
    {
        qDebug()<<"ERROR : cannot get the body! You need to add KGLPhyisicsItem to the KGLPhysicsWidget ";
        return NULL;
    }
}

#include "kglphysicsitem.moc"
