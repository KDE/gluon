/*
 * This file is part of the KGLEngine2D project.
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

#ifndef GLPOINT_H
#define GLPOINT_H

#include <vector>

#include <QtGui/QColor>
#include <QtCore/QPointF>
#include <QList>

class GLPoint;
typedef QList <GLPoint*> GLPointList;

/**
 * @class GLPoint glpoint.h <GLPoint>
 * @brief This class represents a point, with its color and texture mappings.
 *
 * This class provides an easy-to-use point that represents different things :
 * - A point in the engine, with its coordinates
 * - A point on the texture, (due to openGL texture mapping)
 * - A color for this point to be drawn with
 */
class GLPoint: public QPointF
{
public:
    explicit GLPoint(const QPointF &p, const QColor &c = Qt::white, const QPointF &t = QPointF());
    GLPoint(float x, float y, const QColor &c = Qt::white, const QPointF &t = QPointF());

    /**
     * @return the point of the texture this GLPoint is mapped to.
     */
    inline QPointF tex() {
        return m_tex;
    }

    /**
     * the color of this GLPoint
     */
    inline QColor color() {
        return m_color;
    }

    /**
     * Set the texture point this GLPoint will be mapped to.
     * @param t the coordinates of the texture this point should be mapped to.
     */
    inline void setTex(const QPointF &t) {
        m_tex = t;
    }

    /**
     * Set the color of this GLPoint
     * @param c the color this GLPoint will be drawn with
     */
    inline void setColor(const QColor &c) {
        m_color = c;
    }

    /**
     * Set the alpha level of this GLPoint
     * @param a the alpha level this GLPoint will be drawn with
     */
    inline void setAlpha(int a) {
        m_color.setAlpha(a);
    }

    /**
     * Gets the QPointF inside this GLPoint.
     * @return the QPointF
     */
    inline QPointF toQPointF() {
        return QPointF(x(), y());
    }

private:
    QColor m_color;
    QPointF m_tex;
};

#endif //GLPOINT_H
