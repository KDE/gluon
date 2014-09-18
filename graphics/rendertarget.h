/*****************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010-2012 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include <QtCore/QObject>

#include "gluon_graphics_export.h"
#include "renderchainitem.h"

class QColor;
namespace GluonGraphics
{
    class MaterialInstance;
    class Texture;
    class TextureData;

    /**
     * A texture to render to.
     *
     * The render target class describes a single target for rendering.
     * The target is most of the time a Frame Buffer Object, but this
     * class can take any texture and render it to screen. Note that if the
     * render target should be used for off-screen rendering it should not be
     * included in the render chain directly.
     *
     * The render target is the only "container class" in the render chain.
     * That is, the render target can compose render chain items together to
     * form a single image, but most other items cannot or will need special
     * handling. The render target will bind itself, then call renderContents()
     * on all children and finally release itself. It will then have the composited
     * result of the rendered children as contents, which can be rendered to screen
     * or to a different render target.
     *
     * \note This class always renders its contents as a 1x1 full
     * screen quad.
     *
     * \sa RenderChainItem
     */
    class GLUON_GRAPHICS_EXPORT RenderTarget : public QObject, public RenderChainItem
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
            RenderTarget( int width, int height, QObject* parent = 0 );
            virtual ~RenderTarget();

            /**
             * Bind this render target, so that the next draw calls issued by the
             * rest of the system will be rendered to this target. This only
             * works if a Framebuffer Object has been set for this target.
             */
            virtual void bind() = 0;

            /**
             * Release the render target, causing all following calls to be
             * rendered directly to screen.
             */
            virtual void release() = 0;

            /**
             * Add an item to be rendered onto this render target.
             *
             * \param item The item to add.
             */
            void addChild( RenderChainItem* item );
            /**
             * Remove an item from being rendered to this render target.
             *
             * \param item The item to remove.
             */
            void removeChild( RenderChainItem* item );

            int width() const;
            int height() const;

            virtual Texture* texture();

            QColor backgroundColor() const;

        public Q_SLOTS:
            /**
             * Resize the RenderTarget and any attached framebuffers and
             * textures.
             *
             * \param width The new width of the RenderTarget.
             * \param height The new height of the RenderTarget.
             */
            virtual void resize( int width, int height );

            virtual void update();

            /**
             * Render this render target. Reimplemented from Renderable::render().
             */
            virtual void renderContents();

            void setBackgroundColor( const QColor& color );

        protected:
            virtual void resizeImpl() = 0;
            virtual TextureData* textureData() = 0;

        private:
            class Private;
            Private* const d;
    };

}

#endif // GLUONGRAPHICS_RENDERTARGET_H
