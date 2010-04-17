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

// WILL BE REPLACE BY QGLTexture!!!!!!!!

#ifndef GLUON_GRAPHICS_TEXTURE_H
#define GLUON_GRAPHICS_TEXTURE_H

#include "gluon_graphics_export.h"

#ifdef Q_WS_WIN
#include <windows.h>
#endif
#ifndef Q_WS_MAC
#include <GL/gl.h>
#else
#include <OpenGL/gl.h>
#endif

#include <QtGui/QPixmap>
#include <QtGui/QImage>

/**
 * \defgroup KGL KGL
 */
//@{
namespace GluonGraphics
{
    class GLUON_GRAPHICS_EXPORT Texture
    {
        public:
            Texture();
            Texture(const QString& fileName);
            Texture(const QImage &img);
            Texture(const QPixmap &pix);
            void setGLTexture(const GLuint& t)
            {
                glDeleteTextures(1, &m_texture);
                m_texture = t;
            }
            ~Texture();
            void bind();
            void unBind();
            void load(const QImage &img, int width = 0, int height = 0);
            void setFilter(GLenum filter);
            void setWrapMode(GLenum coordinate, GLenum mode);
            static int maxSize();
            int size()
            {
                return m_dim.width() * m_dim.height();
            }

            GLuint glId()const
            {
                return m_texture;
            }

            QImage image() const
            {
                return m_img;
            }

            QSizeF dim() const
            {
                return m_dim;
            }

            void setTranslate(const QPointF &t)
            {
                m_translate = t;
            }

            void setRotate(float r)
            {
                m_rotate = r;
            }

            void setScale(const QPointF &s)
            {
                m_scale = s;
            }

            void setScale(float x, float y)
            {
                setScale(QPointF(x, y));
            }

            void translate(const QPointF &t)
            {
                m_translate += t;
            }

            void translate(float x, float y)
            {
                translate(QPointF(x, y));
            }

            void rotate(float r)
            {
                m_rotate += r;
            }

            void scale(const QPointF &s)
            {
                m_scale += s;
            }
            void scale(int x, int y)
            {
                scale(QPointF(x, y));
            }

            void updateTransform();

        protected:
            void init();
        private:
            GLuint m_texture;
            GLenum m_filter;
            QSizeF m_dim;
            QImage m_img;
            QPointF m_translate;
            float m_rotate;
            QPointF m_scale;
    };
}//namespace
//@}
#endif // GLUON_GRAPHICS_TEXTURE_H
