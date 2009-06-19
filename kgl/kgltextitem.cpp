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

#include "kgltextitem.h"


#include <QString>
#include <QPainter>
KGLTextItem::KGLTextItem(const QRectF& rectangle,const QString& text, KGLEngine* parent) :
        KGLItem(parent)
{
    m_text = text;
    m_rect = rectangle;
    createBox(rectangle.size());
    setPosition(rectangle.x(), rectangle.y());
    updateTransform();
    createTexture();
}

void KGLTextItem::createTexture()
{
    QPixmap * pix = new QPixmap(m_rect.width(), m_rect.height());
    pix->fill(Qt::transparent);
    QPainter pen(pix);
    pen.setPen(color());
    pen.drawText(pix->rect(), Qt::AlignCenter, m_text);
    setTexture(*pix);


}
