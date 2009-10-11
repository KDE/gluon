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

#ifndef KGLBASEITEM_H
#define KGLBASEITEM_H
#include <QObject>
#include <Eigen/Geometry>
#include <QRectF>
#include <QPolygonF>
#include <QTransform>
#include <QSizeF>
#include <QMatrix>

#include "kgl_export.h"
#include "kglpoint.h"

/**
 * \defgroup KGL KGL
 */
//@{

const Eigen::Vector3d AXIS_X(1, 0, 0);
const Eigen::Vector3d AXIS_Y(0, 1, 0);
const Eigen::Vector3d AXIS_Z(0, 0, 1);

class KGL_EXPORT KGLBaseItem: public QObject
{
    Q_OBJECT
public:
    KGLBaseItem(QObject *parent=0);
    ~KGLBaseItem();

    virtual inline void addVertex(const KGLPoint &p)
    {
        m_pointList.append(p);
        computeGeometry();
    }

    KGLPointList &pointList() {return m_pointList;}

    virtual void removeVertex(KGLPoint * p)
    {
        //            m_pointList.removeOne (p);
        computeGeometry();
    }

    virtual void clear()
    {
        m_pointList.clear();

    }

    virtual void updateTransform();
    virtual void resetTransform();

    void applyTransform(const Eigen::Transform3d &m)
    {
        m_matrix = m * m_matrix;
    }

    void createBox(const QSizeF &s);
    void createBox(const float &w, const float &h){createBox(QSizeF(w,h));}

    void createPolygon(const QPolygonF &poly);
    void createLine(const QLineF &line);

    //Get
    unsigned int pointCount() const
    {
        return m_pointList.size();
    }

    inline const QPointF &position() const
    {
        return m_position;
    }

    inline const QPointF &scaleValue() const
    {
        return m_scale;
    }
    inline const QPointF &translateValue() const
    {
        return m_translate;
    }
    inline const float &angle() const
    {
        return m_angle;
    }

    inline const float &radius() const
    {
        return m_radius;
    }

    inline unsigned int zindex() const
    {
        return m_zindex;
    }

    inline const QPointF viewCenter()
    {
        return transform(m_center);
    }

    inline const QPointF &center() const
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

    inline  Eigen::Transform3d& matrix()
    {
        return m_matrix;
    }

    inline void setMatrix(const Eigen::Transform3d& m)
    {
        m_matrix = m;
    }

    //Set
    inline void setCenter(const QPointF &c)
    {
        m_center = c;
    }

    inline void setAngle(const float &a, const QPointF &c = QPointF(0,0))
    {
        m_rotateCenter = c;m_angle = a;
    }

    inline void setScale(const QPointF &s)
    {
        m_scale = s;
    }
    inline void setScale(const float &sx, const float &sy)
    {
        setScale(QPointF(sx,sy));
    }
    inline void setTranslate(const QPointF &t)
    {
        m_translate = t;
    }
    inline void setPosition(const QPointF &p)
    {
        m_position = p;


    }

    inline void setPosition(qreal x, qreal y )
    {
        setPosition(QPointF(x,y));
    }

    inline void setShear(const QPointF &s)
    {
        m_shear = s;
    }

    inline void setShear(const float &sx, const float &sy)
    {
        setShear(QPointF(sx,sy));
    }

    inline void setZIndex(int i)
    {
        m_zindex = i;
    }

    inline void translate(const QPointF &step)
    {
        m_translate+=step;
    }

    inline void translate(const float &x,const float &y)
    {
        translate(QPointF(x,y));
    }

    inline void scale(const QPointF &s)
    {
        m_scale.setX(m_scale.x() *s.x());
        m_scale.setY( m_scale.y() *s.y());
    }
    inline void scale(const float &x, const float&y )
    {
        scale(QPointF(x,y));
    }

    inline void rotate(const float &angle)
    {
        m_angle += angle;
    }

    inline void shear(const QPointF &s)
    {
        m_shear+=s;
    }

    inline void shear(const float &sx,const float &sy)
    {
        shear(QPointF(sx,sy));
    }

protected:
    void computeGeometry();
    void initShearMatrix(const QPointF &s);

    QPointF transform(const QPointF &p) const;
    QPolygonF transform(const QPolygonF &p) const;
    QRectF transform(const QRectF &r) const;

private:
    Eigen::Transform3d m_matrix;
    Eigen::Matrix4d m_shearMatrix;

    float m_angle;
    QPointF m_scale;
    QPointF m_position;
    QPointF m_translate;
    QPointF m_rotateCenter;
    QPointF m_shear;
    QPointF m_center;
    QPolygonF m_polygon;
    float m_radius;
    QSizeF m_dim;
    unsigned int m_zindex;
    KGLPointList m_pointList;
};

//@}
#endif // KGLBASEITEM_H
