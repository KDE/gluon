/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2009 Dan Leinir Turthra Jensen <admin@leinir.dk>
 * Copyright (c) 2009 Kim Jung Nissen <jungnissen@gmail.com>
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

#ifndef GLUON_SMARTS_BTPERCEPTIONVIEWCONE_H
#define GLUON_SMARTS_BTPERCEPTIONVIEWCONE_H

#include <QtCore/QtGlobal>
#include <QtCore/QMetaType>

namespace GluonSmarts
{

struct btPerceptionViewcone
{
    public:
        btPerceptionViewcone();

        /**
         * The horizontal angle by which the view cone is offset from the character's orientation
         * Note: This should be between -180 and 180
         */
        qreal offsetAngleHorizontal;

        /**
         * The vertical angle by which the view cone is offset from the character's orientation
         * Note: This should be between -180 and 180
         */
        qreal offsetAngleVertical;

        /**
         * The horizontal angle of extent of the view cone
         * Note: This angle is from the center to one side, not from side to side
         * Note: This should not be larger than 180
         */
        qreal extentAngleHorizontal;

        /**
        * The vertical angle of extent of the view cone
        * Note: This angle is from the center to top, not from top to bottom
        * Note: This should not be larger than 180
        */
        qreal extentAngleVertical;

        /**
         * The radius of the view cone.
         * If this is left at 0, the limit used will be the character's perception limit.
         * Note: This should be no larger than the radius of the perception limit
         */
        qreal radius;

        /**
         * The precion of knowledge discovered in this view cone's area of perception
         * 0 is no precision at all, 1.0 is full precision
         */
        qreal knowledgePrecision;

        /**
         * The precion of knowledge discovered in this view cone's area of perception
         * 0 is no precision at all, 1.0 is full precision
         */
        int position;
};
}

Q_DECLARE_METATYPE( QList<GluonSmarts::btPerceptionViewcone*> )

#endif // GLUON_SMARTS_BTPERCEPTIONVIEWCONE_H
