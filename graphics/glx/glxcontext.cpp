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

#include <QtCore/QDebug>
#include <QtGui/QX11Info>
#include <QtGui/QWidget>

#include <GL/glx.h>

#include "glxfunctions.h"

using namespace GluonGraphics::GLX;

class Context::Private
{
    public:
        Private() : current( false ) { }

        Version parseVersion( const QByteArray& string );

        GLXContext context;
        bool current;

        Version glXVersion;
        Version glVersion;
        Version glslVersion;
        QString renderer;

        QString errorString;

        QList< QString > extensions;
};

bool Version::operator==( const Version& other )
{
    return ( major == other.major && minor == other.minor );
}

QString Version::toString() const
{
    return QString( "%1.%2" ).arg( major ).arg( minor );
}

Context::Context()
    : d( new Private )
{
}

Context::~Context()
{
    if( d->context )
        destroy();

    delete d;
}

bool Context::initialize( QWidget* widget )
{
    //Clear any error state.
    glGetError();

    //Create the actual OpenGL context.
    int attribList[] = { GLX_RGBA, GLX_DOUBLEBUFFER, GLX_RED_SIZE, 8, GLX_GREEN_SIZE, 8, GLX_BLUE_SIZE, 8, None };

    XVisualInfo* info = glXChooseVisual( QX11Info::display(), QX11Info::appScreen(), attribList );
    d->context = glXCreateContext( QX11Info::display(), info, 0, true );

    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        //We failed to create the context. Abort!
        d->errorString = QString( "Failed to create OpenGL context: Error %1" ).arg( error );
        return false;
    }

    //Set it to current so we can initialize some properties.
    glXMakeCurrent( QX11Info::display(), widget->winId(), d->context );
    glXMakeCurrent( QX11Info::display(), widget->winId(), d->context );

    //Set all the version related properties.
    d->glXVersion = d->parseVersion( glXGetClientString( QX11Info::display(), GLX_VERSION ) );
    QByteArray version = QByteArray( reinterpret_cast< const char* >( glGetString( GL_VERSION ) ) ).left( 3 );
    d->glVersion = d->parseVersion( version );
    if( d->glVersion.major < 2 )
    {
        //Oops! We do not have at least OpenGL 2 support. Abort!
        d->errorString = QString( "OpenGL version %1 found. Gluon requires at least OpenGL 2.0 support." ).arg( d->glVersion.toString() );
        destroy();
        return false;
    }
    d->glslVersion = d->parseVersion( reinterpret_cast< const char* >( glGetString( GL_SHADING_LANGUAGE_VERSION ) ) );

    //Make a list of all available extensions.
    d->extensions = QString( reinterpret_cast< const char* >( glGetString( GL_EXTENSIONS ) ) ).split( ' ' );
    if( !d->extensions.contains( "GL_EXT_framebuffer_object" ) )
    {
        //We need support for FBOs otherwise the entire chain of RenderTarget objects will fail.
        d->errorString = QString( "Extension GL_EXT_framebuffer_object not found. Gluon requires this extension to be present." );
        destroy();
        return false;
    }

    d->renderer = reinterpret_cast< const char* >( glGetString( GL_RENDERER ) );

    GluonGraphics::GLX::initializeFunctions();

    glClearColor( 0.f, 0.f, 0.f, 1.f );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    return true;
}

void Context::destroy()
{
    if( !d->context )
        return;

    clearCurrent();
    glXDestroyContext( QX11Info::display(), d->context );
    d->context = 0;
}

void Context::makeCurrent( QWidget* widget )
{
    glXMakeCurrent( QX11Info::display(), widget->winId(), d->context );
    d->current = true;
}

void Context::clearCurrent()
{
    glXMakeCurrent( QX11Info::display(), None, NULL );
    d->current = false;
}

bool Context::isCurrent() const
{
    return d->current;
}

QString Context::errorString() const
{
    return d->errorString;
}

Version Context::glVersion() const
{
    return d->glVersion;
}

Version Context::glXVersion() const
{
    return d->glXVersion;
}

Version Context::glslVersion() const
{
    return d->glslVersion;
}

QString Context::rendererString() const
{
    return d->renderer;
}

bool Context::hasExtension( const QString& extension ) const
{
    return d->extensions.contains( extension );
}

const QList< QString > Context::extensions() const
{
    return d->extensions;
}

Version Context::Private::parseVersion( const QByteArray& string )
{
    QList< QByteArray > numbers = string.split( '.' );

    Version ver = { 0, 0 };
    if( numbers.count() > 0 )
        ver.major = numbers.at( 0 ).toInt();

    if( numbers.count() > 1 )
        ver.minor = numbers.at( 1 ).toInt();

    return ver;
}
