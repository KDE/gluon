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

#include "mathutils.h"

#include <cstring>

#include <QtGui/QImage>
#include <qmath.h>

using namespace GluonGraphics;

void
MathUtils::qmatrixToGLMatrix( const Eigen::Affine3f& matrix, float* out )
{
    std::memcpy(out, matrix.data(), sizeof(float)*16);
}

Eigen::Affine3f
MathUtils::calculateModelViewProj( const Eigen::Affine3f& model, const Eigen::Affine3f& view, const Eigen::Affine3f& projection )
{
    return projection * ( view * model );
}

void
MathUtils::qImageToGL( const QImage& image, uchar* out )
{
    int w = image.width();
    int h = image.height();
    int i = 0;

    for( int r = 0; r < h; ++r )
    {
        for( int c = 0; c < w; ++c )
        {
            QRgb pixel = image.pixel( c, r );
            out[i++] = qRed( pixel );
            out[i++] = qGreen( pixel );
            out[i++] = qBlue( pixel );
            out[i++] = qAlpha( pixel );
        }
    }
}

Eigen::Affine3f
MathUtils::ortho( float left, float right, float bottom, float top, float nearPlane, float farPlane )
{
    // Taken from the Qt QMatrix4x4 class
    if( left == right || bottom == top || nearPlane == farPlane )
        return Eigen::Affine3f::Identity();

    float width = right - left;
    float invheight = top - bottom;
    float clip = farPlane - nearPlane;
    Eigen::Affine3f result;
    result(0,0) = 2.0f / width;
    result(0,1) = 0.0f;
    result(0,2) = 0.0f;
    result(0,3) = -(left + right) / width;
    result(1,0) = 0.0f;
    result(1,1) = 2.0f / invheight;
    result(1,2) = 0.0f;
    result(1,3) = -(top + bottom) / invheight;
    result(2,0) = 0.0f;
    result(2,1) = 0.0f;
    result(2,2) = -2.0f / clip;
    result(2,3) = -(nearPlane + farPlane) / clip;
    result(3,0) = 0.0f;
    result(3,1) = 0.0f;
    result(3,2) = 0.0f;
    result(3,3) = 1.0f;
    return result;
}

Eigen::Affine3f
MathUtils::perspective( float angle, float aspect, float nearPlane, float farPlane )
{
    // Taken from the Qt QMatrix4x4 class
    if( nearPlane == farPlane || aspect == 0.0f )
        return Eigen::Affine3f::Identity();

    float radians = (angle/2.f) * M_PI / 180.f;
    float sine = qSin(radians);
    if( sine == 0 )
        return Eigen::Affine3f::Identity();

    float cotan = qCos(radians)/sine;
    float clip = farPlane - nearPlane;
    Eigen::Affine3f result;
    result(0,0) = cotan/aspect;
    result(0,1) = 0.0f;
    result(0,2) = 0.0f;
    result(0,3) = 0.0f;
    result(1,0) = 0.0f;
    result(1,1) = cotan;
    result(1,2) = 0.0f;
    result(1,3) = 0.0f;
    result(2,0) = 0.0f;
    result(2,1) = 0.0f;
    result(2,2) = -(nearPlane + farPlane) / clip;
    result(2,3) = -(2.0f * nearPlane * farPlane) / clip;
    result(3,0) = 0.0f;
    result(3,1) = 0.0f;
    result(3,2) = -1.0f;
    result(3,3) = 0.0f;
    return result;
}

const Eigen::Vector3f MathUtils::VECTOR_UNIT_X = Eigen::Vector3f( 1.f, 0.f, 0.f );
const Eigen::Vector3f MathUtils::VECTOR_UNIT_Y = Eigen::Vector3f( 0.f, 1.f, 0.f );
const Eigen::Vector3f MathUtils::VECTOR_UNIT_Z = Eigen::Vector3f( 0.f, 0.f, 1.f );
const Eigen::Vector3f MathUtils::VECTOR_UNIT_SCALE = Eigen::Vector3f( 1.f, 1.f, 1.f );

