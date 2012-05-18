/*****************************************************************************
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

#include "outputsurface.h"
#include "manager.h"

using namespace GluonGraphics;

class OutputSurface::Private
{
    public:
        QWidget* widget;
        RenderTarget* renderTarget;
};

OutputSurface::OutputSurface(QWidget* container, QObject* parent)
    : QObject( parent ), d( new Private )
{
    d->widget = container;
    //d->renderTarget = Manager::instance()->resource< RenderTarget >( Manager::defaultRenderTarget );
}

OutputSurface::~OutputSurface()
{
    delete d;
}

RenderTarget* OutputSurface::renderTarget() const
{
    return d->renderTarget;
}

void OutputSurface::setRenderTarget( RenderTarget* newTarget )
{
    if( !newTarget )
        return;

    d->renderTarget = newTarget;
}

void OutputSurface::setRenderTarget( const QString& targetIdentifier )
{
    //setRenderTarget( Manager::instance()->resource< RenderTarget >( targetIdentifier ) );
}

QWidget* OutputSurface::widget()
{
    return d->widget;
}

#include "outputsurface.moc"
