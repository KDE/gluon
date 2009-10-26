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

#ifndef KGLSHADOWITEM_H
#define KGLSHADOWITEM_H

#include "kgl_export.h"
#include "kglitem.h"

#ifdef Q_WS_WIN
#include <eigen2/Eigen/Geometry>
#else
#include <Eigen/Geometry>
#endif

#include <QtCore/QList>
#include <QtCore/QTimer>

/**
 * \defgroup KGL KGL
 */
//@{

class KGL_EXPORT KGLShadowItem : public KGLItem
{
    Q_OBJECT
    public :
        KGLShadowItem(KGLItem * item = 0);
        ~KGLShadowItem();

    public Q_SLOTS:
        void snapMatrix();

        void enable(bool t = 1)
        {
            if (t)
            {
                m_timer->start(m_snapDuration);
            }
            else
            {
                m_timer->stop();
            }
        }

        void paintGL();

        void setSnapDuration(float d) {
            m_snapDuration = d;
            m_timer->start(m_snapDuration);
        }

        void setNbFrame(float d);

    private:
        Q_DISABLE_COPY(KGLShadowItem)
        
        KGLItem* m_parentItem;
        unsigned int m_snapDuration;
        unsigned int m_nbFrame;
        unsigned int m_currentFrame;
        QList <Eigen::Transform3d> m_listMatrix;
        QList <KGLItem*> m_listItem;
        QList <float> m_listAlpha;
        QTimer *m_timer;
};

//@}
#endif // KGLSHADOWITEM_H
