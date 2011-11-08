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

#include "scenemodel.h"
#include "typeinfo"
#include "modeltest.h"

#include "historymanager.h"
#include "objectmanager.h"

#include <core/debughelper.h>
#include <engine/gameobject.h>
#include <engine/component.h>
#include <engine/gameproject.h>
#include <engine/game.h>

#include <KDE/KLocalizedString>

#include <QtCore/QMimeData>

using namespace GluonCreator;

class SceneModel::SceneModelPrivate
{
    public:
        SceneModelPrivate()
        {
            root = 0;
        }

        GluonEngine::GameObject* root;

        int rowIndex( GluonEngine::GameObject* object ) const;
};

SceneModel::SceneModel( QObject* parent ): QAbstractItemModel( parent ), d( new SceneModelPrivate )
{
    setSupportedDragActions( Qt::MoveAction );
    connect( HistoryManager::instance(), SIGNAL(historyChanged(const QUndoCommand*)), SIGNAL(layoutChanged()) );
    //   new ModelTest(this, this);
}

SceneModel::~SceneModel()
{
    delete d;
}

GluonEngine::GameObject* SceneModel::rootGameObject()
{
    return d->root;
}


void SceneModel::setRootGameObject( GluonEngine::GameObject* obj )
{
    if( obj )
    {
        d->root = obj;
        reset();
    }
}

void SceneModel::newGameObject( GluonEngine::GameObject* parent, GluonEngine::GameObject* newChild )
{
    if( parent )
    {
        QModelIndex thisIndex = QModelIndex();
        if( parent->parentGameObject() )
        {
            int row = parent->parentGameObject()->childIndex( parent );
            thisIndex = createIndex( row, 0, parent );
        }
        int childCount = parent->childCount();
        beginInsertRows( thisIndex, childCount, childCount );
        parent->addChild( newChild );
        endInsertRows();
    }
}

void SceneModel::deleteGameObject( GluonEngine::GameObject* obj )
{
    if( obj )
    {
        int row = obj->parentGameObject()->childIndex( obj );
        QModelIndex thisIndex = createIndex( row, 0, obj );
        beginRemoveRows( parent( thisIndex ), row, row );
        obj->parentGameObject()->removeChild( obj );
        obj->deleteLater();
        endRemoveRows();
    }
}

void SceneModel::deleteComponent( GluonEngine::Component* component )
{
    if( component )
    {
        component->gameObject()->removeComponent( component );
        component->deleteLater();
    }
}

QVariant SceneModel::data( const QModelIndex& index, int role ) const
{
    if( !index.isValid() )
        return QVariant();

    if( role == Qt::DisplayRole || role == Qt::EditRole )
    {
        GluonEngine::GameObject* item = static_cast<GluonEngine::GameObject*>( index.internalPointer() );

        if( item )
            return item->name();
    }

    return QVariant();
}

int SceneModel::columnCount( const QModelIndex& ) const
{
    return 1;
}

int SceneModel::rowCount( const QModelIndex& parent ) const
{
    GluonEngine::GameObject* parentItem;
    if( parent.column() > 0 )
        return 0;

    if( !parent.isValid() )
        parentItem = d->root;
    else
        parentItem = static_cast<GluonEngine::GameObject*>( parent.internalPointer() );

    if( parentItem )
        return parentItem->childCount();
    return 0;
}

QModelIndex SceneModel::parent( const QModelIndex& child ) const
{
    if( !child.isValid() )
        return QModelIndex();

    GluonEngine::GameObject* childItem = static_cast<GluonEngine::GameObject*>( child.internalPointer() );

    if( !childItem )
        return QModelIndex();

    GluonEngine::GameObject* parentItem = childItem->parentGameObject();

    if( parentItem == d->root )
        return QModelIndex();

    return createIndex( d->rowIndex( parentItem ), 0, parentItem );
}

QModelIndex SceneModel::index( int row, int column, const QModelIndex& parent ) const
{
    if( !hasIndex( row, column, parent ) )
        return QModelIndex();

    GluonEngine::GameObject* parentItem;

    if( !parent.isValid() )
        parentItem = d->root;
    else
        parentItem = static_cast<GluonEngine::GameObject*>( parent.internalPointer() );

    GluonEngine::GameObject* childItem = parentItem->childGameObject( row );
    if( childItem )
        return createIndex( row, column, childItem );
    else
        return QModelIndex();
}

QModelIndex SceneModel::objectToIndex(GluonCore::GluonObject* object) const
{
    if(object->root() == d->root)
    {
        if(object->parent())
        {
            int row = object->parent()->children().indexOf(object);
            return createIndex( row, 0, object );
        }
    }
    return QModelIndex();
}

QVariant SceneModel::headerData( int /* section */, Qt::Orientation /* orientation */, int /* role */ ) const
{
    return QVariant();
}

Qt::DropActions SceneModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}

Qt::ItemFlags SceneModel::flags( const QModelIndex& index ) const
{
    if( index.isValid() )
        return QAbstractItemModel::flags( index ) | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    else
        return QAbstractItemModel::flags( index ) | Qt::ItemIsDropEnabled;
}

QStringList
SceneModel::mimeTypes() const
{
    QStringList types;
    types << "application/gluon.object.gameobject";
    types << "application/gluon.text.componentclass";
    types << "application/gluon.engine.GluonEngine::Prefab";
    return types;
}

QMimeData* SceneModel::mimeData( const QModelIndexList& indexes ) const
{
    if( indexes.count() <= 0 )
        return 0;

    QStringList types = mimeTypes();
    if( types.isEmpty() )
        return 0;

    QMimeData* data = new QMimeData();
    QStringList names;
    foreach( const QModelIndex & index, indexes )
    {
        names.append( static_cast<GluonEngine::GameObject*>( index.internalPointer() )->fullyQualifiedName() );
    }
    data->setData( "application/gluon.object.gameobject", names.join( ";" ).toUtf8() );

    return data;
}

bool SceneModel::dropMimeData( const QMimeData* data, Qt::DropAction action, int row, int /* column */, const QModelIndex& parent )
{
    DEBUG_FUNC_NAME

    if( action == Qt::IgnoreAction )
        return false;

    if( parent.isValid() )
    {
        GluonEngine::GameObject* gobj = qobject_cast<GluonEngine::GameObject*>( ( QObject* )parent.internalPointer() );

        if( !gobj )
        {
            gobj = d->root;
        }

        foreach( const QString & something, data->formats() )
        {
            DEBUG_TEXT( QString( "Dropped mimetype %1 on object %2" ).arg( something ).arg( gobj->fullyQualifiedName() ) )
        }

        if( data->hasFormat( "application/gluon.engine.GluonEngine::Prefab" ) )
        {
            QByteArray encodedData = data->data( "application/gluon.engine.GluonEngine::Prefab" );
            QDataStream stream( &encodedData, QIODevice::ReadOnly );
            QStringList newItems;

            while( !stream.atEnd() )
            {
                QString text;
                stream >> text;
                newItems << text;
            }
            foreach( const QString & text, newItems )
            {
                DEBUG_TEXT2( "Creating instance for %1", text )
                //ObjectManager::instance()->createNewComponent( text, gobj );
            }
        }

        if( data->hasFormat( "application/gluon.text.componentclass" ) )
        {
            QByteArray encodedData = data->data( "application/gluon.text.componentclass" );
            QDataStream stream( &encodedData, QIODevice::ReadOnly );
            QStringList newItems;
            int rows = 0;

            while( !stream.atEnd() )
            {
                QString text;
                stream >> text;
                newItems << text;
                ++rows;
            }
            foreach( const QString & text, newItems )
            {
                DEBUG_TEXT2( "Adding component of class %1", text )
                ObjectManager::instance()->createNewComponent( text, gobj );
            }
        }

        if( data->hasFormat( "application/gluon.object.gameobject" ) )
        {
            QList<GluonEngine::GameObject*> objects;

            QString dataString = data->data( "application/gluon.object.gameobject" );
            QStringList names = dataString.split( ';' );
            DEBUG_TEXT2( "Dropped names %1 on Scene Model", dataString )

            GluonEngine::GameProject* project = GluonEngine::Game::instance()->gameProject();
            foreach( const QString & name, names )
            {
                GluonEngine::GameObject* gobj = qobject_cast<GluonEngine::GameObject*>( project->findGlobalItemByName( name ) );
                if( gobj )
                    objects.append( gobj );
            }

            foreach( GluonEngine::GameObject * item, objects )
            {
                // Update the view for the old parent (unfortunately we can't expect the items to
                // all be from the same parent, so we have to do it here)
                GluonEngine::GameObject* oldParentObject = qobject_cast< GluonEngine::GameObject* >( item->parentGameObject() );
                QModelIndex oldParent = createIndex( d->rowIndex( oldParentObject ), 0, oldParentObject );
                int oldRow = d->rowIndex( item );
                beginRemoveRows( oldParent, oldRow, oldRow );
                oldParentObject->removeChild( item );
                endRemoveRows();
            }

            insertRows( row, objects, parent );
        }
    }

    return true;
}

bool SceneModel::setData( const QModelIndex& index, const QVariant& value, int role )
{
    if( !index.isValid() )
        return false;

    if( role == Qt::EditRole )
    {
        static_cast<GluonCore::GluonObject*>( index.internalPointer() )->setName( value.toString() );
        emit dataChanged( index, index );
        return true;
    }
    return false;
}

void SceneModel::emitDataChanged(const QModelIndex& index)
{
    emit dataChanged( index, index );
}

bool SceneModel::insertRows( int row, int count, const QModelIndex& parent )
{
    beginInsertRows( parent, row, row + count - 1 );

    GluonEngine::GameObject* obj = static_cast<GluonEngine::GameObject*>( parent.internalPointer() );
    if( !obj )
        obj = d->root;

    for( int i = 0; i < count; ++i )
    {
        obj->addChildAt( new GluonEngine::GameObject(), i );
    }

    endInsertRows();
    return true;
}

bool SceneModel::insertRows( int row, const QList<GluonEngine::GameObject*> &children, const QModelIndex& parent )
{
    DEBUG_FUNC_NAME;
    int count = children.count();

    GluonEngine::GameObject* pobj = static_cast<GluonEngine::GameObject*>( parent.internalPointer() );
    if( !pobj )
        pobj = d->root;

    if( children.at( 0 )->parent() == pobj )
        return false;

    int childCount = pobj->childCount();
    beginInsertRows( parent, childCount, childCount + count - 1 );
    int index = row;
    foreach( GluonEngine::GameObject * obj, children )
    {
        pobj->addChildAt( obj, index++ );
    }
    endInsertRows();
    return true;
}

bool SceneModel::removeRows( int row, int count, const QModelIndex& parent )
{
    return QAbstractItemModel::removeRows( row, count, parent );
}

int SceneModel::SceneModelPrivate::rowIndex( GluonEngine::GameObject* object ) const
{
    if( object )
    {
        if( object->parentGameObject() )
        {
            return object->parentGameObject()->childIndex( object );
        }
    }
    return 0;
}

