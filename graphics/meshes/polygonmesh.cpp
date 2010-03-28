/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
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

#include "polygonmesh.h"
namespace GluonGraphics
{
    PolygonMesh::PolygonMesh(QObject * parent)
            : Mesh(parent)
    {
        m_polygon = QPolygonF();
    }
    PolygonMesh::PolygonMesh(const QPolygonF& polygon, QObject * parent)
            : Mesh(parent)
    {
        setPolygon(polygon);
    }
    PolygonMesh::PolygonMesh(const QRectF& rect, QObject * parent)
            : Mesh(parent)
    {
        setPolygon(QPolygonF(rect));
    }
    void PolygonMesh::setPolygon(const QPolygonF &polygon)
    {
        clear();
        m_polygon = polygon;
        foreach(const QPointF &p, m_polygon)
        {
            QVector2D textureCoord(p.x(), p.y());
            addVertex(Vertex(p.x(), p.y(), Qt::white, textureCoord));
        }
    }
}
