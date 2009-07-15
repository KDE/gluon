/*
 * This file is part of the KGLEngine2D project.
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

#include "kglshadowitem.h"
#include <QDebug>

KGLShadowItem::KGLShadowItem(KGLItem * item)
        : KGLItem()
{
    m_parentItem = item;
    m_snapDuration = 20;
    m_nbFrame = 10;
    m_currentFrame = 0;
    m_timer = new QTimer;
    setNbFrame(m_nbFrame);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(snapMatrix()));
}

void KGLShadowItem::snapMatrix()
{
    m_listMatrix.append(m_parentItem->matrix());
    m_listAlpha.append(1);

    m_currentFrame++;
    if (m_currentFrame > m_nbFrame) {
        m_listMatrix.removeFirst();
        m_listAlpha.removeFirst();
    }
}

void KGLShadowItem::draw()
{
    for (int i = 0; i < m_listAlpha.size(); ++i) {
        m_listAlpha[i] -= 2 / m_nbFrame;
        if (m_listAlpha[i] < 0) m_listAlpha[i] = 0;
    }

    m_parentItem->setZIndex(0);

    for (int i = 0; i < m_listMatrix.size(); ++i) {
        m_listItem[i]->resetTransform();
        m_listItem[i]->applyTransform(m_listMatrix[i]);

        m_listItem[i]->setAlpha(m_listAlpha[i]);
        m_listItem[i]->draw();
    }
}

void KGLShadowItem::setNbFrame(float d)
{
    m_nbFrame = d;
    m_listItem.clear();
    for (unsigned int i = 0; i < m_nbFrame; ++i) {
        KGLItem * item= m_parentItem->clone();
      
        m_listItem.append(item);
    }
}
