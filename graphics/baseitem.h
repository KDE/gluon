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

#ifndef GLUON_GRAPHICS_BASEITEM_H
#define GLUON_GRAPHICS_BASEITEM_H

#include <QtCore/QObject>
#include <QtCore/QRectF>
#include <QtCore/QSizeF>
#include <QtGui/QPolygonF>
#include <QtGui/QTransform>
#include <QtGui/QMatrix>

#include <QMatrix4x4>
#include <QVector2D>
#include <QVector3D>
#include <QQuaternion>

#include "gluon_graphics_export.h"
#include "vertex.h"

namespace GluonGraphics
{
class GLUON_GRAPHICS_EXPORT BaseItem: public QObject
{
    Q_OBJECT
public:
    BaseItem(QObject *parent=0);
    ~BaseItem();

    virtual inline void addVertex(const Vertex &p)
    {
        m_vertexList.append(p);
        computeGeometry();
    }

    VertexList &vertexList() {return m_vertexList;}

    virtual void removeVertex(Vertex * p)
    {
        Q_UNUSED(p);
        //            m_vertexList.removeOne (p);
        computeGeometry();
    }

    virtual void clear()
    {
        m_vertexList.clear();

    }

    virtual void updateTransform();
    virtual void resetTransform();

    void applyTransform(const QMatrix4x4 &m)
    {
        m_matrix = m * m_matrix;
    }

    void createBox(const QSizeF &s);
    void createBox(const float &w, const float &h){createBox(QSizeF(w,h));}

    void createPolygon(const QPolygonF &poly);
    void createLine(const QLineF &line);

    //Get
    unsigned int vertexCount() const
    {
        return m_vertexList.size();
    }

    inline QVector3D position() const
    {
        return m_position;
    }

    inline QVector3D scaleValue() const
    {
        return m_scale;
    }

    inline float radius() const
    {
        return m_radius;
    }

    inline QVector3D center() const
    {
        return  m_center;
    }

    inline const QPolygonF viewPolygon() const
    {
        return transform(m_polygon);
    }

    inline const QPolygonF polygon() const
    {
        return m_polygon;
    }

    virtual inline const QRectF boundingBox() const
    {
        return polygon().boundingRect();
    }

    virtual inline const QRectF viewBoundingBox() const
    {
        return viewPolygon().boundingRect();
    }

    inline  bool contains(QPointF &p) const
    {
        return polygon().containsPoint(p,Qt::WindingFill);
    }

    inline  QMatrix4x4 transformMatrix()
    {
        return m_matrix;
    }

    inline void setTransformMatrix(const QMatrix4x4& m)
    {
        m_matrix = m;
    }

    //Set
    inline void setCenter(const QVector3D &c)
    {
        m_center = c;
    }

    inline void setScale(const QVector3D &s)
    {
        m_scale = s;
    }
    inline void setScale(float sx, float sy, float sz)
    {
        setScale(QVector3D(sx, sy, sz));
    }
    
    inline void setPosition(const QVector3D &p)
    {
        m_position = p;
    }

    inline void setPosition(float x, float y, float z)
    {
        setPosition(QVector3D(x, y, z));
    }

    inline void translate(const QVector3D &step)
    {
        m_position += step;
    }

    inline void translate(float x, float y, float z)
    {
        translate(QVector3D(x, y, z));
    }

    inline void scale(const QVector3D &s)
    {
        m_scale = s;
    }
    inline void scale(float x, float y, float z)
    {
        scale(QVector3D(x, y, z));
    }

protected:
    void computeGeometry();
    void initShearMatrix(const QPointF &s);

    QPointF transform(const QPointF &p) const;
    QPolygonF transform(const QPolygonF &p) const;
    QRectF transform(const QRectF &r) const;

private:
    QMatrix4x4 m_matrix;

    QVector3D m_position;
    QVector3D m_scale;
    QQuaternion m_orientation;

    QVector3D m_center;

    QPolygonF m_polygon;
    float m_radius;
    QSizeF m_dim;
    unsigned int m_zindex;
    VertexList m_vertexList;
};

}//namespace

#endif // GLUON_GRAPHICS_BASEITEM_H
