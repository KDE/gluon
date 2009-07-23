/*
 * This file is part of the Gluon library.
 * Copyright 2008 Sacha Schutz <istdasklar@free.fr>
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

#ifndef KGLBOXITEM_H
#define KGLBOXITEM_H

#include "kglitem.h"

/**
* @class KGLBoxItem kglboxitem.h <KGLBoxItem>
* This is a KGLItem subclass which can be initialized with a QRectF or QSizeF
*/
class KGLBoxItem : public KGLItem
{
    Q_OBJECT
    public:
        explicit KGLBoxItem(KGLEngine * parent=0);
        explicit KGLBoxItem(const QSizeF &dim,KGLEngine* parent=0);
        explicit KGLBoxItem(const float &w, const float &h, KGLEngine * parent=0);

        void setBox(const QSizeF &dim)
        {
            clear();
            createBox(dim);
            m_dim = dim;
        }
        
        void setBox(const float &w, const float &h)
        {
            clear();
            createBox(w,h);
            m_dim = QSizeF(w,h);
        }

        float width()
        {
            return m_dim.width();
        }
        
        float height()
        {
            return m_dim.height();
        }
        
        QSizeF dim()
        {
            return m_dim;
        }

        QSizeF m_dim;
};

#endif  //KGLBOXITEM_H
