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

#include "kglanimitem.h"
#include "kglengine2d.h"

#include <KDebug>

#include <QTimeLine>

KGLAnimItem::KGLAnimItem(const GLint &texture, const int &nbFrame, const int &duration, const QSizeF &) :
        KGLItem()
{
    setObjectName(metaObject()->className());
    m_timeLine = new QTimeLine(duration, this);
    m_timeLine->setEndFrame(nbFrame);
    m_timeLine->setLoopCount(0);
    m_timeLine->setFrameRange(0, nbFrame);
    m_timeLine->setDuration(duration);

    init();
    setTexture(texture);

    connect(m_timeLine, SIGNAL(frameChanged(int)), this, SLOT(createFrame(int)));
    m_timeLine->start();
}

void KGLAnimItem::createFrame(int id)
{
    //One picture, with many picture's frame inside. This fonction select which frame will be drawn.
    int nbFrame = m_timeLine->endFrame();

    if (id > nbFrame) {
        kWarning() << "KGLAnimItem: frame selected is out of range";
        return;
    }

    const double pal = 1. / nbFrame;
    const double y1 = ((id - 1) * pal);
    const double y2 = id * pal;
    m_points[0]->setTex(QPointF(0, y1));
    m_points[1]->setTex(QPointF(0, y2));
    m_points[2]->setTex(QPointF(1, y1));
    m_points[3]->setTex(QPointF(1, y2));
}
