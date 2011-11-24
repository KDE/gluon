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

#include "colorgen.h"

#include <QtGui/QColor>

ColorGen::ColorGen(int hue, int sat, int step)
{
    qsrand(13);
    m_sat = sat;
    m_hue = hue;
    m_hueorig = hue;
    m_satorig = sat;
    m_step = step;
    m_v = 0;
}

QColor ColorGen::nextColor()
{
    QColor color(0, 0, 0, 0);

    if (m_hue >= 255) {
        m_sat += m_step;
        if (m_sat >= 255) {
            m_sat = 0;
        }
        m_hue = 0;
    }
    m_hue += m_step;

    color.setHsv(m_hue, m_sat, 255, 255);
    return color;
}

QColor ColorGen::randomColor()
{
    m_v = 255 * qrand();

    QColor color(0, 0, 0, 0);
    color.setHsv(m_v, m_sat, 255, 255);
    return color;
}

void ColorGen::reset()
{
    m_hue = m_hueorig;
    m_sat = m_satorig;
}
