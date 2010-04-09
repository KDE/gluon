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

#include "texture.h"
#include <QtCore/QDebug>
#include <QtCore/QFile>
namespace GluonGraphics
{
    void Texture::init()
    {
        m_dim = QSizeF();
        m_texture = 0;

        m_translate = QPointF(0, 0);
        m_rotate = 0;
        m_scale = QPointF(1, 1);
    }

    Texture::Texture()
    {
        init();
    }

    Texture::Texture(const QString& fileName)
    {
        init();

        if (!QFile::exists(fileName))
        {
            return;
        }
        load(QImage(fileName));
    }

    Texture::Texture(const QImage &img)
    {
        init();
        load(img);
    }

    Texture::Texture(const QPixmap &pix)
    {
        init();
        load(pix.toImage());
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &m_texture);
    }

    void Texture::load(const QImage &img, int width, int height)
    {
        if (img.isNull())
        {
            qDebug() << "cannot load Texture. QImage is empty";
            return;
        }

        QImage image = img.convertToFormat(QImage::Format_ARGB32);

        //image = image.mirrored(0, 1); // Reverse the picture!Otherwise the texture will be reverse

        if (width <= 0)
            width = image.width();
        if (height <= 0)
            height = image.height();
        if (width != image.width() || height != image.height())
            image = image.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

        m_dim = image.size();
        m_img = image;
        glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture);

        glTexImage2D(GL_TEXTURE_2D,        //TYPE
                     0,                   //Mipmap
                     4,                   //Color
                     image.width(),       //width
                     image.height(),      //height
                     0,                   //border width
                     GL_BGRA,            //FORMAT
                     GL_UNSIGNED_BYTE,   //Color type
                     image.bits());      //image bits

        setFilter(GL_LINEAR);
        setWrapMode(GL_TEXTURE_WRAP_S, GL_REPEAT);
        setWrapMode(GL_TEXTURE_WRAP_T, GL_REPEAT);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::updateTransform()
    {
        glMatrixMode(GL_TEXTURE);
        glLoadIdentity();
        glTranslatef(m_translate.x(), m_translate.y(), 0);
        glRotatef(m_rotate, 0, 0, 1);
        glScalef(m_scale.x(), m_scale.y(), 1);
        glMatrixMode(GL_MODELVIEW);
    }

    void Texture::bind()
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, m_texture);

    }

    void Texture::unBind()
    {
        glDisable(GL_TEXTURE_2D);
    }
    void Texture::setFilter(GLenum filter)
    {
        bind();
        GLenum magfilter = (filter == GL_NEAREST) ? GL_NEAREST : GL_LINEAR;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magfilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
        unBind();

    }
    void Texture::setWrapMode(GLenum coordinate, GLenum mode)
    {
        bind();
        glTexParameteri(GL_TEXTURE_2D, coordinate, mode);
        unBind();
    }
    int Texture::maxSize()
    {
        GLint texSize;
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &texSize);

        return texSize;

    }
}
