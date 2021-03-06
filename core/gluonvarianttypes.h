/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2009 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

#ifndef GLUON_VARIANTTYPES
#define GLUON_VARIANTTYPES

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <QtCore/QMetaType>

Q_DECLARE_METATYPE(Eigen::Vector2f);
Q_DECLARE_METATYPE(Eigen::Vector2f*)
Q_DECLARE_METATYPE(Eigen::Vector3f);
Q_DECLARE_METATYPE(Eigen::Vector3f*);
Q_DECLARE_METATYPE(Eigen::Vector4f);
Q_DECLARE_METATYPE(Eigen::Vector4f*);
Q_DECLARE_METATYPE(Eigen::Quaternionf);
Q_DECLARE_METATYPE(Eigen::Quaternionf*);
Q_DECLARE_METATYPE(Eigen::Affine3f);
Q_DECLARE_METATYPE(Eigen::Affine3f*);

namespace GluonCore
{
    namespace VariantType
    {
        static const int Float = 135;
        static const int Vector2f = qRegisterMetaType<Eigen::Vector2f>( "Vector2f" );
        static const int Vector3f = qRegisterMetaType<Eigen::Vector3f>( "Vector3f" );
        static const int Vector4f = qRegisterMetaType<Eigen::Vector4f>( "Vector4f" );
        static const int Quaternionf = qRegisterMetaType<Eigen::Quaternionf>( "Quaternionf" );
        static const int Affine3f = qRegisterMetaType<Eigen::Affine3f>( "Affine3f" );
    }
}
#endif
