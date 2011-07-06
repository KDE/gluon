/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2011 Giulio Camuffo <giuliocamuffo@gmail.com>
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

#include "uiasset.h"

#include "textureimageprovider.h"

#include <graphics/texture.h>
#include <graphics/engine.h>

#include <QtDeclarative/QDeclarativeItem>
#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeComponent>

REGISTER_OBJECTTYPE( GluonEngine, UiAsset )

using namespace GluonEngine;

class UiAsset::UiAssetPrivate
{
    public:
        UiAssetPrivate( UiAsset* asset )
            : q( asset )
            , qmlItem( 0 )
            , engine( 0 )
            , component( 0 )
        {

        }
        ~UiAssetPrivate() {}

        void errorPrint()
        {
            QString errorStr = "Error loading QML file.\n";
            if( component->isError() )
            {
                QList<QDeclarativeError> errors = component->errors();
                foreach( const QDeclarativeError & error, errors )
                {
                    errorStr += ( error.line() > 0 ? QString( QString::number( error.line() ) +
                                  QLatin1String( ": " ) ) : QLatin1String( "" ) )
                                + error.description();
                }
            }
            q->debug( component->url().toString() + '\n' + errorStr );
        }

        UiAsset* q;
        QDeclarativeItem* qmlItem;
        QDeclarativeEngine* engine;
        QDeclarativeComponent* component;
};

UiAsset::UiAsset( QObject* parent )
    : Asset( parent )
    , d( new UiAssetPrivate( this ) )
{

}

UiAsset::~UiAsset()
{
    delete d;
}

QIcon UiAsset::icon() const
{
    return GluonEngine::Asset::icon();
}

const QStringList UiAsset::supportedMimeTypes() const
{
    QStringList types;

    types << "text/x-csrc";
    types << "text/plain";

    return types;
}

const QList< AssetTemplate* > UiAsset::templates()
{
    return QList<AssetTemplate*>() << new AssetTemplate( "Interface File", "template.qml", "ui", this );
}

void UiAsset::load()
{
    if( !d->engine )
    {
        d->engine = new QDeclarativeEngine( this );
        d->engine->addImageProvider( "texture", new TextureImageProvider() );
    }

    Asset::load();
}

void UiAsset::execute()
{
    if( !file().isEmpty() )
    {
        if( d->component )
        {
            delete d->qmlItem;
            delete d->component;
        }
        d->engine->clearComponentCache();
        d->qmlItem = 0;

        d->component = new QDeclarativeComponent( d->engine, this );
        d->component->loadUrl( file().toLocalFile() );

        if( d->component->isError() )
        {
            d->errorPrint();
            return;
        }

        QObject* root = d->component->create();

        if( !root )
        {
            d->errorPrint();
            return;
        }

        d->qmlItem = qobject_cast<QDeclarativeItem*>( root );
        if( d->qmlItem )
        {
            mimeData()->setText( name() );
            setLoaded( true );
            return;
        }

        //failed
        delete root;
    }

    debug( "Error loading ui: %1", name() );
}

void UiAsset::setName( const QString& newName )
{
    GluonEngine::Asset::setName( newName );
}

QDeclarativeItem* UiAsset::qmlItem() const
{
    return d->qmlItem;
}

QDeclarativeEngine* UiAsset::engine() const
{
    return d->engine;
}

// Q_EXPORT_PLUGIN2( gluon_asset_terrain, GluonEngine::UiAsset )

#include "uiasset.moc"
