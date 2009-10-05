/*
 * This file is part of the Gluon library.
 * Copyright 2009 Gluon team
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

#ifndef KGLGRIDITEM_H
#define KGLGRIDITEM_H

#include "kgl_export.h"
#include "kglitem.h"
#include <QSizeF>
#include <QList>

/**
 * \defgroup KGL KGL
 */
//@{

class KGL_EXPORT KGLGridItem : public KGLItem
{

    public:
        KGLGridItem(const QSizeF &size, float tile=1, KGLEngine * engine=0);
        KGLGridItem(float width, float height, float tile=1, KGLEngine * engine=0);
        void init();
        void createGrid();
        const KGLPoint * pointAt(const QPoint &p);
        const KGLPoint * pointAt(int x, int y)
        {
            return pointAt(QPoint(x,y));
        }

        inline void setSize(const QSizeF &s)
        {
            m_size = s;
        }

        inline void setTile(const float &t)
        {
            m_tile = t;
        }

    private:
        QSizeF m_size;
        float m_tile;
};

//@}
#endif // KGLGRIDITEM_H
