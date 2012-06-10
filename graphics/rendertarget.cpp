/*****************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010-2012 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "rendertarget.h"

#include "renderpipelineitem.h"

using namespace GluonGraphics;

class RenderTarget::Private
{
    public:
        int width;
        int height;

        QList< RenderPipelineItem* > children;
};

RenderTarget::RenderTarget( QObject* parent )
    : QObject( parent ), d( new Private )
{
}

RenderTarget::RenderTarget( int width, int height, QObject* parent )
    : QObject( parent ), d( new Private )
{
}

RenderTarget::~RenderTarget()
{
    delete d;
}

void RenderTarget::addChild(RenderPipelineItem* item)
{

}

void RenderTarget::removeChild(RenderPipelineItem* item)
{

}

int RenderTarget::height()
{
    return d->height;
}

int RenderTarget::width()
{
    return d->width;
}

void RenderTarget::update()
{
    bind();

    Q_FOREACH( RenderPipelineItem* item, d->children )
    {
        item->renderContents();
    }

    release();
}

void RenderTarget::renderContents()
{
    update();


}

void RenderTarget::resize( int width, int height )
{
    if( width == d->width && height == d->height )
        return;

    d->width = width;
    d->height = height;

    resizeImpl();
}

#include "rendertarget.moc"
