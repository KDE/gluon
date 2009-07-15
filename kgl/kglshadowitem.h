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

#ifndef KGLSHADOWITEM_H
#define KGLSHADOWITEM_H

#include "kglitem.h"

#include <Eigen/Geometry>

#include <QList>
#include <QTimer>



class KGLShadowItem : public KGLItem
{
    Q_OBJECT
public :
    KGLShadowItem(KGLItem * item = 0);

public Q_SLOTS:
    void snapMatrix();
    void enable(bool t = 1) {
        if (t) m_timer->start(m_snapDuration); else m_timer->stop();
    }
    void draw();
    void setSnapDuration(float d) {
        m_snapDuration = d; m_timer->start(m_snapDuration);
    }
    void setNbFrame(float d);

private:
    KGLItem* m_parentItem;
    unsigned int m_snapDuration;
    unsigned int m_nbFrame;
    unsigned int m_currentFrame;
    QList <Eigen::Transform3d> m_listMatrix;
    QList <KGLItem*> m_listItem;
    QList <float> m_listAlpha;
    QTimer *m_timer;

};

#endif // KGLSHADOWITEM_H
