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

#include "glxcontext.h"

#include <QtGui/QX11Info>
#include <QtGui/QWidget>
#include <GL/glx.h>

using namespace GluonGraphics::GLX;

class Context::Private
{
    public:
        GLXContext context;
        bool current;
};

Context::Context()
    : d( new Private )
{
    int attribList[] = { GLX_RGBA, GLX_DOUBLEBUFFER, GLX_RED_SIZE, 8, GLX_GREEN_SIZE, 8, GLX_BLUE_SIZE, 8, None };

    XVisualInfo* info = glXChooseVisual( QX11Info::display(), QX11Info::appScreen(), attribList );
    d->context = glXCreateContext( QX11Info::display(), info, 0, true );
}

Context::~Context()
{
    glXDestroyContext( QX11Info::display(), d->context );
}

void Context::makeCurrent( QWidget* widget )
{
    if( d->current )
        return;

    glXMakeCurrent( QX11Info::display(), widget->internalWinId(), d->context );
    d->current = true;
}

void Context::clearCurrent()
{
    if( !d->current )
        return;

    glXMakeCurrent( QX11Info::display(), None, NULL );
}
