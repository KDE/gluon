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
#include <objectmanager.h>

using namespace Gluon;
using namespace Gluon::Creator;

SceneModel::SceneModel(QObject* parent): QAbstractItemModel(parent)
{
    m_root = 0;
    connect(ObjectManager::instance(), SIGNAL(newObject(Gluon::GameObject*)), SIGNAL(layoutChanged()));
}


GameObject* SceneModel::rootGameObject()
{
    if(m_root) return m_root->childGameObject(0);
    return 0;
}


void SceneModel::setRootGameObject(GameObject* obj)
{
    if(obj)
    {
        if(m_root) delete m_root;
        m_root = new GameObject(this);
        m_root->addChild(obj);
        emit layoutChanged();
    }
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

    if(parentItem) return parentItem->childCount();
    return 0;
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

    GameObject *childItem = parentItem->childGameObject(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QVariant SceneModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section)
    Q_UNUSED(orientation)
    Q_UNUSED(role)

    return QVariant();
}

int SceneModel::rowIndex(GameObject* object) const
{
    if(object && object->parentGameObject())
    {
        return object->parentGameObject()->childIndex(object);
    }
    return 0;
}

#include "scenemodel.moc"

