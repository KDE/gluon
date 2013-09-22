/******************************************************************************
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

#ifndef GLUONGRAPHICS_CAMERA_H
#define GLUONGRAPHICS_CAMERA_H

#include "gluon_graphics_export.h"
#include "entity.h"
#include "renderchainitem.h"

class QRectF;
class QSizeF;

#include <Eigen/Core>
#include <Eigen/Geometry>

namespace GluonGraphics
{
    class Frustrum;

    /**
     * \brief A view point and volume.
     *
     * The camera class describes a view point and view
     * volume (a.k.a. frustum). These are used to determine
     * what to render and where to render it.
     */
    class GLUON_GRAPHICS_EXPORT Camera : public Entity, public RenderChainItem
    {
            Q_OBJECT

        public:
            /**
             * Constructor.
             *
             * Creates a camera with a default frustum.
             *
             * \param parent The parent QObject.
             */
            explicit Camera( QObject* parent = 0 );

            /**
             * Constructor.
             *
             * \param frustum The frustum to use for this camera.
             * \param parent The parent QObject.
             */
            explicit Camera( Frustrum* frustum, QObject* parent = 0 );

            /**
             * Destructor.
             */
            virtual ~Camera();

            /**
             * Retrieve the view matrix from this camera.
             *
             * The view matrix is the position and rotation of the
             * "eye". This determines from where the scene is viewed.
             *
             * \return The view matrix.
             */
            Eigen::Affine3f viewMatrix() const;

            /**
             * Retrieve the frustum used by this camera.
             *
             * \return The frustum used.
             */
            Frustrum* frustrum() const;

            QSizeF visibleArea() const;

            float nearPlane() const;

            float farPlane() const;

        public Q_SLOTS:
            void setTransform( const Eigen::Affine3f& transform );

            /**
             * Set the frustum to use.
             *
             * \param frustum The frustum to use.
             */
            void setFrustrum( GluonGraphics::Frustrum* frustrum );

            void setVisibleArea( QSizeF area );

            void setNearPlane( float near );

            void setFarPlane( float far );

            virtual void resize( int width, int height );

            virtual void render();

            virtual void renderContents();

        private:
            class Private;
            Private* const d;
    };

}

#endif // GLUONGRAPHICS_CAMERA_H
