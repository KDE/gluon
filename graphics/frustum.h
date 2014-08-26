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

#ifndef GLUONGRAPHICS_FRUSTUM_H
#define GLUONGRAPHICS_FRUSTUM_H

#include "gluon_graphics_export.h"

class QRectF;
class QSizeF;

#include <Eigen/Core>
#include <Eigen/Geometry>

namespace GluonGraphics
{
    /**
     * \brief Describes a geometrical frustum for projection calculations.
     *
     * A frustum is essentially a pyramid with the top removed. It is
     * used for projection calculations and a technique called frustum
     * culling.
     *
     * \todo Expand this description and its use.
     */
    class GLUON_GRAPHICS_EXPORT Frustum
    {
        public:
            /**
             * Constructor.
             *
             * Creates an identity frustum.
             */
            Frustum();

            /**
             * Destructor.
             */
            virtual ~Frustum();

            Frustum( const Frustum& other );

            Frustum& operator=( const Frustum& other );

            /**
             * Retrieve the projection matrix.
             *
             * \return The projection matrix of this frustum.
             */
            Eigen::Affine3f projectionMatrix();

            /**
             * Check whether a point falls within the frustum.
             *
             * \param point The point to check whether it is inside the
             * frustum.
             *
             * \return True if the point is inside, false if outside.
             */
            bool containsPoint( const Eigen::Vector3f& point );

            /**
             * Check whether a sphere falls within the frustum.
             *
             * \param point The centre point of the sphere that needs to be
             * checked.
             * \param radius The radius of the sphere to check.
             *
             * \return True if the sphere is inside or intersects the
             * frustum. False if not.
             */
            bool containsSphere( const Eigen::Vector3f& point, float radius );

            /**
             * Retrieve the distance to the near plane of this frustum.
             *
             * \return The distance to the near plane of this frustum.
             */
            float nearPlane();

            /**
             * Retrieve the distance to the far plane of this frustum.
             *
             * \return The distance to the far plane of this frustum.
             */
            float farPlane();

            /**
             * Retrieve the view plane of this frustum.
             *
             * The view plane is equal to the near plane.
             *
             * \return The view plane of this frustum.
             */
            QRectF viewPlane();

            /**
             * Set this frustum to use an orthographic projection.
             *
             * \param left The left coordinate of the view plane.
             * \param right The right coordinate of the view plane.
             * \param bottom The bottom coordinate of the view plane.
             * \param top The top coordinate of the view plane.
             * \param near The distance to the near plane.
             * \param far The distance to the far plane. Should be > near .
             */
            void setOrthographic( float left, float right, float bottom, float top, float near, float far );

            /**
             * Set this frustum to use an orthographic projection, adjusted
             * for aspect ratio.
             *
             * Note that the view plane will always be centred on 0,0; that
             * is, the view plane's left coordinate will be -(area.width / 2).
             *
             * \param area The area describing the width and height of the view plane.
             * \param aspect The aspect ratio to adjust for.
             * \param near The distance to the near plane.
             * \param far The distance to the far plane.
             */
            void setOrthoAdjusted( const QSizeF& area, float aspect, float near, float far );

            /**
             * Set this frustum to use a perspective projection.
             *
             * \param fov The field of view, in radians.
             * \param aspect Aspect ratio of the frustum.
             * \param near Distance to the near plane.
             * \param far Distance to the far plane.
             */
            void setPerspective( float fov, float aspect, float near, float far );

            /**
             * Update the frustum to account for a new aspect ratio.
             *
             * \param aspect The new aspect ratio to use.
             */
            void updateFrustum( float aspect );

        private:
            class Private;
            Private* const d;
    };

}

#endif // GLUONGRAPHICS_FRUSTUM_H
