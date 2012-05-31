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

#include <QResizeEvent>

#include "manager.h"
#include "outputsurface.h"
#include "backend.h"

using namespace GluonGraphics;

class RenderWidget::Private
{
    public:
        Private() : surface( 0 ) { }

        OutputSurface* surface;
};

RenderWidget::RenderWidget( QWidget* parent, Qt::WindowFlags f ) :
    QWidget( parent, f ), d( new Private )
{
    setAttribute( Qt::WA_PaintOnScreen );
    setAttribute( Qt::WA_OpaquePaintEvent );
}

RenderWidget::~RenderWidget()
{
    delete d->surface;
    delete d;
}

void RenderWidget::paintEvent( QPaintEvent* event )
{
    if( !d->surface )
    {
        if( !Manager::instance()->backend()->initialize( this ) )
            qFatal( Manager::instance()->backend()->errorString().toUtf8() );

        Manager::instance()->initialize();
        d->surface = Manager::instance()->backend()->createOutputSurface( this );
        d->surface->setSize( width(), height() );
    }

    d->surface->renderContents();
}

void RenderWidget::resizeEvent( QResizeEvent* event )
{
    if( d->surface )
        d->surface->setSize( event->size().width(), event->size().height() );
    QWidget::resizeEvent( event );
}

#include "renderwidget.moc"
