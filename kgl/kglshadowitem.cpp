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

#include "kglshadowitem.h"
#include <QDebug>

KGLShadowItem::KGLShadowItem(KGLItem * item)
    : KGLItem()
{
    m_parentItem = item;
    m_snapDuration = 20;
    m_nbFrame = 20;
    m_currentFrame = 0;
    m_timer = new QTimer;
    setNbFrame(m_nbFrame);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(snapMatrix()));
}

KGLShadowItem::~KGLShadowItem()
{
    delete m_timer;
}

void KGLShadowItem::snapMatrix()
{



    m_listMatrix.append(m_parentItem->matrix());
    m_listAlpha.append(255);

    m_currentFrame++;
    if (m_currentFrame > m_nbFrame) 
    {
        m_listMatrix.removeFirst();
        m_listAlpha.removeFirst();
    }
}

void KGLShadowItem::paintGL()
{

 
    for (int i = 0; i < m_listAlpha.size(); ++i)
    {
        m_listAlpha[i] -= 255 / (float)(m_nbFrame);
        if (m_listAlpha[i] < 0) m_listAlpha[i] = 0;
    }
    m_parentItem->setZIndex(0);
    for (int i = 0; i < m_listMatrix.size(); ++i)
    {
        m_listItem[i]->resetTransform();
        m_listItem[i]->applyTransform(m_listMatrix[i]);
        m_listItem[i]->setColor(QColor(255,255,255,30));


        m_listItem[i]->paintGL();
    }
}

void KGLShadowItem::setNbFrame(float d)
{
    m_nbFrame = d;
    m_listItem.clear();
    for (unsigned int i = 0; i < m_nbFrame; ++i) 
    {
        KGLItem * item= m_parentItem->clone();

        m_listItem.append(item);
    }
}
