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

class QMatrix4x4;
class QVector3D;

namespace GluonGraphics
{
    /**
     * \brief Describes a geometrical frustum for projection calculations.
     *
     * A frustum is essentially a pyramid with the top removed. It is
     * used for projection calculations and a technqiue called frustum
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
             * Creates an identity frustrum.
             */
            Frustum();

            /**
             * Destructor.
             */
            virtual ~Frustum();

            Frustum(const Frustum& other);

            Frustum& operator=(const Frustum& other);

            /**
             * Retrieve the projection matrix.
             *
             * \return The projection matrix of this frustum.
             */
            QMatrix4x4 projectionMatrix();

            /**
             * Check whether a point falls within the frustum.
             *
             * \param point The point to check whether it is inside the
             * frustrum.
             *
             * \return True if the point is inside, false if outside.
             */
            bool containsPoint(const QVector3D& point);

            /**
             * Check whether a sphere falls within the frustum.
             *
             * \param point The centre point of the sphere that needs to be
             * checked.
             * \param radius The radius of the sphere to check.
             *
             * \return True if the sphere is inside or intersects the
             * frustrum. False if not.
             */
            bool containsSphere(const QVector3D& point, float radius);

            /**
             * Set this frustum to use an orthographic projection.
             *
             * \param view Rectangle containing the position and dimensions
             * of the near (view) plane.
             * \param near The distance to the near plane.
             * \param far The distance to the far plane. Should be > near .
             */
            void setOrthographic(float left, float right, float bottom, float top, float near, float far);

            /**
             * Set this frustum to use a perspective projection.
             *
             * \param fov The field of view, in radians.
             * \param aspect Aspect ratio of the frustrum.
             * \param near Distance to the near plane.
             * \param far Distance to the far plane.
             */
            void setPerspective( float fov, float aspect, float near, float far);

        private:
            class FrustumPrivate;
            FrustumPrivate * const d;
    };

}

#endif // GLUONGRAPHICS_FRUSTUM_H
