/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (C) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

#include "asset.h"

#include <QtCore/QStringList>
#include <QtCore/QDir>
#include <QtCore/QMimeData>

#include <QtCore/QDebug>

#include <core/metainfo.h>

#include "game.h"

REGISTER_OBJECTTYPE( GluonEngine, Asset )

using namespace GluonEngine;

class GluonEngine::AssetPrivate
{
    public:
        AssetPrivate()
            : loaded( false )
            , mime( new QMimeData )
        {
        }

        QString file;
        bool loaded;
        QMimeData* mime;
};

Asset::Asset( QObject* parent )
    : GluonObject( parent )
    , d( new AssetPrivate )
{
}

Asset::~Asset()
{
    delete d->mime;
    delete d;
}

void Asset::sanitize()
{
    if (GluonEngine::Game::instance()->gameProject())
    {
        GluonEngine::Game::instance()->gameProject()->addAsset(this);
    }

    GluonObject::sanitize();
}

void
Asset::setName( const QString& newName )
{
    QString oldName( name() );

    GluonCore::GluonObject::setName( newName );

    // Rename the underlying file, if one exists...
    if( !d->file.isEmpty() )
    {
        // If we use QDir::current(), .exists will throw debug crap... this works around that particular annoyance
        if( QDir( QDir::currentPath() ).exists( absolutePath().toLocalFile() ) )
        {
            QString newFile = Asset::fullyQualifiedFileName( this, QFileInfo( absolutePath().toLocalFile() ).completeSuffix() );

            QString oldPath = d->file.section( '/', 0, -2 );
            QString newPath = newFile.section( '/', 0, -2 );
            QDir::current().mkpath( newPath );

            if( QDir::current().rename( absolutePath().toLocalFile(), QDir::current().absoluteFilePath( newPath ) ) )
            {
                if( QDir::current().exists( oldPath ) )
                    QDir::current().rmpath( oldPath );
                setFile( newFile );
            }
        }
    }
}

void
Asset::setFile( const QString& newFile )
{
    if( !d->file.isEmpty() )
    {
        QString oldPath = d->file.section( '/', 0, -2 );
        if( QDir::current().exists( oldPath ) )
            QDir::current().rmpath( oldPath );
    }

    QString newPath = newFile.section( '/', 0, -2 );
    QDir::current().mkpath( newPath );
    d->file = newFile;

    emit dataChanged();
}

QString
Asset::file() const
{
    return d->file;
}

QUrl
Asset::absolutePath() const
{
    return QUrl::fromLocalFile( Game::instance()->gameProject()->dirname().toLocalFile() + '/' + d->file );
}

const QMimeData*
Asset::data() const
{
    return d->mime;
}

QMimeData* Asset::dragData() const
{
    QMimeData* data = new QMimeData();
    QByteArray encodedData;
    QDataStream stream( &encodedData, QIODevice::WriteOnly );
    stream << fullyQualifiedName();
    data->setData( QString("application/gluon.engine.").append(metaObject()->className()), encodedData );
    return data;
}

QList<AssetAction*>
Asset::actions()
{
    return QList<AssetAction*>();
}

bool
Asset::isLoaded() const
{
    return d->loaded;
}

void
Asset::load()
{
    d->loaded = true;
    emit dataChanged();
}

void Asset::unload()
{
    d->loaded = false;
}

void
Asset::reload()
{
    unload();
    load();
}

bool
Asset::shouldSerializeChildren( ) const
{
    // We do not recurse here - this allows the assets to handle their own
    // children
    return false;
}

QMimeData*
Asset::mimeData() const
{
    return d->mime;
}

void
Asset::setLoaded( bool loaded )
{
    d->loaded = loaded;
}

GluonCore::GluonObject*
Asset::findItemByNameInternal( QStringList qualifiedName )
{
    if( !qualifiedName.isEmpty() && !isLoaded() )
        load();

    return GluonCore::GluonObject::findItemByNameInternal( qualifiedName );
}

QString
Asset::fullyQualifiedFileName( GluonCore::GluonObject* obj, const QString& extension )
{
    QStringList parts = obj->fullyQualifiedName().split( '/' );
    if( parts.count() > 1 && parts.first() == obj->gameProject()->name() )
        parts.removeFirst();

    QString fileExtension = parts.last().section('.', -1, -1, QString::SectionIncludeLeadingSep);
    if (fileExtension == QString(".%1").arg(extension))
        parts.last().remove(fileExtension);

    QRegExp filter( "[^a-z0-9_]+" );

    QString file = parts.last().toLower().replace( ' ', '_' ).remove( filter );
    parts.removeLast();

    QStringList path;
    foreach( const QString & part, parts )
    {
        path.append( part.toLower().replace( ' ', '_' ).remove( filter ) );
    }

    QString dir = path.join( "/" );
    if( dir.length() > 0 )
        dir.append( '/' );

    QString ext = extension.isEmpty() ? obj->metaInfo()->defaultExtension() : extension;
    return QString( "%1%2.%3" ).arg( dir, file, ext );
}


 

