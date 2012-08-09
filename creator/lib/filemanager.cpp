/*****************************************************************************
* This file is part of the Gluon Development Platform
* Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
* Copyright (c) 2011 Laszlo Papp <lpapp@kde.org>
* Copyright (c) 2012 Shreya Pandit <shreya@shreyapandit.com>
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
#include <QDebug>
#include <KDE/KStandardAction>
#include <QWidget>
#include <QtCore/QMetaClassInfo>
#include <KDE/KParts/PartManager>
#include <KDE/KMimeType>
#include <KDE/KMimeTypeTrader>
#include <KDE/KService>
#include <KDE/KActionCollection>
#include <KDE/KApplication>
#include <QAction>

using namespace GluonCreator;

GLUON_DEFINE_SINGLETON( FileManager )

class FileManager::Private
{
    public:

        struct OpenedFile
        {
            KParts::Part* part;
            bool closable;
        };

        KParts::PartManager* partManager;
        QHash<QString, OpenedFile> files;
};


KParts::PartManager* FileManager::partManager() const
{
    return d->partManager;
}

KParts::Part* FileManager::part( const QString& partName ) const
{
    if( d->files.contains( partName ) )
        return d->files.value( partName ).part;

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

    QString icon = asset->metaObject()->classInfo( asset->metaObject()->indexOfClassInfo( "org.gluon.icon" ) ).value();
    openFile( asset->absolutePath().toLocalFile(), asset->name(), asset->name(), icon );
}

void FileManager::openFile( const QString& fileName, const QString& name, const QString& title, const QString& icon,  const QString& partName, const QVariantList& partParams, bool closeable )
{
    qDebug()<< "Active window on opening file is"<< kapp->activeWindow();
    if( fileName.isEmpty() )
        return;

    QString fullName = name.isEmpty() ? KUrl( fileName ).fileName() : name;
    QString fullTitle = title.isEmpty() ? fullName : title;
    if( d->files.contains( fullName ) )
    {
        emit newPart( fullName, fullTitle, icon );
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
	qDebug()<<" This parts widget is " << part->widget(); 
        Private::OpenedFile openFile;
        openFile.part = part;
	openFile.closable = closeable;
        d->files.insert( fullName, openFile );
        d->partManager->addPart( part, true );
        emit newPart( fullName, fullTitle, icon );

        return;
    }

    // There really is no part that can be used.
    // Instead, just open it in an external application.
    // KRun* runner = new KRun( KUrl( fileName ), qApp->activeWindow() );
}

void FileManager::SaveAll()
{
  QList<Private::OpenedFile> listopen = d->files.values();
    foreach( Private::OpenedFile open,listopen )
	{
	  KParts::ReadWritePart * rw = qobject_cast<KParts::ReadWritePart *>(open.part);
	  if(rw){ rw->save();}
	}
}

void FileManager::UndoOnEditor()
{
  QList<Private::OpenedFile> listopen = d->files.values();
    foreach( Private::OpenedFile open,listopen )
	{
	  QWidget* widget = open.part->widget();
	  if(widget->hasFocus())
	    {	QAction *undoAction = open.part->action("edit_undo");
		undoAction->activate(QAction::Trigger);
	    }
	}
}

void FileManager::RedoOnEditor()
{
  QList<Private::OpenedFile> listopen = d->files.values();
    foreach( Private::OpenedFile open,listopen )
	{
	  QWidget* widget = open.part->widget();
	  if(widget->hasFocus())
	    {	QAction *redoAction = open.part->action("edit_redo");
		redoAction->activate(QAction::Trigger);
	    }
	}
}


void FileManager::closeFile( const QString& file, bool force )
{
    if( d->files.contains( file ) )
    {
        Private::OpenedFile openFile = d->files.value( file );
        if( openFile.closable || force )
        {
            d->partManager->removePart( openFile.part );
            d->files.remove( file );
            delete openFile.part;
            emit fileClosed( file );
        }
    }
}

void FileManager::setCurrentFile( const QString& file )
{
    if( d->files.contains( file ) )
        d->partManager->setActivePart( d->files.value( file ).part );
}

void FileManager::closeAll( bool force )
{
    QList< QString > files = d->files.keys();
    foreach( const QString& file, files )
    {
        closeFile( file, force );
    }
}

FileManager::FileManager( QObject* parent )
    : GluonCore::Singleton< GluonCreator::FileManager >( parent ), d( new Private )
{
}

FileManager::~FileManager()
{
    delete d;
}
