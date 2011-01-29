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
#include "projectmodel.h"

#include "core/gluonobject.h"
#include "core/debughelper.h"
#include "engine/game.h"
#include "engine/gameproject.h"
#include "engine/asset.h"
#include "engine/scene.h"

#include <KDebug>
#include <KLocalizedString>
#include <KMimeType>
#include <KIcon>

#include <QtCore/QMimeData>
#include <kmimetype.h>
#include <QtCore/QFileInfo>
#include <engine/filelocation.h>
#include <QDir>
#include <historymanager.h>
#include <objectmanager.h>

using namespace GluonCreator;

class ProjectModel::ProjectModelPrivate
{
    public:
        ProjectModelPrivate()
        {
            root = 0;
            project = 0;
        }

        QObject* root;
        GluonEngine::GameProject* project;

        QStringList acceptedMimeTypes;
};

ProjectModel::ProjectModel( QObject* parent ): QAbstractItemModel( parent ), d( new ProjectModelPrivate )
{
    connect( HistoryManager::instance(), SIGNAL( historyChanged( const QUndoCommand* ) ), SIGNAL( layoutChanged() ) );
}

ProjectModel::~ProjectModel()
{
    delete d;
}


GluonEngine::GameProject*
ProjectModel::project()
{
    return d->project;
}

void
ProjectModel::setProject( GluonEngine::GameProject* project )
{
    if( project )
    {
        d->root = new QObject( this );
        d->project = project;
        project->setParent( d->root );

        reset();
    }
}

QVariant
ProjectModel::data( const QModelIndex& index, int role ) const
{
    if( !index.isValid() )
        return QVariant();

    if( role == Qt::DecorationRole )
    {
        GluonCore::GluonObject* gobj = qobject_cast<GluonCore::GluonObject*>( static_cast<QObject*>( index.internalPointer() ) );
        if( gobj )
        {
            QVariant filename = gobj->property( "file" );
            QString classname( gobj->metaObject()->className() );
            if( classname == QLatin1String( "GluonCore::GluonObject" ) )
            {
                // In this case we're dealing with something which is a "folder"... show it as such
                return KIcon( "folder" );
            }
            if( qobject_cast<GluonEngine::Asset*>( gobj ) )
            {
                QIcon icon = qobject_cast<GluonEngine::Asset*>( gobj )->icon();
                if( icon.isNull() )
                {
                    if( filename.isValid() )
                    {
                        // If the asset doesn't provide an icon itself, but we do have a filename
                        // Get the icon for the mimetype of that url
                        QString name = filename.value<QString>();
                        return KIcon( KMimeType::iconNameForUrl( KUrl( name ) ) );
                    }
                    else
                        return KIcon( "unknown" );
                }
                return icon;
            }
            else
                return KIcon( "text-x-generic" );
        }
    }

    if( role == Qt::DisplayRole || role == Qt::EditRole )
    {
        GluonCore::GluonObject* gobj = qobject_cast<GluonCore::GluonObject*>( static_cast<QObject*>( index.internalPointer() ) );
        if( gobj )
            return gobj->name();
    }

    return QVariant();
}

int
ProjectModel::columnCount( const QModelIndex& parent ) const
{
    Q_UNUSED( parent )
    return 1;
}

int
ProjectModel::rowCount( const QModelIndex& parent ) const
{
    if( parent.column() > 0 )
        return 0;

    QObject* parentItem = d->root;
    if( parent.isValid() )
        parentItem = static_cast<QObject*>( parent.internalPointer() );

    if( parentItem )
    {
        if( qobject_cast<GluonCore::GluonObject*>( parentItem ) )
        {
            if( qobject_cast<GluonEngine::Scene*>( parentItem ) )
                return 0;

            int childCount = 0;
            const QObjectList allChildren = parentItem->children();
            foreach( const QObject * child, allChildren )
            {
                if( qobject_cast<const GluonCore::GluonObject* >( child ) )
                    ++childCount;
            }
            return childCount;
        }
        else
            return parentItem->children().count();
    }

    return 0;
}

QModelIndex
ProjectModel::parent( const QModelIndex& child ) const
{
    if( !child.isValid() )
        return QModelIndex();

    QObject* childItem = static_cast<QObject*>( child.internalPointer() );
    QObject* parentItem = childItem->parent();

    if( parentItem == d->root )
        return QModelIndex();

    QObject* grandParent = parentItem->parent();
    if( grandParent )
    {
        int childCount = -1;
        const QObjectList allChildren = grandParent->children();
        foreach( const QObject * grandChild, allChildren )
        {
            if( qobject_cast<const GluonCore::GluonObject* >( grandChild ) )
                ++childCount;
            if( grandChild == parentItem )
                return createIndex( childCount, 0, parentItem );
        }
    }
    return createIndex( -1, 0, grandParent );
}

QModelIndex
ProjectModel::index( int row, int column, const QModelIndex& parent ) const
{
    if( !hasIndex( row, column, parent ) )
        return QModelIndex();

    QObject* parentItem = d->root;
    if( parent.isValid() )
        parentItem = static_cast<QObject*>( parent.internalPointer() );

    int childCount = -1;
    const QObjectList allChildren = parentItem->children();
    foreach( const QObject * child, allChildren )
    {
        if( qobject_cast<const GluonCore::GluonObject*>( child ) )
            ++childCount;
        if( childCount == row )
            return createIndex( row, column, const_cast<QObject*>( child ) );
    }

    return QModelIndex();
}

QVariant
ProjectModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    Q_UNUSED( section )
    Q_UNUSED( orientation )
    Q_UNUSED( role )

    return QVariant();
}

Qt::DropActions
ProjectModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction | Qt::LinkAction;
}

Qt::ItemFlags
ProjectModel::flags( const QModelIndex& index ) const
{
    if( index.isValid() )
    {
        //QObject* obj = static_cast<QObject*>( index.internalPointer() );
        GluonEngine::Asset* obj = qobject_cast<GluonEngine::Asset*>(static_cast<QObject*>(index.internalPointer()));
        // One does not simply drop Assets into Mord...other Assets!
        if( obj )//->inherits( "GluonEngine::Asset" ) )
        {
            return QAbstractItemModel::flags( index ) | Qt::ItemIsDragEnabled | Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        }
        else
        {
            return QAbstractItemModel::flags( index ) | Qt::ItemIsDragEnabled | Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDropEnabled;
        }
    }
    else
    {
        return Qt::ItemIsDropEnabled;
    }
}

QStringList
ProjectModel::mimeTypes() const
{
    if( d->acceptedMimeTypes.count() < 1 )
    {
        DEBUG_FUNC_NAME
        d->acceptedMimeTypes.append( "application/gluoncreator.projectmodel.gluonobject" );
        d->acceptedMimeTypes.append( "text/uri-list" );
        d->acceptedMimeTypes.append( GluonCore::GluonObjectFactory::instance()->objectMimeTypes() );
        foreach( const QString & theName, d->acceptedMimeTypes )
        {
            DEBUG_TEXT( QString( "%1" ).arg( theName ) );
        }
    }

    return d->acceptedMimeTypes;
}

QMimeData* ProjectModel::mimeData( const QModelIndexList& indexes ) const
{
    if( indexes.count() <= 0 )
        return 0;

    QStringList types = mimeTypes();
    if( types.isEmpty() )
        return 0;

    QMimeData* data = new QMimeData();
    QByteArray encodedData;

    QDataStream stream( &encodedData, QIODevice::WriteOnly );

    // There should really only be one, but let's do the loop-de-loop anyway
    foreach( const QModelIndex & index, indexes )
    {
        if( index.isValid() )
        {
            const GluonEngine::Asset* item = static_cast<GluonEngine::Asset*>( index.internalPointer() );
            if( item )
            {
                QString text = item->fullyQualifiedName();
                stream << text;
            }
        }
    }

    data->setData( "application/gluoncreator.projectmodel.gluonobject", encodedData );

    return data;
}

bool
ProjectModel::dropMimeData( const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent )
{
    Q_UNUSED( row )
    Q_UNUSED( column )
    DEBUG_FUNC_NAME

    if( action == Qt::IgnoreAction )
        return false;

    if( data->hasUrls() )
    {
        foreach( const QUrl & theUrl, data->urls() )
        {
            ObjectManager::instance()->createNewAsset( theUrl.toLocalFile() );
        }
        return true;
    }
    else if( data->hasFormat( "application/gluoncreator.projectmodel.gluonobject" ) )
    {
        QByteArray encodedData = data->data( "application/gluoncreator.projectmodel.gluonobject" );
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

        foreach(const QString& item, newItems)
        {
            GluonCore::GluonObject* itemObject = d->project->findItemByName(item);
            if( itemObject )
            {
                GluonCore::GluonObject* newParentObject = static_cast<GluonCore::GluonObject*>(parent.internalPointer());
                newParentObject->addChild(itemObject);
            }
        }
        return true;
    }

    return false;
}


bool
ProjectModel::setData( const QModelIndex& index, const QVariant& value, int role )
{
    if( index.isValid() && role == Qt::EditRole )
    {
        static_cast<GluonCore::GluonObject*>( index.internalPointer() )->setName( value.toString() );
        emit dataChanged( index, index );
        return true;
    }
    return false;
}

bool
ProjectModel::removeRows( int row, int count, const QModelIndex& parent )
{
    DEBUG_FUNC_NAME
    if( !parent.isValid() )
        return false;

    if( count < 1 )
        return false;

    GluonCore::GluonObject* parentObject = static_cast<GluonCore::GluonObject*>( parent.internalPointer() );
    DEBUG_TEXT( "Object removal begins..." );

    beginRemoveRows( parent, row, row + count - 1 );
    for( int i = row; i < row + count; ++i )
    {
        DEBUG_TEXT( QString( "Removing child at row %1" ).arg( i ) );
        GluonCore::GluonObject* child = parentObject->child( row );
        if( parentObject->removeChild( child ) )
            delete child;
    }
    endRemoveRows();

    return true;
}

void ProjectModel::addChild( QObject* newChild, QModelIndex& parent )
{
    if( parent.isValid() )
    {
        GluonCore::GluonObject* parentObject = static_cast<GluonCore::GluonObject*>( parent.internalPointer() );

        GluonCore::GluonObject* newObject = qobject_cast<GluonCore::GluonObject*>( newChild );
        if( newChild->parent() == parentObject )
        {
            //Remove the children from the parent to let rowCount return
            //an exact count.
            parentObject->removeChild( newObject );
        }
        int rcount = rowCount( parent );
        beginInsertRows( parent, rcount, rcount );

        parentObject->addChild( newObject );

        endInsertRows();
    }
}

//#include "projectmodel.moc"
