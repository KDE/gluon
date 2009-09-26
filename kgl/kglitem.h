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

#ifndef KGLITEM2_H
#define KGLITEM2_H
#include <GL/glew.h>


#include "kglbaseitem.h"
#include "kgltexture.h"
#include "kglprogram.h"

/**
 * \defgroup KGL KGL
 */
//@{

class KGLEngine;
class KGLItem;

class KGLItem : public KGLBaseItem
{
    Q_OBJECT
    public:
        virtual void paintGL();
        virtual void updateTransform();
        explicit KGLItem(KGLEngine * parent=0);
        explicit KGLItem(const QPolygonF &poly, KGLEngine * parent=0);
        explicit KGLItem(const QSizeF &box, KGLEngine * parent=0);
        explicit KGLItem(const QLineF &line,KGLEngine * parent=0);
        KGLItem *clone();

        void addChildItem(KGLItem* item)
        {
            m_childItems.append(item);
        }

        void remChildItem(KGLItem * item)
        {
            m_childItems.removeOne(item);
        }

        ~KGLItem();

    //Set
        void setMode(GLenum m)
        {
            m_mode=m;
        }

        void setTexture(const GLuint& t)
        {
            m_texture->setGLTexture(t);
        }

        void setTexture(KGLTexture *t)
        {
            m_texture = t;
        }

        void setTexture(const QString& fileName)
        {
            m_texture = new KGLTexture(fileName);
        }

        void setTexture(const QImage& image)
        {
            m_texture = new KGLTexture(image);
        }

        void setTexture(const QPixmap &pix)
        {
            m_texture = new KGLTexture(pix);
        }

        void setColor(const QColor &c);
        void setAlpha(const float &a);

        void showBoundingBox(bool b)
        {
            f_showBoundingBox = b;
            m_isCreated=false;
        }

        void showCenter(bool b)
        {
            f_showCenter = b;
            m_isCreated=false;
        }

        void setTextureEnable(bool t)
        {
            f_textureEnable = t;
        }

        void setProgram(KGLProgram * p)
        {
            m_program = p;
        }

        KGLTexture * texture()
        {
            return m_texture;
        }

        KGLProgram * program()
        {
            return m_program;
        }


        //Get
        const QColor &color()
        {
            return m_color;
        }

        const float &alpha()
        {
            return m_alpha;
        }

        QList<KGLItem*> childItems()
        {
            return m_childItems;
        }

    signals:
        void painted();

    protected:
        virtual void create();
        void drawChild();
        void init();
        virtual void drawGLPoint(KGLPoint &p);
        virtual void drawBoundingBox();
        virtual void drawCenter();

    private:
        int m_GLCallList;
        bool m_isCreated;
        QPointF m_texRepeat;
        QColor m_color;
        float m_alpha;
        GLenum m_mode;
        KGLTexture *m_texture;
        KGLProgram * m_program;
        QList<KGLItem*> m_childItems;
        bool m_shaderEnable;

        //Flags.....
        bool f_showBoundingBox;
        bool f_showCenter;
        bool f_textureEnable;
};

//@}
#endif // KGLITEM2_H
