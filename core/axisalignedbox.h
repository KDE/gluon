/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2012 Felix Rohrbach <fxrh@gmx.de>
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

#ifndef AXISALIGNEDBOX_H
#define AXISALIGNEDBOX_H

#include <QVector3D>

#include "gluon_core_export.h"

namespace GluonCore
{

    /**
     * An axis aligned box with a position pointing to the center and a
     * positive size.
     */
    class GLUON_CORE_EXPORT AxisAlignedBox
    {
        public:
            /**
             * Create a new box, with the given position as center and the given size.
             * @param centerPosition The position
             * @param size The size
             */
            AxisAlignedBox( QVector3D size, QVector3D centerPosition = QVector3D(0,0,0) );

            /**
             * Get the current position. It is the center of the box.
             * @return The current position
             * @see setPosition
             */
            QVector3D position() const;

            /**
             * Set the center of the box to a new position.
             * @param newPosition the new position.
             * @see position
             */
            void setPosition( const QVector3D& newPosition );

            /**
             * Get the current size of the box. All components are positive.
             * @return the current size
             * @see setSize
             */
            QVector3D size() const;

            /**
             * Set the size of the box.
             * @param newSize the new size. It should be positive and not 0.
             * @see size
             */
            void setSize( const QVector3D& newSize );

            /**
             * Combine this box with another box. This returns the bounding box of both boxes,
             * with the center of the new box the average of the two centers, and the size of
             * the new box extended to encompass both boxes.
             * @param box The box to combine with.
             * @return The bounding box of both boxes.
             */
            AxisAlignedBox united( const AxisAlignedBox& box ) const;

        private:
            class Private;
            Private* const d;
    };
}

#endif // AXISALIGNEDBOX_H
