/*****************************************************************************
 * This file is part of the Gluon Development Platform
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

#ifndef GLUONGRAPHICS_RENDERTARGET_H
#define GLUONGRAPHICS_RENDERTARGET_H

#include "gluon_graphics_export.h"
#include <QtOpenGL/QGLFramebufferObject>

namespace GluonGraphics
{
    /**
     * A surface to render to.
     *
     * The render target class describes a single surface to render to.
     * It extends QGLFramebufferObject with facilities to make the rendering
     * of the FBO's surface more easy, as well as provide a means to apply
     * shaders for filtering.
     */
    class GLUON_GRAPHICS_EXPORT RenderTarget : public QGLFramebufferObject
    {
        public:
            RenderTarget();
            virtual ~RenderTarget();

            /**
             * Can this render target be rendered to screen directly?
             *
             * \return True if the render target can be rendered to screen
             * directly. False if otherwise.
             */
            bool isRenderable();

        public Q_SLOTS:
            /**
             * Set whether this render target can be rendered to screen
             * directly. If render is true, the render target will contain
             * surface data for rendering.
             *
             * \param render True to set the render target to be renderable,
             * false to disable this.
             */
            void setRenderable(bool render);
    };

}

#endif // GLUONGRAPHICS_RENDERTARGET_H
