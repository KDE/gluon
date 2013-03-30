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
             * Convert a 4x4 Eigen::Matrix to a float array.
             *
             * This will convert a 4x4 Eigen::Matrix to an array of 16 floats
             * which can be used by OpenGL's matrix functions, most
             * notably glUniformMatrix4fv.
             *
             * Note that this method is mostly a workaround for stuff lacking
             * from Qt (is that still the case with Eigen?).
             *
             * \param matrix The Matrix to convert.
             * \param out An array of 16 floats into which the converted
             * matrix will be copied.
             *
             * TODO: Check if this is still needed/valid with Eigen, maybe rename?
             */
            static void qmatrixToGLMatrix( const Eigen::Affine3f& matrix, float* out );

            /**
             * Calculate a Model-View-Projection matrix.
             *
             * This type of matrix is used to transform vertices into screen
             * space prior to rendering.
             *
             * \param model The object-space matrix. (Object's transformation)
             * \param view The view matrix. (Camera's transformation)
             * \param projection The projection matrix.
             */
            static Eigen::Affine3f calculateModelViewProj( const Eigen::Affine3f& model, const Eigen::Affine3f& view, const Eigen::Affine3f& projection );

            /**
             * Convert a QImage to an array of unsigned chars.
             *
             * This method will convert a 32 bits ARGB QImage to
             * an RGBA array of unsigned chars.
             *
             * Note that this method is mostly a workaround for stuff lacking
             * from Qt.
             *
             * \param image The image to convert.
             * \param out An array of unsigned chars to which the data needs to
             * be copied.
             */
            static void qImageToGL( const QImage& image, uchar* out );

            /**
             * Calculate an orthographic matrix.
             *
             * See https://www.opengl.org/sdk/docs/man2/xhtml/glOrtho.xml
             */
            static Eigen::Affine3f ortho( float left, float right, float bottom, float top, float nearVal, float farVal );

            static Eigen::Affine3f perspective( float angle, float aspect, float nearPlane, float farPlane );

            /**
             * X-axis unit vector, (1, 0, 0).
             */
            static const Eigen::Vector3f      VECTOR_UNIT_X;
            /**
             * Y-axis unit vector, (0, 1, 0).
             */
            static const Eigen::Vector3f      VECTOR_UNIT_Y;
            /**
             * Z-axis unit vector, (0, 0, 1).
             */
            static const Eigen::Vector3f      VECTOR_UNIT_Z;
            /**
             * Default scale vector, (1, 1, 1).
             */
            static const Eigen::Vector3f      VECTOR_UNIT_SCALE;
    };

}

#endif // GLUONGRAPHICS_MATHUTILS_H
