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

#include "kglboxitem.h"

KGLBoxItem::KGLBoxItem(KGLEngine * parent)
    : KGLItem(parent)
{
    setMode(GL_POLYGON);
    createBox(QSizeF());
}

KGLBoxItem::KGLBoxItem(const QSizeF &dim, KGLEngine * parent)
    : KGLItem(parent)
{
    setMode(GL_POLYGON);
    setBox(dim);
    m_dim = dim;
}

KGLBoxItem::KGLBoxItem(const float &w, const float &h, KGLEngine * parent)
    : KGLItem(parent)
{
    setMode(GL_POLYGON);
    setBox(w,h);
    m_dim = QSizeF(w,h);
}
void KGLBoxItem::resize(const QSizeF &size)
{
clear();
m_dim=size;
createBox(size);
recreate();
}
