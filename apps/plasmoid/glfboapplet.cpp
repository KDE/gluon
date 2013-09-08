/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright 2007 Zack Rusin <zack@kde.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "glfboapplet.h"

using namespace GluonPlayer;

#include <QtOpenGL/QGLPixelBuffer>
#include <QtOpenGL/QGLFramebufferObject>
#include <QtGui/QPainter>
#include <QtGui/QImage>

class GLFBOApplet::GLFBOAppletPrivate
{
    public:
        GLFBOAppletPrivate()
        {
            init();
        }
        ~GLFBOAppletPrivate()
        {
            delete fbo;
            delete pbuf;
            delete dummy;
        }
        void init()
        {
            dummy = new QGLWidget( ( QWidget* ) 0 );
            dummy->makeCurrent();

            if( QGLFramebufferObject::hasOpenGLFramebufferObjects() )
            {
                fbo = new QGLFramebufferObject( 256, 256, QGLFramebufferObject::CombinedDepthStencil, GL_TEXTURE_2D, GL_RGBA );

                if( !fbo->isValid() )
                    fbo = new QGLFramebufferObject( 256, 256, QGLFramebufferObject::CombinedDepthStencil, GL_TEXTURE_2D, GL_RGB );

                pbuf = 0;
            }
            else
            {
                qDebug() << "Notice: FBO's not available, falling back to pbuffer's";
                fbo = 0;
                QGLFormat format = QGLFormat::defaultFormat();
                //format.setSampleBuffers(true);
                //format.setAlphaBufferSize(8);
                //dummy size construction
                pbuf = new QGLPixelBuffer( 300, 300, format, dummy );
                if( pbuf->isValid() )
                {
                    pbuf->makeCurrent();
                }
            }
            width = 300;
            height = 300;
        }
        void updateGlSize( const QSize& size )
        {
            if( size.width() > width || size.height() > height )
            {
                if( fbo )
                {
                    GLenum intFormat = fbo->format().internalTextureFormat();
                    delete fbo;
                    fbo = new QGLFramebufferObject( size, QGLFramebufferObject::CombinedDepthStencil, GL_TEXTURE_2D, intFormat );
                }
                else
                {
                    QGLFormat format = pbuf->format();
                    delete pbuf;
                    pbuf = new QGLPixelBuffer( size, format, dummy );
                }
                width = size.width();
                height = size.height();
            }
        }

    public:
        QGLFramebufferObject* fbo;
        QGLPixelBuffer* pbuf;
        QGLWidget*      dummy;
        float   width;
        float   height;
};

GLFBOApplet::GLFBOApplet( QGraphicsItem* parent,
                          const QString& serviceId,
                          int appletId )
    : Plasma::Applet( parent, serviceId, appletId )
    , d( new GLFBOAppletPrivate )
{
    if( d->fbo )
    {
        if( !d->fbo->isValid() )
        {
            setFailedToLaunch( true, i18n( "This system does not support Gluon's OpenGL widget." ) );
        }
    }
    else
    {
        if( !d->dummy->isValid() || !QGLPixelBuffer::hasOpenGLPbuffers()
                || !d->pbuf->isValid() )
        {
            setFailedToLaunch( true, i18n( "This system does not support Gluon's OpenGL widget." ) );
        }
    }
}

GLFBOApplet::GLFBOApplet( QObject* parent, const QVariantList& args )
    : Applet( parent, args )
    , d( new GLFBOAppletPrivate )
{
    if( d->fbo )
    {
        if( !d->fbo->isValid() )
        {
            setFailedToLaunch( true, i18n( "This system does not support Gluon's OpenGL widget." ) );
        }
    }
    else
    {
        if( !d->dummy->isValid() || !QGLPixelBuffer::hasOpenGLPbuffers()
                || !d->pbuf->isValid() )
        {
            setFailedToLaunch( true, i18n( "This system does not support Gluon's OpenGL widget." ) );
        }
    }
}

GLFBOApplet::~GLFBOApplet()
{
    delete d;
}

GLuint GLFBOApplet::bindTexture( const QImage& image, GLenum target )
{
    //Q_ASSERT(d->pbuf);
    if( !d->dummy->isValid() )
    {
        return 0;
    }
    return d->dummy->bindTexture( image, target );
}

void GLFBOApplet::deleteTexture( GLuint textureId )
{
    //Q_ASSERT(d->pbuf);
    d->dummy->deleteTexture( textureId );
}

void GLFBOApplet::paintGLInterface( QPainter* /* painter */,
                                    const QStyleOptionGraphicsItem* /* option */ )
{
}

static inline QPainterPath headerPath( const QRectF& r, int roundness,
                                       int headerHeight = 10 )
{
    QPainterPath path;
    int xRnd = roundness;
    int yRnd = roundness;
    if( r.width() > r.height() )
    {
        xRnd = int ( roundness * r.height() / r.width() );
    }
    else
    {
        yRnd = int ( roundness * r.width() / r.height() );
    }

    if( xRnd >= 100 )                        // fix ranges
    {
        xRnd = 99;
    }
    if( yRnd >= 100 )
    {
        yRnd = 99;
    }
    if( xRnd <= 0 || yRnd <= 0 )             // add normal rectangle
    {
        path.addRect( r );
        return path;
    }

    QRectF rect = r.normalized();

    if( rect.isNull() )
    {
        return path;
    }

    qreal x = rect.x();
    qreal y = rect.y();
    qreal w = rect.width();
    qreal h = rect.height();
    qreal rxx = w * xRnd / 200;
    qreal ryy = h * yRnd / 200;
    // were there overflows?
    if( rxx < 0 )
    {
        rxx = w / 200 * xRnd;
    }
    if( ryy < 0 )
    {
        ryy = h / 200 * yRnd;
    }
    qreal rxx2 = 2 * rxx;
    qreal ryy2 = 2 * ryy;

    path.arcMoveTo( x, y, rxx2, ryy2, 90 );
    path.arcTo( x, y, rxx2, ryy2, 90, 90 );
    QPointF pt = path.currentPosition();
    path.lineTo( x, pt.y() + headerHeight );
    path.lineTo( x + w, pt.y() + headerHeight );
    path.lineTo( x + w, pt.y() );
    path.arcTo( x + w - rxx2, y, rxx2, ryy2, 0, 90 );
    path.closeSubpath();

    return path;
}

void GLFBOApplet::paintInterface( QPainter* painter,
                                  const QStyleOptionGraphicsItem* option,
                                  const QRect& /* contentsRect */ )
{
    if( d->fbo )
    {
        d->dummy->makeCurrent();
        d->fbo->bind();

        glClearColor( 0, 0, 0, 0 );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        QMatrix m = painter->worldMatrix();
        QRect deviceRect = m.mapRect( QRect( QPoint( 23, 25 ), boundingRect().size().toSize() ) );
        d->updateGlSize( deviceRect.size() );

        QPainter p( d->fbo );
        paintGLInterface( &p, option );

        QImage image = d->fbo->toImage();
        painter->drawImage( 0, 0, image );
    }
    else
    {
        Q_ASSERT( d->pbuf );
        if( ( !d->dummy->isValid() || !d->pbuf->isValid() ) )
        {
            if( !hasFailedToLaunch() )
            {
                setFailedToLaunch( true, i18n( "Your machine does not support Gluon's OpenGL widget." ) );
            }

            return;
        }
        d->pbuf->makeCurrent();

        // handle background filling
        glClearColor( 0, 0, 0, 0 );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        QMatrix m = painter->worldMatrix();
        QRect deviceRect = m.mapRect( QRect( QPoint( 23, 25 ), boundingRect().size().toSize() ) );
        d->updateGlSize( deviceRect.size() );

        // redirect this widget's painting into the pbuffer
        QPainter p( d->pbuf );
        paintGLInterface( &p, option );

        // draw the pbuffer contents to the backingstore
        QImage image = d->pbuf->toImage();
        painter->drawImage( 0, 0, image );
    }
}

void GLFBOApplet::makeCurrent()
{
    if( !d->dummy->isValid() )
    {
        d->dummy->makeCurrent();
    }
}

 
