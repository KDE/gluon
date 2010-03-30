/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 * Copyright (C) 2010 Arjen Hiemstra <>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "vertex.h"
#include <QtCore/QDebug>

namespace GluonGraphics
{

    Vertex::Vertex()
    {
        m_x = 0;
        m_y = 0;
        m_z = 0;
        m_r = 1;
        m_g = 1;
        m_b = 1;
        m_a = 1;
        m_tx = 0;
        m_ty = 0;
    }

    Vertex::Vertex(const QVector2D &p, const QColor &c, const QVector2D &t)
    {
        m_x = p.x();
        m_y = p.y();
        m_z = 0;
        m_r = c.redF();
        m_g = c.greenF();
        m_b = c.blueF();
        m_a = c.alphaF();
        m_tx = t.x();
        m_ty = t.y();
    }
    Vertex::Vertex(const QVector3D &p, const QColor &c, const QVector2D &t)
    {
        m_x = p.x();
        m_y = p.y();
        m_z = p.z();
        m_r = c.redF();
        m_g = c.greenF();
        m_b = c.blueF();
        m_a = c.alphaF();
        m_tx = t.x();
        m_ty = t.y();
    }
    Vertex::Vertex(float x, float y, const QColor &c, const QVector2D &t)
    {
        m_x = x;
        m_y = y;
        m_z = 0;
        m_r = c.redF();
        m_g = c.greenF();
        m_b = c.blueF();
        m_a = c.alphaF();
        m_tx = t.x();
        m_ty = t.y();
    }
    Vertex::Vertex(float x, float y, float z, const QColor &c, const QVector2D &t)
    {
        m_x = x;
        m_y = y;
        m_z = z;
        m_r = c.redF();
        m_g = c.greenF();
        m_b = c.blueF();
        m_a = c.alphaF();
        m_tx = t.x();
        m_ty = t.y();
    }

//=========================================

    VertexList::VertexList()
            : QVector <Vertex>()
    {
    }
}
