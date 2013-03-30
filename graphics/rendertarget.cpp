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

#include <QColor>
#include <QtAlgorithms>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include "mathutils.h"
#include "manager.h"
#include "backend.h"
#include "spritemesh.h"
#include "texture.h"
#include "material.h"
#include "materialinstance.h"

#include <core/gluonvarianttypes.h>

using namespace GluonGraphics;

class RenderTarget::Private
{
    public:
        Private( RenderTarget* qq ) : q( qq ), mesh( 0 ), materialInstance( 0 ), texture( 0 ) { }

        void initialize();
        void sortChildren();

        RenderTarget* q;

        int width;
        int height;

        QList< RenderChainItem* > children;

        Mesh* mesh;
        MaterialInstance* materialInstance;

        Texture* texture;

        QColor backgroundColor;

        static bool compareZDepth( RenderChainItem* first, RenderChainItem* second );
};

RenderTarget::RenderTarget( QObject* parent )
    : QObject( parent ), d( new Private( this ) )
{
}

RenderTarget::RenderTarget( int width, int height, QObject* parent )
    : QObject( parent ), d( new Private( this ) )
{
    resize( width, height );
}

RenderTarget::~RenderTarget()
{
    delete d;
}

void RenderTarget::addChild(RenderChainItem* item)
{
    if( item && !d->children.contains( item ) )
    {
        d->children.append( item );
        item->setParentItem( this );
        item->resize( d->width, d->height );
        d->sortChildren();
    }
}

void RenderTarget::removeChild(RenderChainItem* item)
{
    if( item && d->children.contains( item ) )
    {
        d->children.removeOne( item );
        item->setParentItem( 0 );
        d->sortChildren();
    }
}

int RenderTarget::height() const
{
    return d->height;
}

int RenderTarget::width() const
{
    return d->width;
}

QColor RenderTarget::backgroundColor() const
{
    return d->backgroundColor;
}

void RenderTarget::update()
{
    bind();

    foreach( RenderChainItem* item, d->children )
    {
        item->renderContents();
    }

    release();
}

void RenderTarget::renderContents()
{
    if( !d->materialInstance )
        d->initialize();

    update();

    d->materialInstance->bind();
    d->mesh->render( d->materialInstance->shader() );
    d->materialInstance->release();
}

void RenderTarget::resize( int width, int height )
{
    if( width == d->width && height == d->height )
        return;

    d->width = width;
    d->height = height;

    foreach( RenderChainItem* item, d->children )
    {
        item->resize( width, height );
    }

    resizeImpl();
}

Texture* RenderTarget::texture()
{
    if( !d->texture )
        d->texture = new Texture( textureData(), this );

    return d->texture;
}

void RenderTarget::setBackgroundColor( const QColor& color )
{
    d->backgroundColor = color;
}

void RenderTarget::Private::initialize()
{
    mesh = Manager::instance()->resource< SpriteMesh >( Manager::Defaults::SpriteMesh );
    materialInstance = Manager::instance()->resource< Material >( Manager::Defaults::Material )->createInstance();
    Eigen::Affine3f id = Eigen::Affine3f::Identity();
    materialInstance->setProperty( "modelMatrix", QVariant::fromValue(id) );
    materialInstance->setProperty( "viewMatrix", QVariant::fromValue(id) );
    Eigen::Affine3f matrix;
    matrix = MathUtils::ortho( -.5f, .5f, -.5f, .5f, -.5f, .5f );
    materialInstance->setProperty( "projectionMatrix", QVariant::fromValue(matrix) );
    materialInstance->setProperty( "texture0", QVariant::fromValue< Texture* >( q->texture() ) );
}

void RenderTarget::Private::sortChildren()
{
    qStableSort( children.begin(), children.end(), Private::compareZDepth );
}

bool RenderTarget::Private::compareZDepth( RenderChainItem* first, RenderChainItem* second )
{
    return first->zDepth() < second->zDepth();
}

#include "rendertarget.moc"
