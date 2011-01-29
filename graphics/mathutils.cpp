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

#include <QtGui/QImage>

using namespace GluonGraphics;

void
MathUtils::qmatrixToGLMatrix( const QMatrix4x4& matrix, float* out )
{
    qreal* data = matrix.transposed().data();

    for( int i = 0; i < 16; ++i )
    {
        out[i] = static_cast<float>( data[i] );
    }
}

QMatrix4x4
MathUtils::calculateModelViewProj( const QMatrix4x4& model, const QMatrix4x4& view, const QMatrix4x4& projection )
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

const QVector3D MathUtils::VECTOR_UNIT_X = QVector3D( 1.f, 0.f, 0.f );
const QVector3D MathUtils::VECTOR_UNIT_Y = QVector3D( 0.f, 1.f, 0.f );
const QVector3D MathUtils::VECTOR_UNIT_Z = QVector3D( 0.f, 0.f, 1.f );
const QVector3D MathUtils::VECTOR_UNIT_SCALE = QVector3D( 1.f, 1.f, 1.f );

