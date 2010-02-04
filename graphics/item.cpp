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

#include "item.h"

#include <QtCore/QDebug>

#include "engine.h"

using namespace GluonGraphics;

Item::Item()
{
    init();
}

Item::Item(const QPolygonF &poly)
    : BaseItem()
{
    init();
    setObjectName(metaObject()->className());
    createPolygon(poly);
}

Item::Item(const QSizeF &box)
    : BaseItem()
{
    init();
    setObjectName(metaObject()->className());

    createBox(box);
}

Item::Item(const QLineF &line)
    : BaseItem()
{
    init();
    setObjectName(metaObject()->className());
    setMode(GL_LINES);
    createLine(line);
}

Item::~Item()
{
    delete m_texture;
// #ifndef Q_WS_WIN
//     delete m_shaderFx;
// #endif
//     glDeleteLists(m_GLCallList,1);

}

void Item::init()
{
    Engine::instance()->addItem(this);

    m_painter = new GLPainter;
    setObjectName(metaObject()->className());
    f_showBoundingBox = false;
    f_showCenter = false;
    f_textureEnable = true;
    m_mode = GL_POLYGON;
    m_color = Qt::white;
    m_alpha = 1;
    m_texture = new Texture;
    //     m_texRepeat = QPointF(1,1);
    // #ifndef Q_WS_WIN
    //     m_shaderFx = NULL;
    // #endif
    m_isCreated = false;
    resetTransform();
}

Item *Item::clone()
{

    Item * newItem = new Item;
    newItem->setTexture(texture());
    newItem->setMatrix(matrix());
    newItem->setPosition(position());

    foreach(const Vertex &p, vertexList()) {
        newItem->addVertex(p);
    }

    return newItem;
}

void Item::paintGL()
{
  if (!m_isCreated)
  {
    m_painter->createRect(polygon().boundingRect());
    m_isCreated=true;
  }

  glPushMatrix();
  glMultMatrixf(matrix().data());

   if ( f_showBoundingBox) drawBoundingBox();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);
    //Disabled until necessary, causes diagonal lines on ATI cards.
    //glEnable(GL_POLYGON_SMOOTH);


     m_texture->bind();
     m_painter->draw();
     m_texture->unBind();

    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);

    glDepthMask(GL_TRUE);
    glPopMatrix();

    drawChild();

// qDebug()<<"Test";
//     if (!m_isCreated)
//         create();
//     if ( f_showBoundingBox) drawBoundingBox();
//
//     m_texture->updateTransform();
//
//     glPushMatrix();
//     glMultMatrixf(matrix().data());
//
// //     m_texture->bind();
//     glEnable(GL_BLEND);
//     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//     glDepthMask(GL_FALSE);
//     //Disabled until necessary, causes diagonal lines on ATI cards.
//     //glEnable(GL_POLYGON_SMOOTH);
//
// #ifndef Q_WS_WIN
//     if ( m_shaderFx != NULL ){
//         if (shaderFx()->isValid())
//             shaderFx()->bind();
//     }
// #endif
//
//     glCallList(m_GLCallList);  //CALL THE LIST
//
// #ifndef Q_WS_WIN
//     if ( m_shaderFx != NULL ){
//         shaderFx()->unbind();
//     }
// #endif
//
//     glDepthMask(GL_TRUE);
//     glDisable(GL_BLEND);
// //     m_texture->unBind();
//     glDepthMask(GL_TRUE);
//
// if ( f_showCenter) drawCenter();
// glPopMatrix();
//
//     drawChild();
//   emit painted();
}


void Item::updateTransform()
{
    BaseItem::updateTransform();
    if ( m_childItems.size()>0)
    {
        foreach(Item* item, m_childItems)
            item->applyTransform(matrix());
    }
}

void Item::drawChild()
{
    if ( m_childItems.size()>0)
    {
        foreach(Item* item, m_childItems)
        {
            item->paintGL();
        }
    }
}

void Item::drawGLPoint(Vertex &p)
{
    glTexCoord2f(p.texCoordX(), p.texCoordY());

    glColor4f(p.red(), p.green(), p.blue(), p.alpha());
    glVertex2d(p.x(), p.y());
}

void Item::drawBoundingBox()
{
  //must be replace by glpaint
    glBegin(GL_LINE_LOOP);
    QRectF rectAround = viewBoundingBox();
    glColor3f(100, 100, 100);
    glVertex2d(rectAround.x(), rectAround.y());
    glVertex2d(rectAround.x() + rectAround.width(), rectAround.y());
    glVertex2d(rectAround.x() + rectAround.width(), rectAround.y() + rectAround.height());
    glVertex2d(rectAround.x(), rectAround.y() + rectAround.height());
    glEnd();
}

void Item::setColor(const QColor &c)
{
    m_color=c;
    m_painter->setColor(c);
    m_isCreated = false;
}

void Item::setAlpha(const float &a)
{
    m_alpha = a;
    m_color.setAlphaF(a);
    m_painter->setColor(m_color);
    m_isCreated = false;
}

void Item::drawCenter()
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

#include "item.moc"
