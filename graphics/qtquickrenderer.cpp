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

#include "qtquickrenderer.h"

#include <QDeclarativeView>
#include <QDeclarativeError>
#include <QMatrix4x4>

#include "texturedata.h"
#include "spritemesh.h"
#include "material.h"
#include "materialinstance.h"
#include "manager.h"
#include "backend.h"

using namespace GluonGraphics;

class QtQuickRenderer::Private
{
    public:
        Private() : buffer( 0 ), scene( 0 ), data( 0 ) { }
        QImage* buffer;
        QDeclarativeView* scene;

        SpriteMesh* mesh;
        MaterialInstance* material;

        TextureData* data;
};

QtQuickRenderer::QtQuickRenderer( QObject* parent )
    : Texture( parent ), d( new Private )
{
    d->mesh = Manager::instance()->resource< SpriteMesh >( Manager::Defaults::SpriteMesh );
    d->material = Manager::instance()->resource< Material >( Manager::Defaults::Material )->createInstance();
    QMatrix4x4 proj;
    proj.ortho( -0.5, 0.5, -0.5, 0.5, -2, 2);
    d->material->setProperty( "projectionMatrix", proj );
    d->material->setProperty( "viewMatrix", QMatrix4x4() );
    d->material->setProperty( "modelMatrix", QMatrix4x4() );
    d->material->setProperty( "texture0", QVariant::fromValue< Texture* >( this ) );
}

QtQuickRenderer::~QtQuickRenderer()
{
    delete d->buffer;
    delete d->data;
    delete d;
}

void QtQuickRenderer::update()
{
    if( !d->scene )
        return;

    d->buffer->fill( Qt::transparent );

    QPainter painter( d->buffer );
    d->scene->render( &painter );
    painter.end();

    qImageToGL( d->buffer );
    d->data->setData( d->buffer->width(), d->buffer->height(), d->buffer->bits() );
}

void QtQuickRenderer::renderContents()
{
    if( !d->scene )
        return;

    update();

    d->material->bind();
    d->mesh->render( d->material->shader() );
    d->material->release();
}

bool QtQuickRenderer::load( const QUrl& url )
{
    if( d->scene )
        return true;

    d->scene = new QDeclarativeView;
    d->scene->setResizeMode( QDeclarativeView::SizeRootObjectToView );
    d->scene->setSource( url );
    d->scene->setGeometry( 0, 0, 1024, 1024 );

    if( d->scene->errors().count() > 0 )
    {
        DEBUG_BLOCK
        Q_FOREACH( QDeclarativeError error, d->scene->errors() )
        {
            DEBUG_TEXT( error.toString() );
        }
        return false;
    }

    d->data = Manager::instance()->backend()->createTextureData();
    d->data->setFilteringMode( TextureData::NearestFilteringMode );
    d->buffer = new QImage( 1024, 1024, QImage::Format_ARGB32 );

    return true;
}

QImage QtQuickRenderer::image() const
{
    return *(d->buffer);
}

TextureData* QtQuickRenderer::data() const
{
    return d->data;
}

void QtQuickRenderer::resize( int width, int height )
{
    if( d->buffer )
        delete d->buffer;

    d->buffer = new QImage( width, height, QImage::Format_ARGB32 );
    d->scene->setGeometry( 0, 0, width, height );
}

#include "qtquickrenderer.moc"
