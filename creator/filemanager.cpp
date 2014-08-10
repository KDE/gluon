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

#include <QtCore/QMetaClassInfo>
#include <QtCore/QTimer>
#include <QtWidgets/QAction>
#include <QtWidgets/QMenu>

#include <KParts/ReadWritePart>
#include <KParts/PartManager>

#include <KService/KMimeTypeTrader>
#include <KService/KService>
#include <KXmlGui/KActionCollection>

#include <KTextEditor/Document>
#include <QMimeDatabase>
#include <QMimeType>

using namespace GluonCreator;

GLUON_DEFINE_SINGLETON( FileManager )

class FileManager::Private
{
    public:
        struct OpenedFile
        {
            bool operator==( const OpenedFile& other ) const
            {
                return other.part == part;
            }

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
    if( fileName.isEmpty() )
        return;

    QString fullName = name.isEmpty() ? QUrl::fromLocalFile( fileName ).fileName() : name;
    QString fullTitle = title.isEmpty() ? fullName : title;
    if( d->files.contains( fullName ) )
    {
        emit newPart( fullName, fullTitle, icon );
        return;
    }

    QMimeDatabase db;
    QMimeType mime = db.mimeTypeForFile( fileName );

    KParts::ReadOnlyPart* part = 0;
    KService::List parts;

    if( !partName.isEmpty() )
    {
        KService::Ptr service = KService::serviceByDesktopName( partName );
        if( service )
            parts.append( service );
    }

    if( parts.count() == 0 )
    {
        parts.append( KMimeTypeTrader::self()->query( mime.name(), "KParts/ReadWritePart" ) );
        parts.append( KMimeTypeTrader::self()->query( mime.name(), "KParts/ReadOnlyPart" ) );

        if( mime.name().contains( "audio" ) && parts.count() == 0 )
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
        QUrl url = QUrl::fromLocalFile( fileName );
        part->openUrl( url );

        Private::OpenedFile openFile;
        openFile.part = part;
        openFile.closable = closeable;

        KTextEditor::Document* doc = qobject_cast< KTextEditor::Document* >( part );
        if( doc )
            connect( doc, SIGNAL(modifiedChanged(KTextEditor::Document*)), this, SLOT(fileModified(KTextEditor::Document*)) );

        d->files.insert( fullName, openFile );
        d->partManager->addPart( part, true );
        emit newPart( fullName, fullTitle, icon );

        return;
    }

    // There really is no part that can be used.
    // Instead, just open it in an external application.
    // KRun* runner = new KRun( KUrl( fileName ), qApp->activeWindow() );
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

void FileManager::saveAll()
{
    QList< Private::OpenedFile > files = d->files.values();
    Q_FOREACH( Private::OpenedFile file, files )
    {
        KParts::ReadWritePart* part = qobject_cast< KParts::ReadWritePart* >( file.part );
        if( part )
            part->save();
    }
}

bool FileManager::undoOnCurrent()
{
    KParts::ReadWritePart* part = qobject_cast< KParts::ReadWritePart* >( d->partManager->activePart() );

    if( part && part->widget()->hasFocus() )
    {
        QAction* undoAction = part->action( "edit_undo" );
        if( undoAction )
        {
            undoAction->trigger();
            return true;
        }
    }

    return false;
}

bool FileManager::redoOnCurrent()
{
    KParts::ReadWritePart* part = qobject_cast< KParts::ReadWritePart* >( d->partManager->activePart() );

    if( part && part->widget()->hasFocus() )
    {
        QAction* redoAction = part->action( "edit_redo" );
        if( redoAction )
        {
            redoAction->trigger();
            return true;
        }
    }

    return false;
}

void FileManager::fileModified( KTextEditor::Document* doc )
{
    QString filePath;
    Q_FOREACH( Private::OpenedFile file, d->files )
    {
        if( file.part == doc )
            filePath = d->files.key( file );
    }

    emit fileModifiedChanged( filePath, doc->isModified() );
}

FileManager::FileManager( QObject* parent )
    : GluonCore::Singleton< GluonCreator::FileManager >( parent ), d( new Private )
{
}

FileManager::~FileManager()
{
    delete d;
}
