/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Rivo Laks <rivolaks@hot.ee>
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
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

#ifndef GLUONGRAPHICS_CAMERA_H
#define GLUONGRAPHICS_CAMERA_H

#include <QtCore/QObject>

#include "gluon_graphics_export.h"

class QMatrix4x4;
namespace GluonGraphics
{
    class Frustum;

    /**
     * \brief A view point and volume.
     *
     * The camera class describes a view point and view
     * volume (a.k.a. frustrum). These are used to determine
     * what to render and where to render it.
     */
    class GLUON_GRAPHICS_EXPORT Camera : public QObject
    {
        Q_OBJECT

        public:
            /**
             * Contrstructor.
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
            explicit Camera( Frustum* frustum, QObject* parent = 0 );

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
            QMatrix4x4 viewMatrix();

            /**
             * Retrieve the frustum used by this camera.
             *
             * \return The frustum used.
             */
            Frustum* frustum();

        public Q_SLOTS:
            /**
             * Set the view matrix to use.
             *
             * \param matrix The matrix to use.
             */
            void setViewMatrix(const QMatrix4x4& matrix);
            /**
             * Set the frustum to use.
             *
             * \param frustum The frustum to use.
             */
            void setFrustrum( Frustum* frustum);

        private:
            class CameraPrivate;
            CameraPrivate * const d;
    };

}

#endif // GLUONGRAPHICS_CAMERA_H
