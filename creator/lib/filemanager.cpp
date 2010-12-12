/*****************************************************************************
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

#include "filemanager.h"

#include <QtGui/QVBoxLayout>

#include <KDE/KMimeType>
#include <KDE/KMimeTypeTrader>
#include <KDE/KRun>
#include <KDE/KService>
#include <KDE/KTabWidget>
#include <KDE/KToolBar>

#include <KDE/KParts/ReadWritePart>
#include <KDE/KParts/PartManager>

#include <core/debughelper.h>
#include <engine/asset.h>
#include <KActionCollection>
#include <qactiongroup.h>
#include <QMouseEvent>
#include <QApplication>
#include <KServiceTypeTrader>

using namespace GluonCreator;

template<> GLUON_CREATOR_VISIBILITY FileManager* GluonCore::Singleton<FileManager>::m_instance = 0;

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

    openFile( asset->absolutePath(), asset->name() );
}

void FileManager::openFile( const QString& fileName, const QString& name, const QString& partName, const QVariantList& partParams )
{
    if( fileName.isEmpty() )
        return;

    QString fullName = name.isEmpty() ? KUrl( fileName ).fileName() : name;
    if( d->parts.contains( fullName ) )
    {
        DEBUG_TEXT2( "Using existing file: %1", fullName );
        emit newPart( fullName );
        return;
    }

    KMimeType::Ptr mime = KMimeType::findByPath( fileName );

    KParts::ReadOnlyPart* part;
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
        //Add the part if it is found
        KUrl url( fileName );
        part->openUrl( url );
        d->parts.insert( fullName, part );
        d->partManager->addPart( part, true );
        emit newPart( fullName );

        return;
    }

    //Nope, there really is no part that can be used.
    //So instead, just open it in an external application.
    KRun* runner = new KRun( KUrl( fileName ), qApp->activeWindow() );
    Q_UNUSED( runner );

}

void FileManager::closeFile( const QString& file )
{
    if( d->parts.contains( file ) )
    {
        KParts::Part* part = d->parts.value( file );
        d->partManager->removePart( part );
        delete part;
        d->parts.remove( file );
    }
}

void FileManager::setCurrentFile( const QString& file )
{
    d->partManager->setActivePart( d->parts.value( file ) );
}

FileManager::FileManager()
    : d( new FileManagerPrivate )
{
}

FileManager::~FileManager()
{
    delete d;
}
