/*
 * This file is part of the Gluon library.
 * Copyright (C) 2007-2008 Benoit Jacob
 * Copyright (C) 2008 Rivo Laks <rivolaks@hot.ee>
 * Copyright 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright 2008 Charles Huet <packadal@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "kgltextitem.h"

#include <QString>
#include <QPainter>
#include <QFontMetricsF>
#include <QPainter>
#include <QHash>
#include <QMap>
#include <QDebug>


KGLTextItem::KGLTextItem(const QString& text, const QFont &font, KGLEngine* parent)
    : KGLItem(parent)
{
    m_text=text;
    m_font=font;
    initTexture();
}

bool KGLTextItem::initTexture()
{
    clear();
    QFontMetrics metrics(m_font);
    int texwidth = metrics.width(m_text);
    int texheight= metrics.height();

    qDebug()<<texheight;

    QImage image( texwidth, texheight, QImage::Format_RGB32 );
    QPainter painter;
    // start painting the image
    painter.begin( &image );
    painter.setFont( m_font );
    painter.setRenderHint( QPainter::TextAntialiasing );
    painter.setBackground( Qt::black);
    painter.eraseRect( image.rect() );
    //    // use an artificial blue color. This image is only used internally anyway.
    painter.setPen( Qt::blue );
    painter.drawText(image.rect(),Qt::AlignCenter,m_text);
    painter.end();

    GLubyte *bitmap = new GLubyte[ texwidth * texheight ];
    if( bitmap == 0 ) return false;

    for( int j = texheight - 1, n = 0; j >= 0; j-- )
        for( int i = 0; i < texwidth; i++, n++ )
        {
        bitmap[n] = qBlue( image.pixel( i, j ) );
    }

    GLuint text;
    glGenTextures( 1, &text );
    if( text== 0 ) return false;

    glBindTexture( GL_TEXTURE_2D, text);
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
    glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_ALPHA,
            texwidth,
            texheight,
            0,
            GL_ALPHA,
            GL_UNSIGNED_BYTE,
            bitmap );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    delete [] bitmap;

    int ratio = texwidth/texheight;
    float rp = (float)texheight/2/10;
    createBox(ratio*rp,rp);
    texture()->setGLTexture(text);
    return true;
}



