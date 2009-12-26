/*
 * This file is part of the Gluon library.
 * Copyright 2008 Sacha Schutz <istdasklar@free.fr>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "kglcircleitem.h"

#include <math.h>

KGLCircleItem::KGLCircleItem(float radius, unsigned int nbPoints, KGLEngine * parent)
    : KGLItem(parent)
{
    setMode(GL_POLYGON);
    setCircle(radius, nbPoints);
    setCenter(QPointF(0,0));
}

void KGLCircleItem::setCircle(float radius, unsigned int nbPoints)
{
    if (nbPoints < 3) {
        return;
    }

    float step = M_PI * 2 / (float)nbPoints;

    for (float i = 0; i < M_PI*2; i += step) {
        float x = cos(i) ;
        float y = sin(i)  ;
       addVertex( KGLPoint(x*radius, y*radius, Qt::white, QPointF(x, y)));
    }
}

#include "kglcircleitem.moc"
