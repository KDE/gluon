/*****************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "viewport.h"

#include "camera.h"
#include "frustrum.h"

#include <QtCore/QRect>

using namespace GluonGraphics;

class Viewport::Private
{
    public:
        float left;
        float bottom;
        float width;
        float height;
        float aspectRatio;
};

Viewport::Viewport( QObject* parent )
    : QObject( parent ), d( new Private )
{
}


Viewport::~Viewport()
{
    delete d;
}

float
Viewport::left()
{
    return d->left;
}

float
Viewport::bottom()
{
    return d->bottom;
}

float
Viewport::width()
{
    return d->width;
}

float
Viewport::height()
{
    return d->height;
}

float
Viewport::aspectRatio()
{
    return d->aspectRatio;
}

void
Viewport::setLeft( float left )
{
    setSize( left, d->width, d->bottom, d->height );
}

void
Viewport::setBottom( float bottom )
{
    setSize( d->left, d->width, bottom, d->height );
}

void
Viewport::setWidth( float width )
{
    setSize( d->left, width, d->bottom, d->height );
}

void
Viewport::setHeight( float height )
{
    setSize( d->left, d->width, d->bottom, height );
}

void
Viewport::setSize( float left, float width, float bottom, float height )
{
    d->left = left;
    d->bottom = bottom;
    d->width = width;
    d->height = height;

    d->aspectRatio = width / height;

    update();
}

void
Viewport::update()
{
    /*glViewport( d->left, d->bottom, d->width, d->height );

    if( Engine::instance()->activeCamera() )
    {
        Frustrum* frustrum = Engine::instance()->activeCamera()->frustrum();

        frustrum->updateFrustrum( d->aspectRatio );

        // float visibleWidth = d->width;
        // float actualWidth = 0;
        // float visibleHeight = d->height;
        // float actualHeight = 0;
        // float widthDiff = 0;
        // float heightDiff = 0;
        // float aspect = frustrum->viewPlane().width() / frustrum->viewPlane().height();

        // if( d->aspectRatio > 1 )
        // {
            // actualHeight = visibleHeight;
            // actualWidth = visibleHeight * aspect;
            // widthDiff = visibleWidth - actualWidth;
        // }
        // else
        // {
            //actualWidth = visibleWidth;
            // actualHeight = visibleWidth * ( 1 / aspect );
            // heightDiff = visibleHeight - actualHeight;
        // }

        //glScissor(widthDiff / 2, heightDiff / 2, actualWidth, actualHeight);
    }
    else
    {
        //glScissor(d->left, d->bottom, d->width, d->height);
    }
    emit viewportSizeChanged( d->left, d->bottom, d->width, d->height );*/
}

#include "viewport.moc"
