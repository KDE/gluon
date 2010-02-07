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

#include "baseitem.h"
#include <algorithm>

using namespace GluonGraphics;

BaseItem::BaseItem(QObject *parent)
    : QObject(parent)
{
    m_position = Eigen::Vector3f::Zero();
    m_scale = Eigen::Vector3f::Ones();
    m_center= Eigen::Vector3f::Zero();
    m_polygon = QPolygonF();
    m_dim = QSizeF();

    m_orientation = Eigen::Quaternionf::Identity();
}

BaseItem::~BaseItem()
{
}

void  BaseItem::updateTransform()
{
    m_matrix.setIdentity();

    m_matrix.translate(m_position);
    m_matrix.scale(m_scale);
    m_matrix.rotate(m_orientation);
}

void BaseItem::resetTransform()
{
    m_matrix.setIdentity();
    m_position = Eigen::Vector3f::Zero();
    m_scale = Eigen::Vector3f::Ones();
    m_orientation = Eigen::Quaternionf::Identity();
}

void BaseItem::computeGeometry()
{
    //Compute the center
    m_center = Eigen::Vector3f::Zero();
    foreach(const Vertex &p, m_vertexList) {
        m_center += Eigen::Vector3f(p.x(), p.y(), 0);
    }
    m_center /= (float)vertexCount();

    //Compute the Polygon
    m_polygon = QPolygonF();
    foreach(const Vertex &p, m_vertexList) {
        m_polygon<<QPointF(p.x(), p.y());
    }

    //Compute width and height
    m_dim.setWidth( m_polygon.boundingRect().width());
    m_dim.setHeight(m_polygon.boundingRect().height());

    //Compute the radius of bounding Circle
    const double cx = m_center.x();
    const double px = m_vertexList[0].x();
    const double cy = m_center.y();
    const double py = m_vertexList[0].y();

    m_radius = sqrt((cx - px) * (cx - px) + (cy - py) * (cy - py));
}

//=======================================================

QPointF BaseItem::transform(const QPointF &p) const
{
    Eigen::Vector3f vect = m_matrix * Eigen::Vector3f(p.x(), p.y(), 0);
    return QPointF(vect.x(), vect.y());
}

//=========================================================

QPolygonF BaseItem::transform(const QPolygonF &p) const
{
    QPolygonF poly;
    foreach(const QPointF &point, p) {
        poly<<transform(point);
    }
    return poly;
}

//=========================================================

QRectF BaseItem::transform(const QRectF &r) const
{
    Eigen::Vector3f a = m_matrix * Eigen::Vector3f(r.x(), r.y(), 0);
    Eigen::Vector3f b = m_matrix * Eigen::Vector3f(r.width(), r.height(), 0);

    return QRectF(a.x(), a.y(), b.x(), b.y());
}

//=========================================================

void BaseItem::createBox(const QSizeF &dim)
{
    clear();
    addVertex(Vertex(-dim.width()/2, -dim.width()/2, Qt::white, QPointF(0 , 0 )));
    addVertex(Vertex( dim.width()/2, -dim.width()/2, Qt::white, QPointF(1 , 0)));
    addVertex(Vertex( dim.width()/2,  dim.width()/2, Qt::white, QPointF(1 , 1)));
    addVertex(Vertex(-dim.width()/2,  dim.width()/2, Qt::white, QPointF(0 , 1)));
    computeGeometry();
}

void BaseItem::createPolygon(const QPolygonF &poly)
{
    clear();
    foreach(const QPointF &p, poly) {
        addVertex(Vertex(p.x(), p.y() , Qt::white, QPointF(p.x(), p.y())));
    }
    computeGeometry();
}

void BaseItem::createLine(const QLineF &line)
{
    clear();
    addVertex(Vertex(line.x1(), line.y1(), Qt::white));
    addVertex(Vertex(line.x2(), line.y2(), Qt::white));
    computeGeometry();
}

#include "baseitem.moc"
