/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2009 Dan Leinir Turthra Jensen <admin@leinir.dk>
 * Copyright (c) 2009 Kim Jung Nissen <jungnissen@gmail.com>
 * Copyright (c) 2009 Morten Justesen <morten.justesen@gmail.com>
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

#ifndef COLORGEN_H
#define COLORGEN_H

class QColor;

class ColorGen
{
    public:
        ColorGen() {};
        ColorGen( int hue, int sat, int step );

        QColor nextColor();
        QColor randomColor();
        void reset();

    private:
        int m_sat;
        int m_hue;
        int m_step;

        int m_satorig;
        int m_hueorig;
        int m_v;
};

#endif // COLORGEN_H
