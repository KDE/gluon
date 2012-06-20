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
#include "achievement.h"
#include "asset.h"
#include "achievementsmanager.h"
#include "projectmetadata.h"

#include <core/gdlserializer.h>
#include <core/scriptengine.h>
#include <core/debughelper.h>
#include <core/directoryprovider.h>

#include <QtGui/QImageWriter>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QMetaProperty>

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

    connect( child, SIGNAL(showDebug(QString)), Game::instance(), SIGNAL(showDebug(QString)) );
}

bool
GameProject::removeChild( GluonObject* child )
{
    disconnect( child, SIGNAL(showDebug(QString)), Game::instance(), SIGNAL(showDebug(QString)) );

    return GluonCore::GluonObject::removeChild( child );
}

bool
GameProject::saveToFile()
{
    // Run through everything first and save each of the saveable assets
    GameProjectPrivate::saveChildren( this );

    if( !GluonCore::GDLSerializer::instance()->write( filename(), GluonCore::GluonObjectList() << this ) )
        return false;

    QString projectDir = filename().toLocalFile().section( '/', 0, -2 );
    // Recreate the various icon files if we have an icon file available
    QIcon tempIcon = QIcon::fromTheme ("gluon", QIcon( QPixmap( 128, 128 ) ) );
    QImage icon = tempIcon.pixmap(128, 128).toImage();
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
        out << "[Desktop Entry]" << endl << "Icon=./game.png" << endl << "Type=Directory" << endl;
        directoryFile.close();
    }
    QFile folderFile( projectDir + "/desktop.ini" );
    if( folderFile.open( QFile::WriteOnly | QFile::Truncate | QIODevice::Text ) )
    {
        QTextStream out( &folderFile );
        out << "[.ShellClassInfo]" << endl << "ConfirmFileOp=0" << endl << "IconFile=game.ico" << endl << "IconIndex=0" << endl << "InfoTip=A Gluon Game" << endl;
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

    // Save meta data
    ProjectMetaData metaData( filename().toLocalFile(), name(), description(), property("id").toString() );
    metaData.save();

    // Create a template for the achievements in this project
    AchievementsManager achievementsManager;
    achievementsManager.readFromProject(achievements());
    achievementsManager.makeTemplate();
    QString saveDirectory = projectDir + "/.cache";
    achievementsManager.save(saveDirectory);
    d->tags->writeToFile();
    return true;
}

void GameProject::traverseChildren(GluonObject* gluonObject)
{
    foreach( QObject *child, gluonObject->children() )
    {
        Asset *assetChild = qobject_cast<Asset*>(child);
        if (assetChild)
        {
            addAsset(assetChild);
        }
    }
}

bool
GameProject::loadFromFile()
{
    // change directory to the project path..
    QDir::setCurrent( QFileInfo( filename().toLocalFile() ).canonicalPath() );
    setFilename( filename().toLocalFile() );

    QList<GluonObject*> objectList;
    if( GluonCore::GDLSerializer::instance()->read( filename(), objectList, this ) )
    {
        if( objectList.at(0)->metaObject() )
        {
            // If the first object in the list is a GluonProject, then let's
            // adapt ourselves to represent that object...
            if( objectList.at(0)->metaObject()->className() == metaObject()->className() )
            {
                GameProject* loadedProject = qobject_cast<GameProject*>( objectList[0] );

                // First things first - clean ourselves out, all the children
                // and the media info list should be gone-ified
                qDeleteAll( children() );

                // Reassign all the children of the newly loaded project to
                // ourselves...
                foreach( QObject * child, loadedProject->children() )
                {
                    GluonObject* theChild = qobject_cast<GluonObject*>( child );
                    if( theChild )
                    {
                        theChild->setParent( this );
                        theChild->setGameProject( this );
                        traverseChildren(theChild);
                    }
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
            }
            // Otherwise it is not a GluonProject, and should fail!
            else
            {
                DEBUG_BLOCK
                DEBUG_TEXT( QString( "First object loaded is not a Gluon::GameProject." ) )
                DEBUG_TEXT2( "Type of loaded object: %1", objectList.at(0)->metaObject()->className() )
                DEBUG_TEXT2( "Name of loaded object: %1", objectList.at(0)->name() )
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    d->tags = new TagObject();
    d->tags->setPath( d->dirname );
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

QList<Achievement*> GameProject::achievements() const
{
    return d->achievements;
}

void GameProject::addAchievement(Achievement* achievement)
{
    if( !d->achievements.contains(achievement) )
        d->achievements.append(achievement);
}

void GameProject::removeAchievement(Achievement* achievement)
{
    d->achievements.removeOne(achievement);
}

QString GameProject::userName() const
{
    return d->userName;
}

void GameProject::setUserName(const QString& newUserName)
{
    d->userName = newUserName;
}

// ----------------------------------------------------------------------------
// Asset management

Asset* GameProject::findAsset( const QString& name ) const
{
    Asset* foundAsset = 0;

    foreach( Asset *asset, d->assets )
    {
        if( asset->name() == name )
        {
            foundAsset = asset;
            break;
        }
    }

    return foundAsset;
}

Asset* GameProject::findAssetByType( const QString& typeName ) const
{
    int typeID = QMetaType::type( typeName.toAscii().data() );
    return findAssetByType( typeID );
}

Asset* GameProject::findAssetByType( int type ) const
{
    if( d->assetTypes.find( type ) != d->assetTypes.end() )
        return d->assetTypes.value( type );

    return 0;
}

QList<Asset*> GameProject::findAssetsByType( const QString& typeName ) const
{
    int typeID = QMetaType::type( typeName.toAscii().data() );
    return findAssetsByType( typeID );
}

QList<Asset*> GameProject::findAssetsByType( int type ) const
{
    if( d->assetTypes.find( type ) != d->assetTypes.end() )
        return d->assetTypes.values( type );

    return QList<Asset*>();
}

void GameProject::addAsset( Asset* asset )
{
    if( asset )
    {
        int typeID = GluonCore::GluonObjectFactory::instance()->objectTypeIDs().value( asset->metaObject()->className() );
        if( d->assetTypes.constFind( typeID, asset ) == d->assetTypes.constEnd() )
        {
            d->assetTypes.insert( typeID, asset );
            d->assets.append( asset );
            // connect( asset, SIGNAL(destroyed(QObject*)), SLOT(childDeleted(QObject*)) );
            // asset->setParent( this );
            // asset->setGameProject( this );
            // asset->setName( asset->name() );
        }
    }
    else
    {
        DEBUG_BLOCK
        DEBUG_TEXT( "Attempting to add a null asset" )
    }
}

bool GameProject::removeAsset( Asset* asset )
{
    int typeID = QMetaType::type( asset->metaObject()->className() );
    d->assetTypes.remove( typeID, asset );
    // disconnect( asset, SIGNAL(destroyed(QObject*)), this, SLOT(childDeleted(QObject*)) );
    return d->assets.removeOne( asset );
}

QList<Asset*> GameProject::assets() const
{
    return d->assets;
}

void GameProject::addTags( QString objectname, QString tags )
{
    d->tags->addTags( objectname, tags );
}

TagObject* GameProject::getTagObject()
{
    return d->tags;
}

QString GameProject::getTags( QString objectname )
{
    return d->tags->getTags( objectname );
}

#include "gameproject.moc"
