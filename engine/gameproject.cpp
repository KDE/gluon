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

#include "gameproject.h"
#include "gameprojectprivate.h"

#include "scene.h"
#include "game.h"

#include <core/gdlhandler.h>
#include <core/scriptengine.h>
#include <core/debughelper.h>

#include <QtGui/QImageWriter>
#include <QtCore/QCoreApplication>
#include <QtCore/QStringList>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QMetaClassInfo>

REGISTER_OBJECTTYPE( GluonEngine, GameProject )

using namespace GluonEngine;

GameProject::GameProject( QObject* parent )
    : GluonObject( parent )
    , d( new GameProjectPrivate )
{
    setGameProject( this );
}

GameProject::GameProject( const GameProject& other, QObject* parent )
    : GluonObject( parent )
    , d( other.d )
{
}

GameProject::~GameProject()
{
}

void
GameProject::addChild( GluonObject* child )
{
    GluonCore::GluonObject::addChild( child );

    connect( child, SIGNAL( showDebug( const QString& ) ), Game::instance(), SIGNAL( showDebug( const QString& ) ) );
}

bool
GameProject::removeChild( GluonObject* child )
{
    disconnect( child, SIGNAL( showDebug( const QString& ) ), Game::instance(), SIGNAL( showDebug( const QString& ) ) );

    return GluonCore::GluonObject::removeChild( child );
}

bool
GameProject::saveToFile() const
{
    // Run through everything first and save each of the saveable assets
    GameProjectPrivate::saveChildren( this );

    // Eventually, save self
    QFile projectFile( filename().toLocalFile() );
    if( !projectFile.open( QIODevice::WriteOnly ) )
        return false;

    QList<const GluonObject*> thisProject;
    thisProject.append( this );

    QTextStream projectWriter( &projectFile );
    projectWriter << GluonCore::GDLHandler::instance()->serializeGDL( thisProject );
    projectFile.close();

    QString projectDir = filename().toLocalFile().section( '/', 0, -2 );
    // Recreate the various icon files if we have an icon file available
    QImage icon( 128, 128, QImage::Format_ARGB32 );
    if( d->icon )
        icon = d->icon->texture()->image().scaled( 128, 128, Qt::KeepAspectRatio, Qt::SmoothTransformation );
    QString iconFile( projectDir );
    iconFile.append( '/' );
    iconFile.append( GluonEngine::projectIcon );
    icon.save( iconFile );
    if( QImageWriter::supportedImageFormats().contains( "ico" ) )
    {
        iconFile = projectDir;
        iconFile.append( '/' );
        iconFile.append( GluonEngine::projectWinIcon );
        QImageWriter iconWriter( iconFile );
        iconWriter.setFormat( "ico" );
        iconWriter.write( icon );
    }

    // Build the folder information files for Windows and for XDG compliant file browsers
    QFile directoryFile( projectDir + "/.directory" );
    if( directoryFile.open( QFile::WriteOnly | QFile::Truncate | QIODevice::Text ) )
    {
        QTextStream out( &directoryFile );
        out << QString( "[Desktop Entry]\nIcon=game.png\nType=Directory\n" );
        directoryFile.close();
    }
    QFile folderFile( projectDir + "/desktop.ini" );
    if( folderFile.open( QFile::WriteOnly | QFile::Truncate | QIODevice::Text ) )
    {
        QTextStream out( &folderFile );
        out << QString( "[.ShellClassInfo]\nConfirmFileOp=0\nIconFile=game.ico\nIconIndex=0\nInfoTip=A Gluon Game\n" );
        folderFile.close();
    }

    // Recreate the screenshot file if we have one such
    if( d->screenshot )
    {
        QString screenshotFile = projectDir;
        screenshotFile.append( '/' );
        screenshotFile.append( GluonEngine::projectScreenshot );
        d->screenshot->texture()->image().scaled( 800, 600, Qt::KeepAspectRatio ).save( screenshotFile );
    }

    return true;
}

bool
GameProject::loadFromFile()
{
    DEBUG_FUNC_NAME

    // change directory to the project path..
    DEBUG_TEXT( QString( "Changing working directory to %1" ).arg( QFileInfo( filename().toLocalFile() ).canonicalPath() ) );
    QDir::setCurrent( QFileInfo( filename().toLocalFile() ).canonicalPath() );
    setFilename( filename().toLocalFile() );

    DEBUG_TEXT( QString( "Loading project from %1" ).arg( QFileInfo( filename().toLocalFile() ).fileName() ) );
    QFile projectFile( QFileInfo( filename().toLocalFile() ).fileName() );
    if( !projectFile.open( QIODevice::ReadOnly ) )
        return false;

    QTextStream projectReader( &projectFile );
    QString fileContents = projectReader.readAll();
    projectFile.close();

    if( fileContents.isEmpty() )
        return false;

    QList<GluonObject*> objectList = GluonCore::GDLHandler::instance()->parseGDL( filename().toLocalFile(), parent() );
    if( objectList.count() > 0 )
    {
        if( objectList[0]->metaObject() )
        {
            // If the first object in the list is a GluonProject, then let's
            // adapt ourselves to represent that object...
            if( objectList[0]->metaObject()->className() == metaObject()->className() )
            {
                DEBUG_TEXT( "Project successfully parsed - applying to local instance" );
                GameProject* loadedProject = qobject_cast<GameProject*>( objectList[0] );

                // First things first - clean ourselves out, all the children
                // and the media info list should be gone-ified
                qDeleteAll( children() );

                // Reassign all the children of the newly loaded project to
                // ourselves...
                foreach( QObject * child, loadedProject->children() )
                {
                    GluonObject* theChild = qobject_cast<GluonObject*>( child );
                    theChild->setParent( this );
                    theChild->setGameProject( this );
                }

                // Set all the interesting values...
                setName( loadedProject->name() );

                // Copy across all the properties
                const QMetaObject* metaobject = loadedProject->metaObject();
                int count = metaobject->propertyCount();
                for( int i = 0; i < count; ++i )
                {
                    QMetaProperty metaproperty = metaobject->property( i );
                    const QString theName( metaproperty.name() );
                    if( theName == "objectName" || theName == "name" )
                        continue;
                    setProperty( metaproperty.name(), loadedProject->property( metaproperty.name() ) );
                }

                // Then get all the dynamic ones (in case any such exist)
                QList<QByteArray> propertyNames = loadedProject->dynamicPropertyNames();
                foreach( const QByteArray & propName, propertyNames )
                {
                    setProperty( propName, loadedProject->property( propName ) );
                }

                // Sanitize me!
                sanitize();

                // Finally, get rid of the left-overs
                qDeleteAll( objectList );

                DEBUG_TEXT( "Project loading successful!" );
            }
            // Otherwise it is not a GluonProject, and should fail!
            else
            {
                DEBUG_TEXT( QString( "First object loaded is not a Gluon::GameProject." ) );
                DEBUG_TEXT( QString( "Type of loaded object:" ).arg( objectList[0]->metaObject()->className() ) );
                DEBUG_TEXT( QString( "Name of loaded object:" ).arg( objectList[0]->name() ) );
                return false;
            }
        }
        else
        {
            return false;
        }
    }

    return true;
}

bool
GameProject::loadFromFile( QUrl fileUrl )
{
    setFilename( fileUrl );
    setDirname( fileUrl.toLocalFile().section( '/', 0, -2 ) );
    return loadFromFile();
}

bool
GameProject::loadFromFile( QString fileName )
{
    setFilename( fileName );
    setDirname( fileName.section( '/', 0, -2 ) );
    return loadFromFile();
}

/******************************************************************************
 * Property Getter-setters
 *****************************************************************************/

QString
GameProject::description() const
{
    return d->description;
}

void
GameProject::setDescription( QString newDescription )
{
    d->description = newDescription;
}

QUrl
GameProject::homepage() const
{
    return d->homepage;
}
void
GameProject::setHomepage( QUrl newHomepage )
{
    d->homepage = newHomepage;
}

QList<QUrl>
GameProject::mediaInfo() const
{
    return d->mediaInfo;
}
void
GameProject::setMediaInfo( QList<QUrl> newMediaInfo )
{
    d->mediaInfo = newMediaInfo;
}

QUrl
GameProject::filename() const
{
    return d->filename;
}

void
GameProject::setFilename( QUrl fileUrl )
{
    d->filename = fileUrl;
}

void
GameProject::setFilename( QString fileName )
{
    d->filename = QUrl::fromLocalFile( fileName );
}

Scene*
GameProject::entryPoint() const
{
    return d->entryPoint;
}

QUrl
GameProject::dirname() const
{
    return d->dirname;
}

void
GameProject::setDirname( QUrl dirUrl )
{
    d->dirname = dirUrl;
}

void
GameProject::setDirname( QString dirName )
{
    d->dirname = QUrl::fromLocalFile( dirName );
}

void
GameProject::setEntryPoint( Scene* newEntryPoint )
{
    d->entryPoint = newEntryPoint;
}

GluonEngine::TextureAsset* GameProject::icon() const
{
    return d->icon;
}

void GameProject::setIcon( GluonEngine::TextureAsset* newIcon )
{
    d->icon = newIcon;
}

GluonEngine::TextureAsset* GameProject::screenshot() const
{
    return d->screenshot;
}

void GameProject::setScreenshot( GluonEngine::TextureAsset* newScreenshot )
{
    d->screenshot = newScreenshot;
}

QString GameProject::userName() const
{
    return d->userName;
}

void GameProject::setUserName(const QString& newUserName)
{
    d->userName = newUserName;
}

#include "gameproject.moc"
