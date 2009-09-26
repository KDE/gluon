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

#include "kglintroitem.h"
#include <KDebug>
#include <KIcon>
KGLIntroItem::KGLIntroItem(KGLEngine* parent)
    : KGLItem(parent)
{

    m_item = new KGLPixmapItem(KIcon("gluon.png").pixmap(256,256));

    m_shadow = new KGLShadowItem(m_item);
    m_shadow->enable(true);
    m_shadow->setNbFrame(20);
    addChildItem(m_shadow);

    m_timeLine = new QTimeLine(2000, this);
    m_timeLine->setFrameRange(0, 360);

    m_timeLine->setCurveShape(QTimeLine::EaseInOutCurve);
    connect( m_timeLine, SIGNAL(frameChanged(int)), this, SLOT(anim(int)));
    connect(m_timeLine,SIGNAL(finished()),m_timeLine,SLOT(toggleDirection()));
    connect(m_timeLine,SIGNAL(finished()),m_timeLine,SLOT(resume()));
    m_timeLine->start();
        m_item->setColor(QColor(255,255,255,20));
}

void KGLIntroItem::anim(int id)
{
 m_item->setPosition(position());
  m_item->setAngle(id*M_PI/360,m_item->center());
  m_item->updateTransform();
}


