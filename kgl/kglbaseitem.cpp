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
#include "kglbaseitem.h"
#include <algorithm>



KGLBaseItem::KGLBaseItem(QObject *parent)
             :QObject(parent)
{
    m_angle = 0;
    m_position=QPointF(0,0);
    m_scale = 1;
    m_center=QPointF(0,0);
    m_polygon = QPolygonF();
    m_dim = QSizeF();
    m_radius = 1;
    m_zindex = 0;

}
KGLBaseItem::~KGLBaseItem()
{


}


void  KGLBaseItem::updateTransform()
{
    m_matrix.setIdentity();

    m_matrix.translate(Eigen::Vector3d(m_position.x() , m_position.y(), 0));

    m_matrix.translate(Eigen::Vector3d(itemCenter().x() , itemCenter().y(), 0));
    m_matrix.rotate(Eigen::AngleAxisd(m_angle, AXIS_Z));
    m_matrix.translate(Eigen::Vector3d(-itemCenter().x() , -itemCenter().y(), 0));

        m_matrix.scale(m_scale);

}

void KGLBaseItem::resetTransform()
{
    m_matrix.setIdentity();
    m_angle  = 0;
    m_scale  = 1;
    m_position = QPointF(0,0);
}



void KGLBaseItem::computeGeometry()
{
    //Compute the center
    m_center = QPointF(0,0);
    foreach(GLPoint* p, m_vertexList) {
        m_center += QPointF(p->x(), p->y());
    }
    m_center /= (float)vertexNumber();

    //Compute the Polygon
    m_polygon = QPolygonF();
    foreach(GLPoint* p, m_vertexList) {
        m_polygon<<QPointF(p->x(), p->y());
    }

    //Compute width and height
    m_dim.setWidth( m_polygon.boundingRect().width());
    m_dim.setHeight(m_polygon.boundingRect().height());

    //Compute the radius of bounding Circle
    const double cx = m_center.x();
    const double px = m_vertexList[0]->x();
    const double cy = m_center.y();
    const double py = m_vertexList[0]->y();

    m_radius = sqrt((cx - px) * (cx - px) + (cy - py) * (cy - py));



}

//=======================================================

QPointF KGLBaseItem::transform(QPointF p)
{
    Eigen::Vector3d vect = m_matrix * Eigen::Vector3d(p.x(), p.y(), 0);
    return QPointF(vect.x(), vect.y());

}
//=========================================================
QPolygonF KGLBaseItem::transform(QPolygonF p)
{
    QPolygonF poly;
    foreach(QPointF point, p) {
        poly<<transform(point);
    }
    return poly;

}
//=========================================================
QRectF KGLBaseItem::transform(QRectF r)
{
    Eigen::Vector3d a = m_matrix * Eigen::Vector3d(r.x(), r.y(), 0);
    Eigen::Vector3d b = m_matrix * Eigen::Vector3d(r.width(), r.height(), 0);

    return QRectF(a.x(), a.y(), b.x(), b.y());

}
//=========================================================
void KGLBaseItem::createBox(const QSizeF &dim)
{
    clear();
    addVertex(new GLPoint(0, 0, Qt::white, QPointF(0 , 0 )));
    addVertex(new GLPoint(dim.width(), 0, Qt::white, QPointF(1 , 0)));
    addVertex(new GLPoint(dim.width(), dim.height(), Qt::white, QPointF(1 , 1)));
    addVertex(new GLPoint(0, dim.height(), Qt::white, QPointF(0 , 1)));

}
void KGLBaseItem::createPolygon(const QPolygonF &poly)
{
    clear();
    QPointF p;
    foreach(p, poly) {
        addVertex(new GLPoint(p.x(), p.y() , Qt::white, QPointF(p.x(), p.y())));
    }

}
void KGLBaseItem::createLine(const QLineF &line)
{
    clear();
    addVertex(new GLPoint(line.x1(), line.y1(), Qt::white));
    addVertex(new GLPoint(line.x2(), line.y2(), Qt::white));


}
