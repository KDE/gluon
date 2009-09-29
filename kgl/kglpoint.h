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

#ifndef KGLPoint_H
#define KGLPoint_H

#include <vector>

#include <QtGui/QColor>
#include <QtCore/QPointF>
#include <QList>
#include <QVector>

/**
 * \defgroup KGL KGL
 */
//@{

#define KGLPOINT_PARAM_NUMBER 8

class KGLPoint;
class KGLPointList;

class KGLPoint
{
public:
    explicit KGLPoint();
    explicit KGLPoint(const QPointF &p, const QColor &c = Qt::white, const QPointF &t = QPointF());
    explicit KGLPoint(float x, float y, const QColor &c = Qt::white, const QPointF &t = QPointF());

    inline QPointF tex() const{
        return QPointF(m_tx,m_ty);
    }

    inline QColor color() const{
        QColor c;
        c.setRgbF(m_r,m_g,m_b,m_a);
        return c;
    }

    inline void setTex(const QPointF &t) {
        m_tx = t.x();
        m_ty = t.y();
    }

    inline void setColor(const QColor &c) {
        m_r = c.redF();
        m_g = c.greenF();
        m_b = c.blueF();
        m_a = c.alphaF();
    }

    inline void setAlpha(float a) {
        m_a = a;
    }

    inline QPointF toQPointF() {
        return QPointF(m_x, m_y);
    }

    inline void setX(float x)
    {
        m_x = x;
    }
    inline void setY(float y)
    {
        m_y = y;
    }
    inline float x()const
    {
        return m_x;
    }

    inline float y()const
    {
        return m_y;
    }

    inline float red()const
    {
        return m_r;
    }

    inline float green()const
    {
        return m_g;
    }

    inline float blue()const
    {
        return m_b;
    }

    inline float alpha()const
    {
        return m_a;
    }

    inline float texCoordX()const
    {
        return m_tx;
    }

    inline float texCoordY()const
    {
        return m_ty;
    }
//DO NOT CHANGE ORDER OF MEMBER VARIABLE!!!!! It's necessary for the openGL Vertex buffer array
private:
    float m_x;
    float m_y;
    float m_r;
    float m_g;
    float m_b;
    float m_a;
    float m_tx;
    float m_ty;
};

class KGLPointList : public QVector <KGLPoint>
{
public:
    KGLPointList();

    float * array()
    {
        return (float*)data();
    }

    float *vertexStart()
    {
        return array();
    }

    float *colorStart()
    {
        return &(array())[2];
    }

    float *texCoordStart()
    {
        return &(array())[6];
    }
};

//@}
#endif //KGLPoint_H
