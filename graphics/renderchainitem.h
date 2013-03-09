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

class QMatrix4x4;

namespace GluonGraphics
{
    /**
     * \brief Abstract base class for objects that want to participate in the render chain.
     *
     *
     */
    class GLUON_GRAPHICS_EXPORT RenderChainItem
    {
        public:
            RenderChainItem();
            virtual ~RenderChainItem();

            virtual void renderContents() = 0;
            virtual void resize( int width, int height ) = 0;

            float zDepth() const;
            void setZDepth( float z );

            RenderChainItem* parentItem() const;
            void setParentItem( RenderChainItem* parent );

        private:
            class Private;
            Private* const d;
    };
}

#endif // GLUONGRAPHICS_RENDERABLE_H
