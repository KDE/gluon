/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

#include "componentmodel.h"

#include "lib/objectmanager.h"

#include "engine/component.h"

#include "core/gluonobject.h"
#include "core/debughelper.h"

#include <KDE/KLocalizedString>

#include <QtCore/QMimeData>

namespace GluonCreator
{
    struct ComponentModelItem
    {
        public:
            ComponentModelItem()
                : parent( 0 )
            {};
            ComponentModelItem( const ComponentModelItem& other )
                : name( other.name )
                , className( other.className )
            {}
            ~ComponentModelItem()
            {
                qDeleteAll( items );
            }
            int row()
            {
                if( parent )
                    return parent->items.indexOf( this );
                return -1;
            }

            QString name;
            QString className;

            ComponentModelItem* parent;
            QList<ComponentModelItem*> items;
            QHash<QString, int> itemNames;
    };
}
//Q_DECLARE_METATYPE(GluonCreator::ComponentModelItem);

using namespace GluonCreator;

class ComponentModel::ComponentModelPrivate
{
    public:
        ComponentModelPrivate()
            : root( new ComponentModelItem() )
        {}

        ComponentModelItem* root;
};

ComponentModel::ComponentModel( QObject* parent )
    : QAbstractItemModel( parent )
    , d( new ComponentModelPrivate )
{
    DEBUG_BLOCK

    QHash<QString, const QMetaObject*> objectTypes = GluonCore::GluonObjectFactory::instance()->objectTypes();
    int i = 0;
    foreach( const QMetaObject * obj, objectTypes )
    {
        GluonEngine::Component* comp = qobject_cast<GluonEngine::Component*>( obj->newInstance() );
        if( comp )
        {
            QString name( obj->className() );

            ComponentModelItem* item = new ComponentModelItem();
            item->name = ObjectManager::instance()->humanifyClassName( name );
            item->className = name;

            // Ensure the category exists before attempting to insert anything into it... ;)
            QString category = comp->category();
            if( !d->root->itemNames.contains( category ) )
            {
                ComponentModelItem* categoryItem = new ComponentModelItem();
                categoryItem->name = category;
                categoryItem->parent = d->root;
                d->root->items.append( categoryItem );
                d->root->itemNames.insert( category, i );
                ++i;
            }

            item->parent = d->root->items[ d->root->itemNames[category] ];
            d->root->items[ d->root->itemNames[category] ]->itemNames.insert( item->name, d->root->items[ d->root->itemNames[category] ]->items.count() );
            d->root->items[ d->root->itemNames[category] ]->items.append( item );
        }
        else
        {
            QObject* anobj = obj->newInstance();
            if( anobj )
            {
                if( anobj->inherits( "GluonEngine::Component" ) )
                {
                    DEBUG_TEXT2( "The Component %1 is lacking the Q_INTERFACES(GluonEngine::Component) macro", obj->className() );
                }
            }
        }
    }
}

ComponentModel::~ComponentModel()
{
    delete d;
}

QVariant
ComponentModel::data( const QModelIndex& index, int role ) const
{
    if( !index.isValid() )
        return QVariant();

    const ComponentModelItem* item = static_cast<ComponentModelItem*>( index.internalPointer() );

    switch( role )
    {
        case Qt::ToolTipRole:
            if( item->parent )
                return item->parent->name;
            else
                return QVariant();
            break;
        case Qt::DisplayRole:
            switch( index.column() )
            {
                case 2:
                    return item->className;
                    break;
                case 1:
                    if( item->parent )
                        return item->parent->name;
                    else
                        return QString();
                    break;
                case 0:
                default:
                    return item->name;
                    break;
            }
            break;
        default:
            return QVariant();
            break;
    }
    return QVariant();
}

QVariant
ComponentModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if( role != Qt::DisplayRole )
        return QVariant();

    if( orientation == Qt::Horizontal )
    {
        switch( section )
        {
            case 2:
                return i18n( "Class Name" );
                break;
            case 1:
                return i18n( "Category" );
                break;
            case 0:
            default:
                return i18n( "Component" );
                break;
        }
    }
    else
        return QString( "Row %1" ).arg( section );
}

QModelIndex
ComponentModel::index( int row, int column, const QModelIndex& parent ) const
{
    if( !hasIndex( row, column, parent ) )
        return QModelIndex();

    ComponentModelItem* parentItem;

    if( !parent.isValid() )
        parentItem = d->root;
    else
        parentItem = static_cast<ComponentModelItem*>( parent.internalPointer() );

    ComponentModelItem* childItem = parentItem->items[row];
    if( childItem )
        return createIndex( row, column, childItem );
    else
        return QModelIndex();
}

QModelIndex
ComponentModel::parent( const QModelIndex& child ) const
{
    if( !child.isValid() )
        return QModelIndex();

    ComponentModelItem* childItem = static_cast<ComponentModelItem*>( child.internalPointer() );
    ComponentModelItem* parentItem = childItem->parent;

    if( parentItem == d->root )
        return QModelIndex();

    return createIndex( parentItem->row(), 0, parentItem );
}

Qt::ItemFlags
ComponentModel::flags( const QModelIndex& index ) const
{
    Qt::ItemFlags defaultFlags = QAbstractItemModel::flags( index );
    if( index.isValid() )
    {
        ComponentModelItem* item = static_cast<ComponentModelItem*>( index.internalPointer() );
        if( item->className.isEmpty() )
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable | defaultFlags;
        return Qt::ItemIsDragEnabled | Qt::ItemIsEnabled | Qt::ItemIsSelectable | defaultFlags;
    }
    else
        return defaultFlags;
}

QStringList
ComponentModel::mimeTypes() const
{
    QStringList types;
    types << "application/gluon.text.componentclass";
    return types;
}

QMimeData*
ComponentModel::mimeData( const QModelIndexList& indexes ) const
{
    QMimeData* mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream( &encodedData, QIODevice::WriteOnly );

    // There should really only be one, but let's do the loop-de-loop anyway
    foreach( const QModelIndex & index, indexes )
    {
        if( index.isValid() )
        {
            const ComponentModelItem* item = static_cast<ComponentModelItem*>( index.internalPointer() );
            if( item )
            {
                QString text = item->className;
                stream << text;
            }
        }
    }

    mimeData->setData( "application/gluon.text.componentclass", encodedData );
    return mimeData;
}

int
ComponentModel::rowCount( const QModelIndex& parent ) const
{
    if( parent.column() > 0 )
        return 0;

    ComponentModelItem* parentItem;
    if( !parent.isValid() )
        parentItem = d->root;
    else
        parentItem = static_cast<ComponentModelItem*>( parent.internalPointer() );

    return parentItem->items.count();
}

int
ComponentModel::columnCount( const QModelIndex& parent ) const
{
    Q_UNUSED( parent )
    return 1;
}
