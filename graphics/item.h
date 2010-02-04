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

#ifndef GLUON_GRAPHICS_ITEM_H
#define GLUON_GRAPHICS_ITEM_H

#include <QDebug>

#include "gluon_graphics_export.h"

#include "fx.h"
#include "baseitem.h"
#include "texture.h"
#include "glpainter.h"


/**
 * \defgroup KGL KGL
 */
//@{

namespace GluonGraphics
{
    class Engine;

class GLUON_GRAPHICS_EXPORT Item : public BaseItem
{
    Q_OBJECT
    public:
        Item();
        explicit Item(const QPolygonF& poly);
        explicit Item(const QSizeF& box);
        explicit Item(const QLineF& line);
        ~Item();

        virtual void paintGL();
        virtual void updateTransform();

        Item *clone();

        void recreate()
        {
            m_isCreated=false;
        }

        void addChildItem(Item* item)
        {
            m_childItems.append(item);
        }

        void remChildItem(Item * item)
        {
            m_childItems.removeOne(item);
        }

    //Set
        void setMode(GLenum m)
        {
            m_mode=m;
        }

        void setTexture(const GLuint& t)
        {
            m_texture->setGLTexture(t);
        }

        void setTexture(Texture *t)
        {
            m_texture = t;
        }

        void setTexture(const QString& fileName)
        {
            m_texture = new Texture(fileName);
        }

        void setTexture(const QImage& image)
        {
            m_texture = new Texture(image);
        }

        void setTexture(const QPixmap &pix)
        {
            m_texture = new Texture(pix);
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

#ifndef Q_WS_WIN
        void setShaderFx(Program * s)
        {
            m_shaderFx = s;
        }
#endif

        Texture * texture()
        {
            return m_texture;
        }

#ifndef Q_WS_WIN
        Program * shaderFx()
        {
            return m_shaderFx;
        }
#endif

        //Get
        const QColor &color()
        {
            return m_color;
        }

        const float &alpha()
        {
            return m_alpha;
        }

        QList<Item*> childItems()
        {
            return m_childItems;
        }

    signals:
        void painted();

    protected:

        void drawChild();
        void init();
        virtual void drawGLPoint(Vertex &p);
        virtual void drawBoundingBox();
        virtual void drawCenter();

    private:
        int m_GLCallList;
        bool m_isCreated;
        QPointF m_texRepeat;
        QColor m_color;
        float m_alpha;
        GLenum m_mode;
        Texture *m_texture;
#ifndef Q_WS_WIN
        Program * m_shaderFx;
#endif
        QList<Item*> m_childItems;
        bool m_shaderEnable;

        //Flags.....
        bool f_showBoundingBox;
        bool f_showCenter;
        bool f_textureEnable;
        GLPainter * m_painter ;
    };
}//namespace
//@}
#endif // GLUON_GRAPHICS_KGLITEM2_H
