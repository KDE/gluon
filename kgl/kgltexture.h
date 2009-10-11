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

#ifndef KGLTEXTURE_H
#define KGLTEXTURE_H

#include <GL/glew.h>
#include <QPixmap>
#include <QImage>

#include "kgl_export.h"
/**
 * \defgroup KGL KGL
 */
//@{

class KGL_EXPORT KGLTexture
{
public:
    KGLTexture();
    KGLTexture (const QString& fileName);
    KGLTexture ( const QImage &img);
    KGLTexture(const QPixmap &pix);
    void setGLTexture(const GLuint& t){
       glDeleteTextures(1,&m_texture);
        m_texture = t;
    }
    ~KGLTexture();
    void bind();
    void unBind();
    void load(const QImage &img, int width=0, int height=0);
    void setFilter(GLenum filter);
    void setWrapMode(GLenum coordinate, GLenum mode);
    static int maxSize();
    int size(){
     return m_dim.width() * m_dim.height(); 
    }

    GLuint glId()const{
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
        m_rotate= r;
    }

    void setScale(const QPointF &s)
    {
        m_scale = s;
    }

    void setScale(float x,float y){
      setScale(QPointF(x,y));
    }

    void translate(const QPointF &t)
    {
        m_translate += t;
    }

    void translate( float x, float y){
      translate(QPointF(x,y));
    }

    void rotate(float r)
    {
        m_rotate += r;
    }

    void scale(const QPointF &s)
    {
        m_scale+=s;
    }
    void scale(int x,int y){
        scale(QPointF(x,y));
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

//@}
#endif // KGLTEXTURE_H
