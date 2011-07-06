/*****************************************************************************
* This file is part of the Gluon Development Platform
* Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
* Copyright (c) 2011 Laszlo Papp <lpapp@kde.org>
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

#include "filemanager.h"

#include <engine/asset.h>

#include <KDE/KParts/ReadWritePart>
#include <KDE/KParts/PartManager>
#include <KDE/KMimeType>
#include <KDE/KMimeTypeTrader>
#include <KDE/KService>
#include <KDE/KActionCollection>

using namespace GluonCreator;

GLUON_DEFINE_SINGLETON( FileManager )

class FileManager::FileManagerPrivate
{
    public:
        KParts::PartManager* partManager;
        QHash<QString, KParts::ReadOnlyPart*> parts;
};


KParts::PartManager* FileManager::partManager() const
{
    return d->partManager;
}

KParts::Part* FileManager::part( const QString& partName ) const
{
    if( d->parts.contains( partName ) )
        return d->parts.value( partName );

    return 0;
}

void FileManager::initialize( QWidget* widget )
{
    setParent( widget );
    d->partManager = new KParts::PartManager( widget );
}

void FileManager::openAsset( GluonEngine::Asset* asset )
{
    if( !asset )
        return;

    openFile( asset->absolutePath(), asset->name(), asset->name() );
}

void FileManager::openFile( const QString& fileName, const QString& name, const QString& title, const QString& partName, const QVariantList& partParams )
{
    if( fileName.isEmpty() )
        return;

    QString fullName = name.isEmpty() ? KUrl( fileName ).fileName() : name;
    QString fullTitle = title.isEmpty() ? fullName : title;
    if( d->parts.contains( fullName ) )
    {
        emit newPart( fullName, fullTitle );
        return;
    }

    KMimeType::Ptr mime = KMimeType::findByPath( fileName );

    KParts::ReadOnlyPart* part = 0;
    KService::List parts;

    if( !partName.isEmpty() )
    {
        KService::Ptr service = KService::serviceByDesktopName( partName );
        if( !service.isNull() )
            parts.append( service );
    }

    if( parts.count() == 0 )
    {
        parts.append( KMimeTypeTrader::self()->query( mime->name(), "KParts/ReadWritePart" ) );
        parts.append( KMimeTypeTrader::self()->query( mime->name(), "KParts/ReadOnlyPart" ) );

        if( mime->name().contains( "audio" ) && parts.count() == 0 )
            parts.append( KService::serviceByStorageId( "dragonplayer_part.desktop" ) );
    }

    if( parts.count() > 0 )
    {
        part = parts.first()->createInstance<KParts::ReadWritePart>( 0, partParams );
        if( !part )
            part = parts.first()->createInstance<KParts::ReadOnlyPart>( 0, partParams );
    }

    if( part )
    {
        // Add the part if it is found
        KUrl url( fileName );
        part->openUrl( url );
        d->parts.insert( fullName, part );
        d->partManager->addPart( part, true );
        emit newPart( fullName, fullTitle );

        return;
    }

    // There really is no part that can be used.
    // Instead, just open it in an external application.
    // KRun* runner = new KRun( KUrl( fileName ), qApp->activeWindow() );
}

void FileManager::closeFile( const QString& file )
{
    KParts::Part* part;
    if( ( part = d->parts.value( file , 0 ) ) )
    {
        d->partManager->removePart( part );
        d->parts.remove( file );
        delete part;
    }
}

void FileManager::setCurrentFile( const QString& file )
{
    if( d->parts.contains( file ) )
        d->partManager->setActivePart( d->parts.value( file ) );
}

FileManager::FileManager( QObject* parent )
    : GluonCore::Singleton< GluonCreator::FileManager >( parent ), d( new FileManagerPrivate )
{
}

FileManager::~FileManager()
{
    delete d;
}
