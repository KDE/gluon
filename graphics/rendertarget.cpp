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

#include "texture.h"
#include "vertexbuffer.h"
#include "vertexattribute.h"
#include "materialinstance.h"
#include "viewport.h"

#include <QtOpenGL/QGLFramebufferObject>
#include <QtGui/QMatrix4x4>
#include "manager.h"
#include "world.h"

using namespace GluonGraphics;

class RenderTarget::Private
{
    public:
        Camera* camera;

        int width;
        int height;
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

void RenderTarget::render()
{
    bind();

    //for each renderable: render

    release();
}

#include "rendertarget.moc"
