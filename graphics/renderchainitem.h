/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2012 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#ifndef GLUONGRAPHICS_RENDERABLE_H
#define GLUONGRAPHICS_RENDERABLE_H

#include "gluon_graphics_export.h"

namespace GluonGraphics
{
    /**
     * Interface for objects that want to participate in the render chain.
     *
     * The render chain is a tree of objects that output a single image to be composited
     * together into one final image. This includes elements like the "view" of a camera,
     * interface elements rendered using QtQuick and separate render targets to handle things
     * like reflections. Render chain items are sorted by Z depth, with lower Z being
     * rendered before higher.
     *
     * Note that render chain items and entities are separate concepts. Render chain items
     * define a set of layers that make up a 2D surface. Entities are objects in 3D space
     * that can be rendered to a surface. It is in fact possible for an object to be both
     * a render chain item and an entity, see for example the Camera class.
     */
    class GLUON_GRAPHICS_EXPORT RenderChainItem
    {
        public:
            RenderChainItem();
            virtual ~RenderChainItem();

            /**
             * Render the contents of this item.
             */
            virtual void renderContents() = 0;
            /**
             * Resize the contents of the item so they fit within width and height.
             */
            virtual void resize( int width, int height ) = 0;

            /**
             * \return The Z depth of this item.
             */
            float zDepth() const;
            /**
             * Set the Z depth of this item.
             */
            void setZDepth( float z );

            /**
             * \return The parent item of this item.
             */
            RenderChainItem* parentItem() const;
            /**
             * Set the parent item of this item.
             */
            void setParentItem( RenderChainItem* parent );

        private:
            class Private;
            Private* const d;
    };
}

#endif // GLUONGRAPHICS_RENDERABLE_H
