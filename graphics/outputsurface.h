/*****************************************************************************
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

#ifndef GLUONGRAPHICS_OUTPUTSURFACE_H
#define GLUONGRAPHICS_OUTPUTSURFACE_H

#include <QtCore/QObject>

#include "gluon_graphics_export.h"

class QWindow;
namespace GluonGraphics
{
    class RenderTarget;
    /**
     * An on-screen surface to render the final item in the render chain to.
     *
     * The output surface class provides an abstraction of a surface that can be rendered to that can be used
     * in things like widgets and windows. Since we just want a rectangular area to render to, the specific
     * details of what provides that area can mostly be ignored.
     *
     * \todo Provide a scaling factor to scale the render target by so we can do things like render at a
     * lower resolution.
     */
    class GLUON_GRAPHICS_EXPORT OutputSurface : public QObject
    {
            Q_OBJECT
        public:
            /**
             * Constructor.
             *
             * \param container The QWindow object containing this output surface. The backend will use this to create the actual surface to render to.
             * \param parant The QOBject parent.
             */
            OutputSurface( QWindow* container, QObject* parent = 0 );
            virtual ~OutputSurface();

            /**
             * \return The render target that will be rendered to this surface.
             */
            RenderTarget* renderTarget() const;

        public Q_SLOTS:
            /**
             * Render the contents (the render target) of this surface.
             */
            virtual void renderContents() = 0;
            /**
             * Set the render target to be used for rendering.
             *
             * \param newTarget The target to render to this surface.
             */
            virtual void setRenderTarget( RenderTarget* newTarget );
            /**
             * Set the render target to be used for rendering.
             *
             * \param targetIdentifier The target to use for rendering, will be retrieved from Manager.
             */
            virtual void setRenderTarget( const QString& targetIdentifier );
            /**
             * Set the size of this output surface.
             *
             * The render target will be resized to match the given width and height.
             *
             * \param width The new width.
             * \param height The new height
             */
            virtual void setSize( int width, int height );

        protected:
            QWindow* window();

        private:
            class Private;
            Private* const d;
    };

}

#endif // GLUONGRAPHICS_OUTPUTSURFACE_H
