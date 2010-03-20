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

#include <core/singleton.h>
#include "itemlist.h"

namespace GluonGraphics
{
    class Camera;

    class GLUON_GRAPHICS_EXPORT Engine : public GluonCore::Singleton<Engine>
    {
            Q_OBJECT

        public:
            void addItem(Item* item);
            void addItems(const ItemList &items);
            bool removeItem(Item* item);
            bool removeItems(const ItemList &item);
            virtual bool eraseItem(Item* item);
            bool eraseItems(const ItemList &item);
            Item * itemAt(int id) const;
            int itemsCount() const;

            ItemList items() const;

            Camera* activeCamera();

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
