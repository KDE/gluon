/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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
#ifndef Transform_H
#define Transform_H
#include <QMatrix4x4>
#include <QVector3D>
#include <QVector2D>
#include <QQuaternion>
#include <QSizeF>
#include <QObject>
#include <QPolygonF>
#include <QRectF>
#include "gluon_graphics_export.h"



namespace GluonGraphics
{
    class GLUON_GRAPHICS_EXPORT Transform : public QObject
    {
        public:
            Transform(QObject * parent = 0);
            virtual void updateTransform();
            virtual void resetTransform();
            void applyTransform(const QMatrix4x4 &m);
            QMatrix4x4 matrix();
            void setMatrix(const QMatrix4x4& m);
            void setScale(const QVector3D &s);
            void setScale(float sx, float sy, float sz);
            void setScale(float sx, float sy);
            void setScale(const QVector2D &s);

            void setPosition(const QVector3D &p);
            void setPosition(float x, float y, float z);
            void setPosition(float x, float y);
            void setPosition(const QVector2D &p);

            QVector3D position() const;
            
            void setQuaternion(const QQuaternion &orientation);
            void setRotation(const qreal &angle, const QVector3D &axis);
            void setRotation(const qreal &angle, const QVector2D &center);
            void setRotation(const qreal &angle);

            void translate(const QVector3D &step);
            void translate(float x, float y, float z);
            void translate(float x, float y);
            void translate(const QVector2D &step);

            void scale(const QVector3D &s);
            void scale(float x, float y, float z);
            void scale(float x, float y);
            void scale(const QVector2D &s);

            QVector3D transform(const QVector3D &p) ;
            QVector2D transform(const QVector2D &p) ;
            QPolygonF transform(const QPolygonF &p) ;
            QRectF transform(const QRectF &r) ;

        private:
            QMatrix4x4 m_matrix;

            QVector3D m_position;
            QVector3D m_scale;
            qreal m_angle;
            QQuaternion m_orientation;


    };
}//namespace
#endif // Transform_H
