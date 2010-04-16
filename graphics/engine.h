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

#ifndef GLUON_GRAPHICS_ENGINE_H
#define GLUON_GRAPHICS_ENGINE_H

#include "gluon_graphics_export.h"

#include <QtCore/QObject>
#include <QtCore/QMap>

#include <core/singleton.h>

namespace GluonGraphics
{
    class Camera;
    class Item;

    class GLUON_GRAPHICS_EXPORT Engine : public GluonCore::Singleton<Engine>
    {
            Q_OBJECT

        public:
            void addItem(Item* item);
            void addItems(const QList<Item*> &items);
            bool removeItem(Item* item);
            bool removeItems(const QList< GluonGraphics::Item* >& items);
            virtual bool eraseItem(Item* item);
            bool eraseItems(const QList< GluonGraphics::Item* >& items);
            Item * itemAt(int id) const;
            int itemsCount() const;

            QList<Item*> items() const;

            Camera* activeCamera();
            
            void sortItems();
            
            static bool compareDepth(const GluonGraphics::Item* left, const GluonGraphics::Item* right);

        public slots:
            void setActiveCamera(GluonGraphics::Camera* camera);

        signals:
            void activeCameraChanged(GluonGraphics::Camera*);

        private:
            friend class GluonCore::Singleton<Engine>;

            Engine();
            ~Engine();
            Q_DISABLE_COPY(Engine);

            class EnginePrivate;
            EnginePrivate *d;
    };
} //namespace

#endif // GLUON_GRAPHICS_ENGINE_H
