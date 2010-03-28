/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 * Copyright (C) 2010 Arjen Hiemstra <>
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
#ifndef GLUON_GRAPHICS_GLPAINTER_H
#define GLUON_GRAPHICS_GLPAINTER_H

#include <QtCore/QObject>
#include <QtGui/QPainter>
#include <QVector2D>
#include "gluon_graphics_export.h"
#include "texture.h"
#include "vertex.h"


namespace GluonGraphics
{
    class GLPainterPrivate;

    class GLUON_GRAPHICS_EXPORT GLPainter : public QObject
    {
        public:
            GLPainter(QObject * parent = 0);
            ~GLPainter();
            void createRect(const QRectF &rect);
            void createRect(float x, float y, float w, float h);
            void createLine(const QLineF &line);
            void createLine(float x1, float y1, float x2, float y2);
            void createCircle(const QVector2D &center, float radius, float step = 10);
            void createCircle(float cx, float cy, float radius, float step = 10);
            void createPolygon(const QPolygonF & polygon);


            void drawRect(const QRectF &rect);
            void drawRect(float x, float y, float w, float h);
            void drawLine(const QLineF &line);
            void drawLine(float x1, float y1, float x2, float y2);
            void drawPoint(const QVector2D &point);
            void drawPoint(float x, float y);
            void drawCircle(const QVector2D &center, float radius, float step = 10);
            void drawCircle(float cx, float cy, float radius, float step = 10);
            void drawPolygon(const QPolygonF & polygon);

            void setColor(const QColor &col);
            void setLineWidth(float width);
            void setPointSize(float size);
            void setPolygonMode(GLenum mode);

            void draw(GLenum mode = GL_POLYGON);

        private:
            Q_DISABLE_COPY(GLPainter)
            GLPainterPrivate * d;
    };
}//namespace
#endif // GLUON_GRAPHICS_GLPAINTER_H
