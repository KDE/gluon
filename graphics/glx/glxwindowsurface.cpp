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

#include "glxwindowsurface.h"

#include <QtGui/QWidget>
#include <QtGui/QX11Info>

#include "glxcontext.h"

using namespace GluonGraphics;

class GLXOutputSurface::Private
{
    public:
        GLXContext* context;
};

GLXOutputSurface::GLXWindowSurface( GLXContext* context, QWidget* container, QObject* parent )
    : OutputSurface( container, parent ), d( new Private )
{
    d->context = context;
}

GLXOutputSurface::~WindowSurface()
{
    delete d;
}

void GLXOutputSurface::render()
{
    //glXMakeCurrent();
    d->context()->makeCurrent( widget()->x11Info().visual() );

    Manager::instance()->currentWorld()->render();

    d->context->clearCurrent();
}
