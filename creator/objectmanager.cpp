/******************************************************************************
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

#include "objectmanager.h"

#include "selectionmanager.h"
#include "newobjectcommand.h"
#include "deleteobjectcommand.h"
#include "propertychangedcommand.h"
#include "historymanager.h"

#include "models/models.h"
#include "models/scenemodel.h"

#include <engine/gameproject.h>
#include <engine/gameobject.h>
#include <engine/scene.h>
#include <engine/game.h>
#include <engine/component.h>

#include <gluon_global.h>

#include <graphics/materialinstance.h>

#include <core/debughelper.h>

#include <KDE/KLocalizedString>
#include <KDE/KMimeType>
#include <KDE/KDirWatch>

#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <QtCore/QStringBuilder>
#include <QtCore/QDebug>

using namespace GluonCreator;

GLUON_DEFINE_SINGLETON( ObjectManager )

class ObjectManager::Private
{
    public:
    Private()
        : m_objectId( 0 )
        , m_sceneId( 0 )
    {
    }

    int m_objectId;
    int m_sceneId;
    QHash<QString, GluonEngine::Asset*> m_assets;
};

QString
ObjectManager::humanifyClassName( const QString& fixThis, bool justRemoveNamespace ) const
{
    QString fixedString;
    const QString classname = fixThis.right( fixThis.length() - fixThis.lastIndexOf( ':' ) - 1 );
    if( justRemoveNamespace )
        return classname;
    const int length = classname.size();
    for( int i = 0; i < length; ++i )
    {
        const QChar current = classname.at( i );
        if( i == 0 )
        {
            // Always upper-case the first word, whether it is or not...
            fixedString = current.toUpper();
        }
        else
        {
            if( current.isUpper() )
            {
                fixedString = fixedString % ' ' % current;
            }
            else
            {
                fixedString = fixedString % current;
            }
        }
    }
    return fixedString;
}

GluonEngine::Asset* ObjectManager::createNewAsset( const QString& fileName, GluonCore::GluonObject* parent, const QString& className, const QString& name )
{
    DEBUG_BLOCK
    GluonCore::GluonObject* newChild = 0;
    if( className.isEmpty() )
    {
        KMimeType::Ptr type = KMimeType::findByFileContent( fileName );
        DEBUG_TEXT( QString( "Creating asset for file %1 of mimetype %2" ).arg( fileName ).arg( type->name() ) )
        newChild = GluonCore::GluonObjectFactory::instance()->instantiateObjectByMimetype( type->name() );
    }
    else
    {
        newChild = GluonCore::GluonObjectFactory::instance()->instantiateObjectByName( className );
    }

    if( !newChild )
        return 0;

    GluonEngine::Asset* newAsset = qobject_cast< GluonEngine::Asset* >( newChild );
    if( newAsset )
    {
        setupAsset( newAsset, parent, fileName, name );
    }

    if( newAsset->inherits("GluonEngine::MaterialAsset"))
        connect(newAsset, SIGNAL(instanceCreated(GluonGraphics::MaterialInstance*)), SLOT(createObjectCommand(GluonGraphics::MaterialInstance*)));

    return newAsset;
}

void ObjectManager::createAssets( const QStringList& fileNames, GluonCore::GluonObject* parent )
{
    foreach( const QString & asset, fileNames )
    {
        ObjectManager::instance()->createNewAsset( asset, parent );
    }
}

void ObjectManager::setupAsset( GluonEngine::Asset* newAsset, GluonCore::GluonObject* parent, const QString& fileName, const QString& name )
{
    if( newAsset == 0 )
        return;

    if( parent && !qobject_cast<GluonEngine::Asset*>( parent ) )
    {
        parent->addChild( newAsset );
    }
    else
    {
        GluonEngine::Game::instance()->gameProject()->addChild( newAsset );
    }

    newAsset->setGameProject( GluonEngine::Game::instance()->gameProject() );

    QFileInfo info( fileName );
    if( name.isEmpty() )
    {
        newAsset->setName( info.fileName() );
    }
    else
    {
        newAsset->setName( name );
    }

    QString newFile = GluonEngine::Asset::fullyQualifiedFileName( newAsset );
    QFile( fileName ).copy( newFile );
    newAsset->setFile( newFile );

    newAsset->load();

    QString filePath( newAsset->absolutePath().toLocalFile() );
    d->m_assets.insert( filePath, newAsset );
    KDirWatch::self()->addFile( filePath );

    HistoryManager::instance()->addCommand( new NewObjectCommand( newAsset ) );
}

void ObjectManager::changeProperty( GluonCore::GluonObject* object, QString& property, QVariant& oldValue, QVariant& newValue )
{
    HistoryManager::instance()->addCommand( new PropertyChangedCommand( object, property, oldValue, newValue ) );
}

GluonEngine::Component* ObjectManager::createNewComponent( const QString& type, GluonEngine::GameObject* parent )
{
    DEBUG_BLOCK
    GluonCore::GluonObject* newObj = GluonCore::GluonObjectFactory::instance()->instantiateObjectByName( type );
    if( newObj )
    {
        newObj->setName( humanifyClassName( newObj->metaObject()->className(), true ) );

        GluonEngine::Component* comp = qobject_cast<GluonEngine::Component*>( newObj );
        parent->addComponent( comp );

        // Initialize the component
        comp->initialize();

        emit newComponent( comp );

        HistoryManager::instance()->addCommand( new NewObjectCommand( comp ) );

        return comp;
    }
    return 0;
}

GluonEngine::GameObject* ObjectManager::createNewGameObject()
{
    DEBUG_FUNC_NAME
    GluonEngine::GameObject* newObj = new GluonEngine::GameObject();
    newObj->setName( humanifyClassName( newObj->metaObject()->className(), false ) );
    DEBUG_TEXT2( "Creating object: %1", newObj->name() )

    newObj->initialize();

    SelectionManager::SelectionList selection = SelectionManager::instance()->selection();
    if( selection.size() > 0 )
    {
        GluonEngine::GameObject* obj = qobject_cast<GluonEngine::GameObject*>( selection.at( 0 ) );
        if( obj )
        {
            DEBUG_TEXT2( "Item %1 selected in Scene tree - assign new object as child", obj->fullyQualifiedName() )
            Models::instance()->sceneModel()->newGameObject( obj, newObj );
        }
    }

    if( newObj->parentGameObject() == 0 )
    {
        DEBUG_TEXT( QString( "No parent game object yet - assign as child to Scene root" ) )
        Models::instance()->sceneModel()->newGameObject( Models::instance()->sceneModel()->rootGameObject(), newObj );
    }

    emit newGameObject( newObj );

    HistoryManager::instance()->addCommand( new NewObjectCommand( newObj ) );

    return newObj;
}

void ObjectManager::createObjectCommand(GluonGraphics::MaterialInstance* materialInstance)
{
    HistoryManager::instance()->addCommand( new NewObjectCommand( materialInstance ) );
}

void ObjectManager::deleteObject( GluonCore::GluonObject* object )
{
    if( !object )
    {
        qDebug() << "No object specified for deleting";
        return;
    }

    if( SelectionManager::instance()->selection().contains( object ) )
        SelectionManager::instance()->clearSelection();

    GluonCore::GluonObject* parent = qobject_cast< GluonCore::GluonObject* >( object->parent() );

    HistoryManager::instance()->addCommand( new DeleteObjectCommand( object ) );
    emit objectDeleted( parent );
}

GluonEngine::Scene* ObjectManager::createNewScene()
{
    GluonEngine::Scene* scene = new GluonEngine::Scene();
    scene->setName( i18n( "NewScene" ) );
    scene->setGameProject( GluonEngine::Game::instance()->gameProject() );
    GluonEngine::Game::instance()->gameProject()->addChild( scene );

    emit newScene( scene );

    HistoryManager::instance()->addCommand( new NewObjectCommand( scene ) );

    return scene;
}

void ObjectManager::notifyPropertyChanged( QObject* object, const QString& property, const QVariant& value )
{
    emit propertyChanged( object, property, value );
}

void ObjectManager::notifyObjectAdded( GluonCore::GluonObject* parent )
{
    emit objectAdded( parent );
}

void ObjectManager::notifyObjectDeleted( GluonCore::GluonObject* parent )
{
    emit objectDeleted( parent );
}

void ObjectManager::watchCurrentAssets()
{
    QList<GluonEngine::Asset*> assets = GluonEngine::Game::instance()->gameProject()->findItemsByType<GluonEngine::Asset>();
    foreach( GluonEngine::Asset * asset, assets )
    {
        watchAsset( asset );
    }
}

void ObjectManager::watchAsset( GluonEngine::Asset* asset )
{
    QString path = asset->absolutePath().toLocalFile();
    KDirWatch::self()->addFile( path );
    d->m_assets.insert( path, asset );
}

void ObjectManager::assetDirty( const QString& file )
{
    GluonEngine::Asset* asset = d->m_assets.value( file );
    if( asset )
    {
        asset->reload();
        GluonEngine::Game::instance()->drawAll();
    }
}

void ObjectManager::unwatchAsset( GluonEngine::Asset* asset )
{
    QString file = asset->absolutePath().toLocalFile();
    if( d->m_assets.contains( file ) )
    {
        d->m_assets.remove( file );
        KDirWatch::self()->removeFile( file );
    }
}

void ObjectManager::assetDeleted( const QString& file )
{
    if( d->m_assets.contains( file ) )
    {
        d->m_assets.remove( file );
        KDirWatch::self()->removeFile( file );
    }

    //WARNING: This destroys data if we delete assets without saving the project!
    //We should only do this if we save the project.
    QFileInfo fi( file );
    if( fi.isFile() )
    {
        QFile::remove( file );
    }
    else if( fi.isDir() )
    {
        QDir d;
        d.rmpath( file );
    }
}

void ObjectManager::assetDeleted( GluonEngine::Asset* asset )
{
    Q_ASSERT( asset );
    assetDeleted( asset->absolutePath().toLocalFile() );
}

ObjectManager::ObjectManager( QObject* parent )
    : GluonCore::Singleton< GluonCreator::ObjectManager >( parent ), d( new Private() )
{
    connect( KDirWatch::self(), SIGNAL(dirty(QString)), SLOT(assetDirty(QString)) );
    connect( KDirWatch::self(), SIGNAL(created(QString)), SLOT(assetDirty(QString)) );
}

ObjectManager::~ObjectManager()
{

}
