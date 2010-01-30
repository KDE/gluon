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

#ifndef GLUON_GRAPHICS_ENGINE_H
#define GLUON_GRAPHICS_ENGINE_H

#include "gluon_graphics_export.h"

#include <QtCore/QObject>
#include <QtCore/QMap>

#include "itemlist.h"

//TODO: Make Singleton class and remove stuff that should not be here
namespace GluonGraphics
{
  class EnginePrivate;

  typedef QMap<unsigned int, ItemList > IndexGroupMap;

class GLUON_GRAPHICS_EXPORT Engine : public QObject
{
    Q_OBJECT

    public:
        Engine(QObject * parent=0);
        ~Engine();

        virtual void mainLoop(float fps=60);
        void addItem(Item* item);
        void addItems(const ItemList &items);
        bool removeItem(Item* item);
        bool removeItems(const ItemList &item);
        virtual bool eraseItem(Item* item);
        bool eraseItems(const ItemList &item);
        Item * itemAt(int id, unsigned int layer=0) const;
        int itemsCount() const;

//         KGLBoxItem * addBox(float w, float h);

        IndexGroupMap items() const;

        virtual void mouseMoved(const QPointF &pos, Qt::MouseButton button);
        virtual void mousePressed(const QPointF &pos, Qt::MouseButton button);
        virtual void mouseReleased(const QPointF &pos,Qt::MouseButton button);
    private:
        Q_DISABLE_COPY(Engine);

        EnginePrivate *d;
};
} //namespace
//@}
#endif // GLUON_GRAPHICS_ENGINE_H
