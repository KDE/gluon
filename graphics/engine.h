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

#ifndef GLUONGRAPHICS_ENGINE_H
#define GLUONGRAPHICS_ENGINE_H

#include "gluon_graphics_export.h"
#include <core/singleton.h>

namespace GluonGraphics
{

class Mesh;

    class MaterialInstance;
    class Item;

    /**
     * \brief Main entrypoint for working with Gluon Graphics.
     *
     * This class provides the main entry point for working with
     * classes from Gluon Graphics. It provides factory methods
     * for the most used objects in Gluon Graphics as well as providing
     * a registry of objects.
     *
     * 
     */
    class GLUON_GRAPHICS_EXPORT Engine : public GluonCore::Singleton<Engine>
    {
        Q_OBJECT
        public:
            /**
             * Create an instance of GluonGraphics::Item.
             *
             * \see GluonGraphics::Item
             * 
             * \return The item just created.
             */
            Item * createItem();

            /**
             * Create a mesh.
             *
             * \see GluonGraphics::Mesh
             *
             * \return The mesh just created.
             */
            Mesh* createMesh();
            
            
            /**
             * Create a texture.
             *
             * \see GluonGraphics::Texture
             *
             * \return The texture just created.
             */
            Texture * createTexture();

        public Q_SLOTS:
            void render();
            
        private:
            friend class GluonCore::Singleton<Engine>;

            Engine();
            ~Engine();
            Q_DISABLE_COPY(Engine);

            class EnginePrivate;
            EnginePrivate * const d;
    };
} //namespace

#endif // GLUONGRAPHICS_ENGINE_H
