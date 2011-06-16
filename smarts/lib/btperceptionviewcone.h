/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef BTPERCEPTIONVIEWCONE_H
#define BTPERCEPTIONVIEWCONE_H
#include <qglobal.h>

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

#endif // BTPERCEPTIONVIEWCONE_H
