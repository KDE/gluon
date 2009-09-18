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

#ifndef KGLPOLYGONITEM_H
#define KGLPOLYGONITEM_H

#include "kglitem.h"

/**
 * \defgroup KGL KGL
 */
//@{

/**
* @class KGLPolygonItem kglpolygonitem.h <KGLPolygonItem>
* This is a KGLItem subclass that represents a polygon, and which can be initialized with a QPolygonF.
*/
class KGLPolygonItem : public KGLItem
{
    Q_OBJECT
    public:
        KGLPolygonItem(const QPolygonF &polygon, KGLEngine* parent=0);
};

//@}
#endif //KGLPOLYGONITEM_H
