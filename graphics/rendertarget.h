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

#ifdef Q_OS_WIN
#include <windows.h>
#include <GL/glee.h>
#endif

#include <QtOpenGL/QGLFramebufferObject>

namespace GluonGraphics
{
    class MaterialInstance;

    /**
     * A surface to render to.
     *
     * The render target class describes a single target for rendering.
     * The target is most of the time a Frame Buffer Object, but this
     * class can take any texture and render it to screen. By default,
     * the target is "renderable", that is, its contents can be directly
     * rendered to screen. Use setRenderable(false) to disable it in case
     * the
     *
     * Note that this class always renders its target as a 1x1 full
     * screen quad.
     */
    class GLUON_GRAPHICS_EXPORT RenderTarget : public QObject
    {
        Q_OBJECT
        public:
            /**
             * Default constructor.
             */
            explicit RenderTarget( QObject* parent = 0 );
            /**
             * Construct a rendertarget with a given size. This will create
             * a Framebuffer Object with the given size for this rendertarget.
             *
             * \param width The width of the rendertarget.
             * \param height The height of the rendertarget.
             */
            RenderTarget(int width, int height, QObject* parent = 0);
            virtual ~RenderTarget();

            /**
             * Can this render target be rendered to screen directly?
             *
             * \return True if the render target can be rendered to screen
             * directly. False if otherwise.
             */
            bool isRenderable() const;

            /**
             * Retrieve the current framebuffer object.
             *
             * \return The current framebuffer object for this render target.
             */
            QGLFramebufferObject* framebufferObject() const;

            /**
             * Bind this render target, so that the next calls issues by the
             * rest of the system will be rendered to this target. This only
             * works if a Framebuffer Object has been set for this target.
             */
            void bind();

            /**
             * Release the render target, causing all following calls to be
             * rendered directly to screen.
             */
            void release();

            /**
             * Retrieve the MaterialInstance used to render this RenderTarget.
             *
             * \return The MaterialInstance used for rendering this RenderTarget.
             */
            MaterialInstance* materialInstance();

        public Q_SLOTS:
            /**
             * Set whether this render target can be rendered to screen
             * directly. If render is true, the render target will contain
             * surface data for rendering.
             *
             * \param render True to set the render target to be renderable,
             * false to disable this.
             */
            void setRenderable( bool render );

            /**
             * Set the framebuffer object this RenderTarget should use.
             *
             * \param fbo The new framebuffer object to use.
             */
            void setFramebufferObject(QGLFramebufferObject* fbo);

            /**
             * Resize the RenderTarget and any attached framebuffers and
             * textures.
             *
             * \param width The new width of the RenderTarget.
             * \param height The new height of the RenderTarget.
             */
            void resize(int width, int height);

            /**
             * Set the material instance that will be used to render this render
             * target.
             *
             * \param material The material instance to be used for rendering.
             */
            void setMaterialInstance(MaterialInstance* material);

            /**
             * Render this render target to screen. This will only do
             * something if renderable == true.
             */
            void render();

        Q_SIGNALS:
            void framebufferChanged();

        private:
            class Private;
            Private* const d;
    };

}

#endif // GLUONGRAPHICS_RENDERTARGET_H
