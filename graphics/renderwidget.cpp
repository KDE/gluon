/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2012 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "renderwidget.h"

#include "manager.h"
#include "outputsurface.h"
#include "backend.h"

using namespace GluonGraphics;

class RenderWidget::Private
{
    public:
        OutputSurface* surface;
};

RenderWidget::RenderWidget( QWidget* parent, Qt::WindowFlags f ) :
    QWidget( parent, f ), d( new Private )
{
    setAttribute( Qt::WA_PaintOnScreen );
    setAttribute( Qt::WA_OpaquePaintEvent );
    d->surface = Manager::instance()->backend()->createOutputSurface( this );
}

RenderWidget::~RenderWidget()
{
}

void RenderWidget::paintEvent( QPaintEvent* )
{
    d->surface->render();
}

#include "renderwidget.moc"
