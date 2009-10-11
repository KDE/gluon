/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "gameobjecttreemodel.h"
#include <gameobject.h>
#include <QDebug>
#include <typeinfo>

GameObjectTreeModel::GameObjectTreeModel(Gluon::GameObject* root, QObject* parent): QAbstractItemModel(parent)
{
    m_root = new QObject();
    root->setParent(m_root);
}

QVariant GameObjectTreeModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();
    
    if (role != Qt::DisplayRole)
        return QVariant();
    
    Gluon::GameObject *item = static_cast<Gluon::GameObject*>(index.internalPointer());

    switch(index.column())
    {
        case 0:
            return item->name();
            break;
        case 1:
            return item->metaObject()->className();
            break;
        default:
            return QVariant();
    }
}

int GameObjectTreeModel::columnCount(const QModelIndex&) const
{
    return 2;
}

int GameObjectTreeModel::rowCount(const QModelIndex& parent) const
{
    QObject *parentItem;
    if (parent.column() > 0)
        return 0;
    
    if (!parent.isValid())
        parentItem = m_root;
    else
        parentItem = static_cast<QObject*>(parent.internalPointer());

    return parentItem->children().count();
}

QModelIndex GameObjectTreeModel::parent(const QModelIndex& child) const
{
    if (!child.isValid())
        return QModelIndex();
    
    QObject *childItem = static_cast<QObject*>(child.internalPointer());
    QObject *parentItem = childItem->parent();
    
    if (parentItem == m_root)
        return QModelIndex();
    
    return createIndex(rowIndex(parentItem), 0, parentItem);
}

QModelIndex GameObjectTreeModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();
    
    QObject *parentItem;
    
    if (!parent.isValid())
        parentItem = m_root;
    else
        parentItem = static_cast<QObject*>(parent.internalPointer());
    
    QObject *childItem = parentItem->children().at(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QVariant GameObjectTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch(section)
        {
            case 0:
                return QVariant("Name");
                break;
            case 1:
                return QVariant("Type");
                break;
            default:
                return QVariant();
        }
    }
    
    return QVariant();
}

int GameObjectTreeModel::rowIndex(QObject* object) const
{
    if(object->parent())
    {   
        return object->parent()->children().indexOf(object);
    }
    return 0;
}



