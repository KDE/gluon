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

#include "kglitem.h"
#include <KDebug>

#include <iostream>
using namespace std;

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
    m_GLCallList = glGenLists(1);
    m_texRepeat = QPointF(1,1);
    m_program = NULL;
    resetTransform();
}

KGLItem::KGLItem(KGLEngine* parent)
    : KGLBaseItem()
{
    init();
}

KGLItem::KGLItem(const QPolygonF &poly, KGLEngine * parent)
    : KGLBaseItem()
{
    init();
    setObjectName(metaObject()->className());
    createPolygon(poly);
}

KGLItem::KGLItem(const QSizeF &box , KGLEngine * parent)
    : KGLBaseItem()
{
    init();
    setObjectName(metaObject()->className());

    createBox(box);
}

KGLItem::KGLItem(const QLineF &line, KGLEngine * parent)
    : KGLBaseItem()
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

KGLItem *KGLItem::clone()
{

    KGLItem * newItem = new KGLItem;
    newItem->setTexture(texture());
    newItem->setMatrix(matrix());
 newItem->setPosition(position());
    foreach(KGLPoint p, pointList())
    newItem->addVertex(p);

    return newItem;
}

void KGLItem::paintGL()
{
    if (!m_isCreated)
        create();
    if ( f_showBoundingBox) drawBoundingBox();

    m_texture->updateTransform();

    glPushMatrix();
    glLoadMatrixd(matrix().data());

    m_texture->bind();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);
    //Disabled until necessary, causes diagonal lines on ATI cards.
    //glEnable(GL_POLYGON_SMOOTH);

    if ( m_program != NULL ){
        if ( program()->isValid())
            program()->bind();
    }

    glCallList(m_GLCallList);  //CALL THE LIST

    if ( m_program != NULL ){
        program()->unbind();
    }

    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    m_texture->unBind();
    glDepthMask(GL_TRUE);

if ( f_showCenter) drawCenter();
glPopMatrix();

    drawChild();
  emit painted();
}

void  KGLItem::create()
{
    if (m_GLCallList != 0)
    {
        glDeleteLists(m_GLCallList, 1);
    }
    glNewList(m_GLCallList, GL_COMPILE);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    /* envoie des donnees */
    glVertexPointer(2, GL_FLOAT,sizeof(KGLPoint),pointList().vertexStart());
    glTexCoordPointer(2,GL_FLOAT,sizeof(KGLPoint),pointList().texCoordStart());
    glColorPointer(4, GL_FLOAT,sizeof(KGLPoint),pointList().colorStart());

//    /* rendu indice */
    glDrawArrays(m_mode, 0, pointList().size());

    /* desactivation des tableaux de sommet */
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    if (f_showCenter) 
    {
        drawCenter();
    }
    glEndList();
    m_isCreated = true;
}

void KGLItem::updateTransform()
{
    KGLBaseItem::updateTransform();
    if ( m_childItems.size()>0)
    {
        foreach(KGLItem* item, m_childItems)
            item->applyTransform(matrix());
    }
}

void KGLItem::drawChild()
{
    if ( m_childItems.size()>0)
    {
        foreach(KGLItem* item, m_childItems)
        {
            item->paintGL();
        }
        }
}

void KGLItem::drawGLPoint(KGLPoint &p)
{
    glTexCoord2f(p.texCoordX(), p.texCoordY());

    glColor4f(p.red(), p.green(), p.blue(), p.alpha());
    glVertex2d(p.x(), p.y());
}

void KGLItem::drawBoundingBox()
{
    glBegin(GL_LINE_LOOP);
    QRectF rectAround = viewBoundingBox();
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
    for ( int i=0; i<pointList().size();++i)
        pointList()[i].setColor(c);
    m_isCreated = false;
}

void KGLItem::setAlpha(const float &a)
{
    m_alpha = a;

    foreach(KGLPoint p, pointList()) {
        p.setAlpha(a);
    }
    m_isCreated = false;
}

void KGLItem::drawCenter()
{
    glPointSize(3);
    glBegin(GL_POINTS);
    QPointF c = center();
    glColor3f(100, 0, 0);
    glVertex2d(c.x(), c.y());
    glEnd();
    glColor3f(100, 100, 100);
    glPointSize(1);
}
