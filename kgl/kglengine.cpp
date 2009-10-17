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

#include "kglengine.h"
#include "kglengine_p.h"

#include "kglboxitem.h"

#include <QDebug>

KGLEngine::KGLEngine(QObject * parent)
    : QObject(parent)
{
    d = new KGLEnginePrivate();
}

KGLEngine::~KGLEngine()
{
    delete d;
}

void KGLEngine::mainLoop(float ff)
{
}

void KGLEngine::addItem(KGLItem* item)
{
    qDebug() << "adding Item of type: " << item->objectName()<<"-"<<item->zindex();
    d->m_items[item->zindex()].append(item);
    item->setParent(this);
}

void KGLEngine::addItems(const KGLItemList &items)
{
    foreach(KGLItem* item, items) {
        addItem(item);
        item->setParent(this);
    }
}

bool KGLEngine::removeItem(KGLItem* item)
{
    if ( item != NULL)
        return d->m_items[item->zindex()].removeOne(item);
    else return false;
}

bool KGLEngine::removeItems(const KGLItemList &items)
{
    foreach ( KGLItem* item , items)
    {
        if (!removeItem(item))
            return false;
        else return true;
    }
    return true;
}

bool KGLEngine::eraseItem(KGLItem* item)
{
    if ( removeItem(item))
    {
        delete item;
        return true;
    }
    else return false;
}

KGLItem *KGLEngine::itemAt( int id, unsigned int layer) const
{
    if ( id < d->m_items[layer].size())
        return d->m_items[layer].at(id);

    else return NULL;

}

bool KGLEngine::eraseItems(const KGLItemList &items)
{
    foreach(KGLItem* item, items) {
        if (!eraseItem(item)) return false;
        else return true;
    }
    return true;
}

int KGLEngine::itemsCount() const
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

KGLBoxItem *KGLEngine::addBox(float w, float h)
{
    KGLBoxItem * b = new KGLBoxItem(w,h);
    addItem(b);
    return b;
}

IndexGroupMap KGLEngine::items() const
{
    return d->m_items;
}

void KGLEngine::mouseMoved(const QPointF &pos, Qt::MouseButton button)
{}

void KGLEngine::mousePressed(const QPointF &pos, Qt::MouseButton button)
{}

void KGLEngine::mouseReleased(const QPointF &pos, Qt::MouseButton button)
{}
