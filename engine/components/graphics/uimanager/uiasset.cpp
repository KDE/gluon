/******************************************************************************
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

#include "uiasset.h"

#include <core/debughelper.h>
#include <graphics/texture.h>
#include <graphics/engine.h>

#include <QtCore/QUrl>
#include <QtCore/QMimeData>
#include <QtCore/QFile>
#include <QtCore/QDebug>
#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeComponent>
#include <QtGui/QImage>
#include <QtGui/QImageReader>
#include <QtGui/QGraphicsWidget>
#include <QtXml/QXmlStreamReader>

#include "vertex.h"

REGISTER_OBJECTTYPE( GluonEngine, UiAsset )

using namespace GluonEngine;

class UiAsset::UiAssetPrivate
{
    public:
        UiAssetPrivate( UiAsset* asset)
            : q(asset)
            , widget(0)
            , engine(0)
            , component(0)
        {

        }
        ~UiAssetPrivate() {}

        void errorPrint()
        {
            QString errorStr = "Error loading QML file.\n";
            if( component->isError() )
            {
                QList<QDeclarativeError> errors = component->errors();
                foreach( const QDeclarativeError& error, errors )
                {
                    errorStr += ( error.line() > 0 ? QString( QString::number( error.line() ) +
                                  QLatin1String( ": " ) ) : QLatin1String( "" ) )
                                + error.description();
                }
            }
            q->debug( component->url().toString() + '\n' + errorStr );
        }

        UiAsset* q;
        QGraphicsWidget* widget;
        QDeclarativeEngine* engine;
        QDeclarativeComponent* component;
};

UiAsset::UiAsset( QObject* parent )
    : Asset( parent )
    , d( new UiAssetPrivate(this) )
{

}

UiAsset::~UiAsset()
{
    delete d->widget;
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

void UiAsset::load()
{
    if( !d->engine )
    {
        d->engine = new QDeclarativeEngine(this);
        d->component = new QDeclarativeComponent(d->engine, this);
    }

    if( !file().isEmpty() )
    {
        if( !d->widget )
        {
            d->component->loadUrl( file().toLocalFile() );

            if( d->component->isError() )
            {
                d->errorPrint();
                return;
            }

            QObject *root = d->component->create();

            if( !root ) {
                d->errorPrint();
                return;
            }

            d->widget = qobject_cast<QGraphicsWidget*>(root);

            if( d->widget )
            {
                debug( "Execution of QML done!" );
                mimeData()->setText( name() );
                setLoaded( true );
                return;
            }

            delete root;
        }

    }

    debug( "Error loading ui: %1", name() );
}

void UiAsset::setName( const QString& newName )
{
    GluonEngine::Asset::setName( newName );
}

QGraphicsWidget* UiAsset::widget() const
{
    return d->widget;
}

QDeclarativeEngine* UiAsset::engine() const
{
    return d->engine;
}

// Q_EXPORT_PLUGIN2( gluon_asset_terrain, GluonEngine::UiAsset )

#include "uiasset.moc"
