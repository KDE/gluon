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

#include "kgltexture.h"
#include <KDebug>

void KGLTexture::init()
{
    m_dim = QSizeF();
    m_texture = 0;

    m_translate = QPointF(0,0);
    m_rotate = 0;
    m_scale = QPointF(1,1);
    kDebug()<<"init texture";
}

KGLTexture::KGLTexture()
{
    init();
}

KGLTexture::KGLTexture(const QString& fileName)
{
    init();
    load(QImage(fileName));
}

KGLTexture::KGLTexture ( const QImage &img)
{
    init();
    load(img);
}

KGLTexture::KGLTexture(const QPixmap &pix)
{
    init();
    load(pix.toImage());
}

KGLTexture::~KGLTexture()
{
    glDeleteTextures(1, &m_texture);
}

void KGLTexture::load(const QImage &img, int width, int height)
{
    kDebug()<<"load texture";
    if (img.isNull()) {
        kDebug()<<"cannot load Texture. QImage is emply";
        return;
    }

    QImage image = img.convertToFormat(QImage::Format_ARGB32);

    image = image.mirrored(0,1); // Reverse the picture!Otherwise the texture will be reverse

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

    //glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void KGLTexture::updateTransform()
{
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glTranslatef(m_translate.x(),m_translate.y(),0);
    glRotatef(m_rotate,0,0,1);
    glScalef(m_scale.x(), m_scale.y(),1);
    glMatrixMode(GL_MODELVIEW);
}

void KGLTexture::bind()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

void KGLTexture::unBind()
{
    glDisable(GL_TEXTURE_2D);
}
