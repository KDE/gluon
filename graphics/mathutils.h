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

#include <QtGui/QMatrix4x4>
#include <QtGui/QVector3D>

namespace GluonGraphics
{
    /**
     * Utility class containing Math-related methods.
     */
    class GLUON_GRAPHICS_EXPORT MathUtils
    {
        public:
            /**
             * Convert a QMatrix4x4 to a float array.
             *
             * This will convert a QMatrix4x4 to an array of 16 floats
             * which can be used by OpenGL's matrix functions, most
             * notably glUniformMatrix4fv.
             *
             * Note that this method is mostly a workaround for stuff lacking
             * from Qt.
             *
             * \param matrix The QMatrix to convert.
             * \param out An array of 16 floats into which the converted
             * matrix will be copied.
             */
            static void qmatrixToGLMatrix( const QMatrix4x4& matrix, float* out );

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
            static QMatrix4x4 calculateModelViewProj( const QMatrix4x4& model, const QMatrix4x4& view, const QMatrix4x4& projection );

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
             * X-axis unit vector, (1, 0, 0).
             */
            static const QVector3D      VECTOR_UNIT_X;
            /**
             * Y-axis unit vector, (0, 1, 0).
             */
            static const QVector3D      VECTOR_UNIT_Y;
            /**
             * Z-axis unit vector, (0, 0, 1).
             */
            static const QVector3D      VECTOR_UNIT_Z;
            /**
             * Default scale vector, (1, 1, 1).
             */
            static const QVector3D      VECTOR_UNIT_SCALE;
    };

}

#endif // GLUONGRAPHICS_MATHUTILS_H
