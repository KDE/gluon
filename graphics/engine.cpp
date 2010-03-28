/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 * Copyright (C) 2010 Arjen Hiemstra <>
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

using namespace GluonGraphics;

template<> Engine *GluonCore::Singleton<Engine>::m_instance = 0;

class Engine::EnginePrivate
{
    public:
        EnginePrivate()
        {
            activeCamera = 0;
        }

        ItemList items;
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

void Engine::addItems(const ItemList &items)
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

bool Engine::removeItems(const ItemList &items)
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

bool Engine::eraseItems(const ItemList &items)
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

ItemList Engine::items() const
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

#include "engine.moc"
