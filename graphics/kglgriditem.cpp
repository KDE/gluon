/*
 * This file is part of the Gluon library.
 * Copyright 2009 Gluon team
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

#include "kglgriditem.h"
#include <QtCore/QDebug>

KGLGridItem::KGLGridItem(const QSizeF &size, float tile, KGLEngine * parent)
    : KGLItem(parent)
{
    setMode(GL_TRIANGLE_STRIP);
    m_size = size;
    m_tile = tile;
    createGrid();
}

KGLGridItem::KGLGridItem(float width, float height, float tile, KGLEngine * parent)
    : KGLItem(parent)
{
    setMode(GL_TRIANGLE_STRIP);
    m_size = QSizeF(width,height);
    m_tile = tile;
    createGrid();
}

void KGLGridItem::createGrid()
{
    clear();

    for ( float j=0; j<=m_size.height();j+=m_tile)
    {
        for ( float i=0; i<=m_size.width(); i+=m_tile)
        {
            addVertex(KGLPoint(i,j,Qt::white,QPointF(i/m_size.width(),j/m_size.height())));
            addVertex(KGLPoint(i,j+m_tile,Qt::white,QPointF(i/m_size.width(),(j+m_tile)/m_size.height())));
        }
    }
}

const KGLPoint * KGLGridItem::pointAt(const QPoint &p)
{
    int id =  m_size.width()*p.y() + p.x();
    return &(pointList().at(id));
}

#include "kglgriditem.moc"
