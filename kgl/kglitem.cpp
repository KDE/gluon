/*
 * This file is part of the KGLEngine project.
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
#include "kglitem.h"


void KGLItem::init()
{
    setObjectName(metaObject()->className());
    m_isCreated = false;
    f_showBoundingBox = false;
    f_showCenter = false;
    f_textureEnable = true;
    m_mode = GL_POLYGON;
    m_color = Qt::white;
    m_alpha = 1;
    m_texture = new KGLTexture;
    m_program = new KGLProgram;
    m_GLCallList = glGenLists(1);
    m_texRepeat = QPointF(1,1);
    resetTransform();

}
KGLItem::KGLItem(KGLEngine* parent)
            :KGLBaseItem()
{
    init();
}


KGLItem::KGLItem(const QPolygonF &poly, KGLEngine * parent)
           :KGLBaseItem()
{
    init();
    setObjectName(metaObject()->className());
    createPolygon(poly);
}

KGLItem::KGLItem(const QSizeF &box , KGLEngine * parent)
         :KGLBaseItem()
{
    init();
    setObjectName(metaObject()->className());

    createBox(box);

}


KGLItem::KGLItem(const QLineF &line, KGLEngine * parent)
         :KGLBaseItem()
{
    init();
    setObjectName(metaObject()->className());
    setMode(GL_LINES);
    createLine(line);
}

KGLItem::~KGLItem()
{
    delete m_texture;
    delete m_program;
    glDeleteLists(m_GLCallList,1);

}
void KGLItem::draw()
{
    if (!m_isCreated)
        create();
    if ( f_showBoundingBox) drawBoundingBox();

    m_texture->updateTransform();

    glPushMatrix();
    glLoadMatrixd(matrix().data());
  if ( f_textureEnable)
     m_texture->bind();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);
    glEnable(GL_POLYGON_SMOOTH);

    if ( program()->isValid())
        program()->bind();

    glCallList(m_GLCallList);  //CALL THE LIST

    program()->unbind();
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    m_texture->unBind();
    glDepthMask(GL_TRUE);

    glPopMatrix();

}
void  KGLItem::create()
{
    if (m_GLCallList != 0)
        glDeleteLists(m_GLCallList, 1);
    glNewList(m_GLCallList, GL_COMPILE);
    glBegin(m_mode);

    foreach(GLPoint* p, vertexList())
    {
        drawGLPoint(p);
    }
    glEnd();

    if ( f_showCenter) drawCenter();

    glEndList();
    m_isCreated = true;
}

void KGLItem::drawGLPoint(GLPoint *p)
{
    glTexCoord2f(p->tex().x(), p->tex().y());
    const float r = (float)p->color().red() / 255;
    const float g = (float)p->color().green() / 255;
    const float b = (float)p->color().blue() / 255;
    const float a = (float)p->color().alpha() / 255;
    glColor4f(r, g, b, a);
    glVertex2d(p->x(), p->y());


}

void KGLItem::drawBoundingBox()
{
    glBegin(GL_LINE_LOOP);
    QRectF rectAround = boundingBox();
    glColor3f(100, 100, 100);
    glVertex2d(rectAround.x(), rectAround.y());
    glVertex2d(rectAround.x() + rectAround.width(), rectAround.y());
    glVertex2d(rectAround.x() + rectAround.width(), rectAround.y() + rectAround.height());
    glVertex2d(rectAround.x(), rectAround.y() + rectAround.height());
    glEnd();
}



void KGLItem::setColor(const QColor &c)
{
    m_color = c;
    foreach(GLPoint* p, vertexList()) {
        p->setColor(c);
    }
    m_isCreated = false;
}

void KGLItem::setAlpha(const float &a)
{
    m_alpha = a;

    foreach(GLPoint* p, vertexList()) {
        p->setAlpha((int)(a*255));
    }
    m_isCreated = false;
}

void KGLItem::drawCenter()
{
    glPointSize(3);
    glBegin(GL_POINTS);
    QPointF c = itemCenter();
    glColor3f(100, 0, 0);
    glVertex2d(c.x(), c.y());
    glEnd();
    glColor3f(100, 100, 100);
    glPointSize(1);

}

//==================KGLPolygonItem ===================

