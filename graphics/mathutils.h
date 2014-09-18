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

#ifndef GLUONGRAPHICS_MATHUTILS_H
#define GLUONGRAPHICS_MATHUTILS_H

#include "gluon_graphics_export.h"

#include <QtGui/QImage>

#include <Eigen/Core>
#include <Eigen/Geometry>

namespace GluonGraphics
{
    /**
     * Utility class containing Math-related methods.
     */
    class GLUON_GRAPHICS_EXPORT MathUtils
    {
        public:
            /**
             * Calculate an orthographic projection matrix.
             *
             * See https://www.opengl.org/sdk/docs/man2/xhtml/glOrtho.xml
             */
            static Eigen::Affine3f ortho( float left, float right, float bottom, float top, float nearVal, float farVal );

            /**
             * Calculate a perspective projection matrix.
             */
            static Eigen::Affine3f perspective( float angle, float aspect, float nearPlane, float farPlane );
    };

}

#endif // GLUONGRAPHICS_MATHUTILS_H
