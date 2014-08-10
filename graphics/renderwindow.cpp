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
};

RenderWindow::RenderWindow( QWindow* parent ) : QWindow( parent )
{
    setSurfaceType( QSurface::OpenGLSurface );

    if( !Manager::instance()->backend()->initialize( this ) )
        qFatal( Manager::instance()->backend()->errorString().toUtf8() );
}

RenderWindow::~RenderWindow()
{
    delete d->surface;
}

void RenderWindow::exposeEvent( QExposeEvent* event )
{
    if( !isExposed() )
        return;

    if( !d->surface )
    {
        Manager::instance()->initialize();
        d->surface = Manager::instance()->backend()->createOutputSurface( this );
        d->surface->setSize( width(), height() );
    }

    requestActivate();
    d->surface->renderContents();
}

void RenderWindow::resizeEvent( QResizeEvent* event )
{
    if( d->surface )
        d->surface->setSize( event->size().width(), event->size().height() );

    QWindow::resizeEvent( event );
}

void RenderWindow::update()
{
    QExposeEvent* ev = new QExposeEvent( geometry() );
    QCoreApplication::sendEvent( this, ev );
}

 
