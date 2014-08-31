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

#include "renderwindow.h"

#include <QtCore/QCoreApplication>
#include <QtGui/QResizeEvent>
#include <QtGui/QBackingStore>

#include "manager.h"
#include "outputsurface.h"
#include "backend.h"
#include "shader.h"
#include "meshdata.h"

using namespace GluonGraphics;

class RenderWindow::Private
{
    public:
        OutputSurface* surface = nullptr;
        QBackingStore* store = nullptr;
};

RenderWindow::RenderWindow( QWindow* parent ) : QWindow( parent )
{
    setSurfaceType( QSurface::RasterSurface );

    //This is used to indirectly call some platform methods to handle resizing.
    d->store = new QBackingStore{ this };

    resize( 640, 480 );

    if( !Manager::instance()->backend()->initialize( winId() ) )
        qFatal( Manager::instance()->backend()->errorString().toUtf8() );
}

RenderWindow::~RenderWindow()
{
    delete d->surface;
}

OutputSurface* RenderWindow::outputSurface() const
{
    return d->surface;
}

void RenderWindow::exposeEvent( QExposeEvent* event )
{
    Q_UNUSED( event )
    render();
}

void RenderWindow::resizeEvent( QResizeEvent* event )
{
    if( d->surface )
        d->surface->setSize( event->size().width(), event->size().height() );

    //QWindow fails to properly resize if certain platform methods are not called.
    //However, those methods are not publicly available thus we need to use
    //QBackingStore to indirectly call them. Rather than having a backing store that
    //takes as much memory as the window size, we can use a 1x1 backing store since
    //it just needs a non-zero size. In addition, the small size prevent flickering
    //as it means the window doesn't get completely redrawn twice.
    d->store->resize( QSize{ 1, 1 } );
    d->store->flush( QRect{ 0, 0, 1, 1 } );
    render();
}

void RenderWindow::render()
{
    if( !isExposed() )
        return;

    if( !d->surface )
    {
        Manager::instance()->initialize();
        d->surface = Manager::instance()->backend()->createOutputSurface( this );
        d->surface->setSize( width(), height() );
    }

    d->surface->renderContents();
}

void RenderWindow::update()
{
    QExposeEvent* ev = new QExposeEvent( geometry() );
    QCoreApplication::postEvent( this, ev );

}
