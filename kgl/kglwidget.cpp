/*
 * This file is part of the KGLWidget project.
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

#include "kglwidget.h"

#include <stdlib.h>
#include <algorithm>

#include <QtGlobal>
#include <QFile>

#include <KDebug>

using namespace std;
using namespace Eigen;

KGLWidget::KGLWidget(QWidget * parent)
    :QGLWidget(parent)
{
    initalize();
    resize(640,480);
}
KGLWidget::KGLWidget(QSize size, float frameRate,QWidget *parent)
    :QGLWidget(parent)
{
    initalize();
    resize(size);
    m_frameRate = frameRate;
}

void KGLWidget::initalize()
{
    m_frameRate = 16.6;
    m_timer = new QTimer(this);
    m_fpsTimer = new QTimer(this);
    m_countFrame = 0;
    m_fps = 1000/m_frameRate;
    m_sleep=true;
    m_hasAxis = false;
    m_hasFps = false;
    m_ratio = width() / height();
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
    setAutoBufferSwap(true);
    setOrthoView(-100,100,-100,100);
    glInit();
    initGlew();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(mainLoop()));
    connect(m_fpsTimer, SIGNAL(timeout()), this, SLOT(calculFps()));

//    ctx = glcGenContext();
//    glcContext(ctx);

}

KGLWidget::~KGLWidget()
{

    //delete all child automatica
}


void KGLWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA ,GL_ONE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
    setAutoBufferSwap (true);



}
 bool KGLWidget::initGlew()
 {
     GLenum code;
     kDebug()<<"Glew initialisation....";
     /* initialisation de GLEW */
     code = glewInit();
     if(code != GLEW_OK)
     {
         kDebug()<< "cannot init GLEW :"<<glewGetErrorString(code);
         return false;
     }
     kDebug()<<"Glew success...";
     return true;
 }
void KGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawGLItems();

    if (m_hasAxis)
        drawRepere(4,4);

    if (m_hasFps) {
        renderText(50, 50, "fps : " + QString::number(m_fps), QFont("Times", 10, 10, false), 2000);
        renderText(50, 60, "fff : " + QString::number(100 / m_fps), QFont("Times", 10, 10, false), 2000);
    }

//
//    GLint myFont;
//
//myFont = glcGenFontID();
//glcNewFontFromFamily(myFont, "Palatino"); // Select the family of my font
//glcFontFace(myFont, "Bold"); // Select the face of my font
//glcFont(myFont);
//glPushMatrix();
//glcLoadIdentity();
//glcScale(10.f, 10.f);
//glcRotate(4.6);
//glColor3f(1.f, 0.f, 0.f);
//glRasterPos2f(-100, 0);
//glcRenderString("Hello world!");
//glPopMatrix();




    QGLWidget::paintGL();
}

void KGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(m_orthoView.left(),m_orthoView.right() ,m_orthoView.bottom(), m_orthoView.top());


}

void KGLWidget::drawRepere(float scalex, float scaley) // a modifier
{
    glPushMatrix();


    glScalef(scalex, scaley,0);
    renderText(1,0,0,"X");
    renderText(-1,1,0,"Y");
    glBegin(GL_LINES);
    glColor3ub(255, 0, 0);
    glVertex2d(0, 0);
    glColor3ub(255, 0, 0);
    glVertex2d(1, 0);
    glColor3ub(0, 255, 0);
    glVertex2d(0, 0);
    glColor3ub(0, 255, 0);
    glVertex2d(0, 1);
    glEnd();
    glPopMatrix();
}

void KGLWidget::drawGLPoint(GLPoint *p)
{
    const float r = (float)p->color().red() / 255;
    const float g = (float)p->color().green() / 255;
    const float b = (float)p->color().blue() / 255;
    const float a = (float)p->color().alpha() / 255;
    glBegin(GL_POINTS);
    glColor4f(r, g, b, a);
    glVertex2d(p->x(), p->y());
    glColor4f(1, 1, 1, 1);
    glEnd();
}

void KGLWidget::drawCross(float x, float y)
{
    glBegin(GL_LINES);
    glColor3ui(100, 100, 100);
    glVertex2d(x - 0.025, y);
    glVertex2d(x + 0.025, y);
    glVertex2d(x, y - 0.025);
    glVertex2d(x, y + 0.025);

    glEnd();
}

void KGLWidget::drawRectangle(const QRectF &rect)
{
    glBegin(GL_LINE_LOOP);
    glColor3f(100, 100, 100);
    glVertex2d(rect.x(), rect.y());
    glVertex2d(rect.x() + rect.width(), rect.y());
    glVertex2d(rect.x() + rect.width(), rect.y() + rect.height());
    glVertex2d(rect.x(), rect.y() + rect.height());
    glEnd();
}

void KGLWidget::drawPolygon(const QPolygonF &polygon)
{
    glBegin(GL_LINE_LOOP);

    glColor3f(100, 100, 100);
    foreach(const QPointF &p, polygon) {
        glVertex2d(p.x(), p.y());
    }

    glEnd();
}

void KGLWidget::drawGLItems() const
{
    IndexGroupMap::const_iterator i = m_items.constBegin();
    while (i != m_items.constEnd())
    {
        KGLItem * it;
        foreach ( it, i.value())
        {
            it->draw();
        }
        ++i;
    }
}
void KGLWidget::mainLoop()
{
    updateGL();
    m_countFrame++;
}

void KGLWidget::addItem(KGLItem* item)
{
    kDebug() << "adding Item of type: " << item->objectName()<<"-"<<item->zindex();
    m_items[item->zindex()].append(item);
    item->setParent(this);
}
//
void KGLWidget::addItems(const KGLItemList* items)
{
    foreach(KGLItem* item, *items) {
        addItem(item);
        item->setParent(this);
    }
}
bool KGLWidget::removeItem(KGLItem* item)
{
    if ( item != NULL)
        return m_items[item->zindex()].removeOne(item);
    else return false;
}

bool KGLWidget::removeItems(const KGLItemList *items)
{

    foreach ( KGLItem* item , *items)
    {
        if (!removeItem(item))
            return false;
        else return true;
    }

    return true;
}

bool KGLWidget::eraseItem(KGLItem* item)
{
    if ( removeItem(item))
    {
        delete item;
        return true;
    }
    else return false;
}
KGLItem *KGLWidget::itemAt( int id, unsigned int layer)
{
    if ( id < m_items[layer].size())
        return m_items[layer].at(id);

    else return NULL;

}
bool KGLWidget::eraseItems(const KGLItemList *items)
{
    foreach(KGLItem* item, *items) {
        if (!eraseItem(item)) return false;
        else return true;
    }
    return true;
}

int KGLWidget::itemsCount() const
{
    int size=0;
    IndexGroupMap::const_iterator i = m_items.constBegin();
    while (i != m_items.constEnd()) {
        size+=i.value().size();
        ++i;
    }
    kDebug()<<"size="<<size;
    return size;
}
void KGLWidget::kglDebug(QString txt)
{
    kDebug()<<txt;
    m_debugList<<txt;
}

    KGLItemList KGLWidget::itemList()
    {
KGLItemList list;
 IndexGroupMap::const_iterator i = m_items.constBegin();
    while (i != m_items.constEnd())
    {
        foreach ( KGLItem * it, i.value())
        {
          list.append(it);
        }
          ++i;
    }
    return list;
}
//====================================================
QStandardItemModel *KGLWidget::getStandardItemModel()
{
    QStandardItemModel * model = new QStandardItemModel;

    IndexGroupMap::const_iterator i = m_items.constBegin();
    while (i != m_items.constEnd())
    {
        QStandardItem * layer = new QStandardItem("layer-"+QString::number(i.key()));

        foreach ( KGLItemBase * it, i.value())
        {
            layer->appendRow( new QStandardItem(it->objectName()));
        }
        model->appendRow (layer);
        ++i;
    }
    return model;
}
