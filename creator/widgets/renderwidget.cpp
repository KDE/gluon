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

#include <QtGui/QResizeEvent>
#include <QtWidgets/QApplication>

#include <core/log.h>

#include <graphics/defaults.h>
#include <graphics/outputsurface.h>
#include <graphics/backend.h>
#include <graphics/shader.h>
#include <graphics/meshdata.h>

using namespace GluonCreator;
using namespace GluonGraphics;

class RenderWidget::Private
{
    public:
        Private() : surface( 0 ) { }

        OutputSurface* surface;

        Shader* shader;
        MeshData* data;
};

RenderWidget::RenderWidget( QWidget* parent, Qt::WindowFlags f ) :
    QWidget( parent, f )
{
    setAttribute( Qt::WA_PaintOnScreen );
    setAttribute( Qt::WA_OpaquePaintEvent );

    if( !Backend::currentBackend()->initialize( winId() ) )
    {
        CRITICAL() << "Could not initialize GluonGraphics backend";
        CRITICAL() << Backend::currentBackend()->errorString();
        QCoreApplication::exit( 1 );
    }
}

RenderWidget::~RenderWidget()
{
    delete d->surface;
}

void RenderWidget::paintEvent( QPaintEvent* event )
{
    if( !d->surface )
    {
        Defaults::initialize();
        d->surface = Backend::currentBackend()->createOutputSurface( windowHandle() );
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

void RenderWidget::enterEvent(QEvent* event)
{
    setFocus();
}

void RenderWidget::leaveEvent(QEvent* event)
{
    clearFocus();
}

QPaintEngine* RenderWidget::paintEngine() const
{
    return nullptr;
}
