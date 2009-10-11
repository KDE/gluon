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

#ifndef KGLENGINE_H
#define KGLENGINE_H

#include <QObject>
#include <QMap>

#include "kgl_export.h"
#include "kglbaseitem.h"
#include "kglitemlist.h"
#include "kglitem.h"
#include "kglboxitem.h"
#include "kgltextitem.h"

/**
 * \defgroup KGL KGL
*/
//@{

typedef QMap<unsigned int, KGLItemList > IndexGroupMap;

class KGLPhysicsEngine;

class KGL_EXPORT KGLEngine : public QObject
{
    Q_OBJECT
    public:
        KGLEngine(QObject * parent=0);
        virtual void mainLoop(float fps=60);
        void addItem(KGLItem* item);
        void addItems(const KGLItemList* items);
        bool removeItem(KGLItem* item);
        bool removeItems(const KGLItemList *item);
        virtual bool eraseItem(KGLItem* item);
        bool eraseItems(const KGLItemList *item);
        KGLItem * itemAt(int id, unsigned int layer=0) const;
        int itemsCount() const;

        KGLBoxItem * addBox(float w, float h)
        {
            KGLBoxItem * b = new KGLBoxItem(w,h); addItem(b); return b;
        }

        IndexGroupMap items() const
        {
            return m_items;
        }

        virtual void mouseMoved(const QPointF &pos, Qt::MouseButton button);
        virtual void mousePressed(const QPointF &pos, Qt::MouseButton button);
        virtual void mouseReleased(const QPointF &pos,Qt::MouseButton button);
    private:
        Q_DISABLE_COPY(KGLEngine);
        
        IndexGroupMap m_items;

};

//@}
#endif // KGLENGINE_H
