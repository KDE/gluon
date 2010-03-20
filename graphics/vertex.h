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

#ifndef GLUON_GRAPHICS_VERTEX_H
#define GLUON_GRAPHICS_VERTEX_H

#include <QtGui/QColor>
#include <QVector2D>
#include <QVector3D>
#include <QtCore/QVector>

#include "gluon_graphics_export.h"



/**
 * @brief Vertex represents an openGL point with 3d coordination, color and texture coordinate.
 *It used is @ref VertexList and @ref VertexBufferArray
 *It will probably be replaced by Qt4.6 feature.....
 **/


namespace GluonGraphics
{
    class Vertex;
    class VertexList;

    class GLUON_GRAPHICS_EXPORT Vertex
    {
        public:
            explicit Vertex();
            explicit Vertex(const QVector2D &p, const QColor &c = Qt::white, const QVector2D &t = QVector2D());
            explicit Vertex(const QVector3D &p, const QColor &c = Qt::white, const QVector2D &t = QVector2D());
            explicit Vertex(float x, float y, const QColor &c = Qt::white, const QVector2D &t = QVector2D());
            explicit Vertex(float x, float y, float z, const QColor &c = Qt::white, const QVector2D &t = QVector2D());

            inline QVector2D tex() const
            {
                return QVector2D(m_tx, m_ty);
            }

            inline QColor color() const
            {
                QColor c;
                c.setRgbF(m_r, m_g, m_b, m_a);
                return c;
            }

            inline void setTex(const QVector2D &t)
            {
                m_tx = t.x();
                m_ty = t.y();
            }

            inline void setColor(const QColor &c)
            {
                m_r = c.redF();
                m_g = c.greenF();
                m_b = c.blueF();
                m_a = c.alphaF();
            }

            inline void setAlpha(float a)
            {
                m_a = a;
            }


            inline void setX(float x)
            {
                m_x = x;
            }
            inline void setY(float y)
            {
                m_y = y;
            }

            inline void setZ(float z)
            {
                m_z = z;
            }

            inline float x()const
            {
                return m_x;
            }

            inline float y()const
            {
                return m_y;
            }

            inline float z()const
            {
                return m_z;
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
            float m_z;
            float m_r;
            float m_g;
            float m_b;
            float m_a;
            float m_tx;
            float m_ty;
    };

    class VertexList : public QVector <Vertex>
    {
        public:
            VertexList();

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
                return &(array())[3];
            }

            float *texCoordStart()
            {
                return &(array())[7];
            }
    };
} //namespace
//@}
#endif //GLUON_GRAPHICS_VERTEX_H
