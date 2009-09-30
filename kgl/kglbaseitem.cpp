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

#include "kglbaseitem.h"
#include <algorithm>

KGLBaseItem::KGLBaseItem(QObject *parent)
    : QObject(parent)
{
    m_angle = 0;
    m_position=QPointF(0,0);
    m_translate=QPointF(0,0);
    m_scale = 1;
    m_rotateCenter = QPointF(0,0);
    m_shear = QPointF(0,0);
    m_center=QPointF(0,0);
    m_polygon = QPolygonF();
    m_dim = QSizeF();
    m_radius = 1;
    m_zindex = 0;
    initShearMatrix(m_shear);
}

KGLBaseItem::~KGLBaseItem()
{
}

void  KGLBaseItem::updateTransform()
{
    m_matrix.setIdentity();

    m_matrix.translate(Eigen::Vector3d(m_position.x() , m_position.y(), 0));

    m_matrix.scale(m_scale);
    m_matrix.translate(Eigen::Vector3d(m_translate.x() , m_translate.y(), 0));

    m_matrix.translate(Eigen::Vector3d(m_rotateCenter.x(), m_rotateCenter.y(), 0));
    m_matrix.rotate(Eigen::AngleAxisd(m_angle, AXIS_Z));
    m_matrix.translate(Eigen::Vector3d(-m_rotateCenter.x() , -m_rotateCenter.y(), 0));



    //    m_shearMatrix(0,1) = m_shear.x();
    //    m_shearMatrix(1,0) = m_shear.y();
    //    m_matrix =   m_matrix* m_shearMatrix ;
}

void KGLBaseItem::resetTransform()
{
    m_matrix.setIdentity();
    m_angle  = 0;
    m_scale  = 1;
    m_shear  = QPointF(0,0);
    m_position = QPointF(0,0);
}

void KGLBaseItem::computeGeometry()
{
    //Compute the center
    m_center = QPointF(0,0);
    foreach(const KGLPoint &p, m_pointList) {
        m_center += QPointF(p.x(), p.y());
    }
    m_center /= (float)pointCount();

    //Compute the Polygon
    m_polygon = QPolygonF();
    foreach(const KGLPoint &p, m_pointList) {
        m_polygon<<QPointF(p.x(), p.y());
    }

    //Compute width and height
    m_dim.setWidth( m_polygon.boundingRect().width());
    m_dim.setHeight(m_polygon.boundingRect().height());

    //Compute the radius of bounding Circle
    const double cx = m_center.x();
    const double px = m_pointList[0].x();
    const double cy = m_center.y();
    const double py = m_pointList[0].y();

    m_radius = sqrt((cx - px) * (cx - px) + (cy - py) * (cy - py));
}

//=======================================================

QPointF KGLBaseItem::transform(const QPointF &p) const
{
    Eigen::Vector3d vect = m_matrix * Eigen::Vector3d(p.x(), p.y(), 0);
    return QPointF(vect.x(), vect.y());
}

//=========================================================

QPolygonF KGLBaseItem::transform(const QPolygonF &p) const
{
    QPolygonF poly;
    foreach(const QPointF &point, p) {
        poly<<transform(point);
    }
    return poly;
}

//=========================================================

QRectF KGLBaseItem::transform(const QRectF &r) const
{
    Eigen::Vector3d a = m_matrix * Eigen::Vector3d(r.x(), r.y(), 0);
    Eigen::Vector3d b = m_matrix * Eigen::Vector3d(r.width(), r.height(), 0);

    return QRectF(a.x(), a.y(), b.x(), b.y());
}

//=========================================================

void KGLBaseItem::createBox(const QSizeF &dim)
{
    clear();
    addVertex( KGLPoint(0, 0, Qt::white, QPointF(0 , 0 )));
    addVertex( KGLPoint(dim.width(), 0, Qt::white, QPointF(1 , 0)));
    addVertex(KGLPoint(dim.width(), dim.height(), Qt::white, QPointF(1 , 1)));
    addVertex(KGLPoint(0, dim.height(), Qt::white, QPointF(0 , 1)));
    computeGeometry();
}

void KGLBaseItem::createPolygon(const QPolygonF &poly)
{
    clear();
    foreach(const QPointF &p, poly) {
        addVertex(KGLPoint(p.x(), p.y() , Qt::white, QPointF(p.x(), p.y())));
    }
    computeGeometry();
}

void KGLBaseItem::createLine(const QLineF &line)
{
    clear();
    addVertex(KGLPoint(line.x1(), line.y1(), Qt::white));
    addVertex(KGLPoint(line.x2(), line.y2(), Qt::white));
    computeGeometry();
}

void KGLBaseItem::initShearMatrix(const QPointF &s)
{
    m_shearMatrix(0,0) = 1;
    m_shearMatrix(0,1) = s.x();
    m_shearMatrix(0,2) = 0;
    m_shearMatrix(0,3) = 0;

    m_shearMatrix(1,0) = s.y();
    m_shearMatrix(1,1) = 1;
    m_shearMatrix(1,2) = 0;
    m_shearMatrix(1,3) = 0;

    m_shearMatrix(2,0) = 0;
    m_shearMatrix(2,1) = 0;
    m_shearMatrix(2,2) = 1;
    m_shearMatrix(2,3) = 0;

    m_shearMatrix(3,0) = 0;
    m_shearMatrix(3,1) = 0;
    m_shearMatrix(3,2) = 0;
    m_shearMatrix(3,3) = 1;
}
