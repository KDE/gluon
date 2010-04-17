/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "engine.h"
#include "camera.h"

#include <QtCore/QDebug>

#include "item.h"

using namespace GluonGraphics;

template<> Engine *GluonCore::Singleton<Engine>::m_instance = 0;

class Engine::EnginePrivate
{
    public:
        EnginePrivate()
        {
            activeCamera = 0;
        }

        QList<Item*> items;
        
        Camera* activeCamera;
};

Engine::Engine()
{
    d = new EnginePrivate();
}

Engine::~Engine()
{
    delete d;
}

void Engine::addItem(Item* item)
{
    d->items.append(item);
    item->setParent(this);
}

void Engine::addItems(const QList<Item*> &items)
{
    foreach(Item* item, items)
    {
        addItem(item);
    }
}

bool Engine::removeItem(Item* item)
{
    if (item != NULL)
        return d->items.removeOne(item);
    else return false;
}

bool Engine::removeItems(const QList<Item*> &items)
{
    bool retVal = true;
    foreach(Item* item , items)
    {
        if (!removeItem(item))
            retVal = false;
    }
    return retVal;
}

bool Engine::eraseItem(Item* item)
{
    if (removeItem(item))
    {
        delete item;
        return true;
    }
    else return false;
}

Item *Engine::itemAt(int id) const
{
    return d->items.at(id);
}

bool Engine::eraseItems(const QList<Item*> &items)
{
    bool retVal = true;
    foreach(Item* item, items)
    {
        if (!eraseItem(item))
            retVal = false;
    }
    return retVal;
}

int Engine::itemsCount() const
{
    return d->items.size();
}

QList<Item*> Engine::items() const
{
    return d->items;
}

Camera* Engine::activeCamera()
{
    return d->activeCamera;
}

void Engine::setActiveCamera(Camera* camera)
{
    d->activeCamera = camera;

    emit activeCameraChanged(camera);
}

void Engine::sortItems()
{
    qStableSort(d->items.begin(), d->items.end(), Engine::compareDepth);
}

bool Engine::compareDepth(const GluonGraphics::Item* left, const GluonGraphics::Item* right)
{
    return left->position().z() < right->position().z();
}

#include "engine.moc"
