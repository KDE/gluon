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
#include "kglphysicsitem.h"
#include <KDebug>
KGLPhysicsItem::KGLPhysicsItem(KGLEngine * parent)
    :KGLItem(parent)
{
    setObjectName("PhysicsItem");
    m_body = NULL;
    m_isMassFromShape=true;
    m_shapeType = POLYGON_SHAPE;
    initDensity(1.0f);
    initFriction(0.3f);

}
void KGLPhysicsItem::setupParam()
{
    m_bodyDef.userData = this;
    m_bodyDef.position.Set(position().x(), position().y());
    m_bodyDef.angle = angle();



    if ( m_shapeType == POLYGON_SHAPE)
    {
        if ( itemPolygon().size() > 8)
        {
            kDebug()<<"Error! Cannot build a physics polygon with more 8 vertex...";
            return;
        }
        m_polygonDef.vertexCount = itemPolygon().size();
        kDebug()<<"POLYGON!!!!!!!!!!";
        //---CONSTRUCT A POYLGON SHAPE
        int i=0;
        foreach (QPointF p, itemPolygon())
        {
            m_polygonDef.vertices[i].Set(p.x(),p.y());
            kDebug()<<m_polygonDef.vertices[i].x;
            kDebug()<<m_polygonDef.vertices[i].y;
            ++i;
        }
    }
    if ( m_shapeType == CIRCLE_SHAPE)
    {

        kDebug()<<"CIRCLE!!!!!!!!!!";
        //CONSTRUCT A CIRCLE SHAPE
        m_circleDef.radius = radius();
        m_circleDef.density = 1;
        m_circleDef.friction = 0.3;
        m_circleDef.restitution = 0.5;
        m_circleDef.localPosition.x = itemCenter().x();
        m_circleDef.localPosition.y = itemCenter().y();
        kDebug()<<"RADIUS:"<<radius();

    }


}


void KGLPhysicsItem::setup(b2World *world)
{
    setupParam();
    m_body = world->CreateBody(&m_bodyDef);

    if ( m_shapeType == POLYGON_SHAPE)
        m_body->CreateShape(&m_polygonDef);

    if ( m_shapeType == CIRCLE_SHAPE)
        m_body->CreateShape(&m_circleDef);

    if ( m_isMassFromShape == true)
        m_body->SetMassFromShapes();
}
void KGLPhysicsItem::updatePhysics()
{
    setPosition(body()->GetPosition().x, body()->GetPosition().y);
    setAngle(body()->GetAngle());
   updateTransform();

}
b2Body* KGLPhysicsItem::body()
{
    if ( m_body != NULL)
        return m_body;

    else
    {
        kDebug()<<"ERROR : cannot get the body! You need to add KGLPhyisicsItem to the KGLPhysicsWidget ";
        return NULL;
    }
}
