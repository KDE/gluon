/*
 * This file is part of the KGLEngine2D project.
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef KGLPIXMAP_ITEM_H
#define KGLPIXMAP_ITEM_H

#include <QPixmap>
#include "kglitem.h"
#include "kglboxitem.h"
class KGLPixmapItem: public KGLBoxItem
{
    Q_OBJECT
public:

    //    explicit KGLPixmapItem(const GLint &texture = 0, const QRectF &dim = QRectF(0, 0, 0.5, 0.5));
    explicit KGLPixmapItem(const QString &fileName, KGLWidget* parent=0);
    explicit KGLPixmapItem(const QPixmap &p, KGLWidget* parent=0);
    QPixmap &pixmap(){return m_pix;}

private:
    QPixmap  m_pix;


};

#endif //KGLPIXMAP_ITEM_H

