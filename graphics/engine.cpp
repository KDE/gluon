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

#include "engine.h"
#include "engine_p.h"



#include <QtCore/QDebug>
namespace GluonGraphics
{
Engine::Engine(QObject * parent)
    : QObject(parent)
{
    d = new EnginePrivate();
}

Engine::~Engine()
{
    delete d;
}

void Engine::mainLoop(float ff)
{
}

void Engine::addItem(Item* item)
{
    qDebug() << "adding Item of type: " << item->objectName()<<"-"<<item->zindex();
    d->m_items[item->zindex()].append(item);
    item->setParent(this);
}

void Engine::addItems(const ItemList &items)
{
    foreach(Item* item, items) {
        addItem(item);
        item->setParent(this);
    }
}

bool Engine::removeItem(Item* item)
{
    if ( item != NULL)
        return d->m_items[item->zindex()].removeOne(item);
    else return false;
}

bool Engine::removeItems(const ItemList &items)
{
    foreach ( Item* item , items)
    {
        if (!removeItem(item))
            return false;
        else return true;
    }
    return true;
}

bool Engine::eraseItem(Item* item)
{
    if ( removeItem(item))
    {
        delete item;
        return true;
    }
    else return false;
}

Item *Engine::itemAt( int id, unsigned int layer) const
{
    if ( id < d->m_items[layer].size())
        return d->m_items[layer].at(id);

    else return NULL;

}

bool Engine::eraseItems(const ItemList &items)
{
    foreach(Item* item, items) {
        if (!eraseItem(item)) return false;
        else return true;
    }
    return true;
}

int Engine::itemsCount() const
{
    int size=0;
    IndexGroupMap::const_iterator i = d->m_items.constBegin();
    while (i != d->m_items.constEnd()) {
        size+=i.value().size();
        ++i;
    }
    qDebug()<<"size="<<size;
    return size;
}

// KGLBoxItem *Engine::addBox(float w, float h)
// {
//     KGLBoxItem * b = new KGLBoxItem(w,h);
//     addItem(b);
//     return b;
// }

IndexGroupMap Engine::items() const
{
    return d->m_items;
}

void Engine::mouseMoved(const QPointF &pos, Qt::MouseButton button)
{}

void Engine::mousePressed(const QPointF &pos, Qt::MouseButton button)
{}

void Engine::mouseReleased(const QPointF &pos, Qt::MouseButton button)
{}
} //namespace
#include "engine.moc"
