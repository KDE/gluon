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

#ifndef GLUONGRAPHICS_VIEWPORT_H
#define GLUONGRAPHICS_VIEWPORT_H

#include "gluon_graphics_export.h"

#include <QtCore/QObject>

namespace GluonGraphics
{
    /**
     * \brief Geometry of the viewing region.
     *
     * The viewport describes the properties of the "window"
     * which is used to view the scene.
     */
    class GLUON_GRAPHICS_EXPORT Viewport : public QObject
    {
            Q_OBJECT
        public:
            explicit Viewport( QObject* parent = 0 );
            virtual ~Viewport();

            float left();
            float width();
            float bottom();
            float height();
            float aspectRatio();

        public Q_SLOTS:
            void setLeft( float left );
            void setWidth( float width );
            void setBottom( float bottom );
            void setHeight( float height );

            void setSize( float left, float width, float bottom, float height );

            void update();

        Q_SIGNALS:
            void viewportSizeChanged( int left, int bottom, int width, int height );

        private:
            class ViewportPrivate;
            ViewportPrivate* const d;
    };

}

#endif // GLUONGRAPHICS_VIEWPORT_H
