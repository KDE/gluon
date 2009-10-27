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

#include "scenemodel.h"
#include <gluon/gameobject.h>
#include <QDebug>
#include <typeinfo>

using namespace Gluon;
using namespace Gluon::Creator;

SceneModel::SceneModel(QObject* parent): QAbstractItemModel(parent)
{
    m_root = 0;
}


GameObject* SceneModel::rootGameObject()
{
    return m_root->child(0);
}


void SceneModel::setRootGameObject(GameObject* obj)
{
    if(m_root) delete m_root;
    m_root = new GameObject(this);
    m_root->addChild(obj);
}

QVariant SceneModel::data(const QModelIndex& index, int role) const
{
    if (index.isValid() && role == Qt::DisplayRole)
    {
        GameObject *item = static_cast<GameObject*>(index.internalPointer());

        if(item)
            return item->name();
    }

    return QVariant();
}

int SceneModel::columnCount(const QModelIndex&) const
{
    return 1;
}

int SceneModel::rowCount(const QModelIndex& parent) const
{
    GameObject *parentItem;
    if (parent.column() > 0)
        return 0;
    
    if (!parent.isValid())
        parentItem = m_root;
    else
        parentItem = static_cast<GameObject*>(parent.internalPointer());
    
    return parentItem->childCount();
}

QModelIndex SceneModel::parent(const QModelIndex& child) const
{
    if (!child.isValid())
        return QModelIndex();
    
    GameObject *childItem = static_cast<GameObject*>(child.internalPointer());
    GameObject *parentItem = childItem->parentGameObject();
    
    if (parentItem == m_root)
        return QModelIndex();
    
    return createIndex(rowIndex(parentItem), 0, parentItem);
}

QModelIndex SceneModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();
    
    GameObject *parentItem;
    
    if (!parent.isValid())
        parentItem = m_root;
    else
        parentItem = static_cast<GameObject*>(parent.internalPointer());
    
    GameObject *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QVariant SceneModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return QVariant("Name");
    }
    
    return QVariant();
}

int SceneModel::rowIndex(GameObject* object) const
{
    if(object->parentGameObject())
    {   
        return object->parentGameObject()->childIndex(object);
    }
    return 0;
}



