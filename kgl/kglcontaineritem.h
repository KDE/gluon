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

#ifndef KGLCONTAINERITEM_H
#define KGLCONTAINERITEM_H

#include "kglitem.h"
#include "kglitemlist.h"
#include <QDataStream>

#include <KDE/KDebug>

/**
 * \defgroup KGL KGL
 */
//@{

class KGLContainerItem: public KGLItem
{
    Q_OBJECT
    public:
        KGLContainerItem(QObject * parent=0);
        virtual ~KGLContainerItem();

        virtual void draw();

        void addChild(KGLItem* item);
        inline void eraseChild(KGLItem *item)
        {
            m_children.removeOne(item);
        }

        inline const KGLItemList childItems() const
        {
            return m_children;
        }

    protected:
        KGLItemList m_children;
};

//@}
#endif //KGLCONTAINERITEM_H
