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

#include "kglpixmapitem.h"
#include "kglengine.h"
#include <QtCore/QFile>
#include <KDebug>
#include <Eigen/Core>

KGLPixmapItem::KGLPixmapItem(const QString &fileName,KGLEngine * parent)
    :KGLBoxItem(parent)
{
    m_pix = QPixmap(fileName);
    if ( m_pix.isNull())
    {
        kDebug()<<"cannot load pixmap";
        return;
    }
    KGLTexture *texture = new KGLTexture(fileName);
    setTexture(texture);
    createBox(texture->dim().width(), texture->dim().height());

}
KGLPixmapItem::KGLPixmapItem(const QPixmap &p, KGLEngine * parent )
    :KGLBoxItem(parent)
{
    m_pix = p;
    if ( m_pix.isNull())
    {
        kDebug()<<"cannot load pixmap";
        return;
    }
    KGLTexture * texture= new KGLTexture(m_pix);
    setTexture(texture);
    createBox(texture->dim().width(), texture->dim().height());
}


