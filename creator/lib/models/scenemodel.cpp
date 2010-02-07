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
#include <qmimedata.h>
#include <KLocalizedString>
#include <typeinfo>

#include <core/debughelper.h>
#include <engine/gameobject.h>
#include <engine/component.h>
#include <objectmanager.h>

using namespace GluonCreator;

SceneModel::SceneModel(QObject* parent): QAbstractItemModel(parent)
{
    m_root = 0;
    setSupportedDragActions(Qt::MoveAction);
    connect(ObjectManager::instance(), SIGNAL(newGameObject(GluonEngine::GameObject*)), SIGNAL(layoutChanged()));
}


GluonEngine::GameObject* SceneModel::rootGameObject()
{
    if(m_root) return m_root->childGameObject(0);
    return 0;
}


void SceneModel::setRootGameObject(GluonEngine::GameObject* obj)
{
    if(obj)
    {
        m_root = obj;

        reset();
    }
}

QVariant SceneModel::data(const QModelIndex& index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        GluonEngine::GameObject *item = static_cast<GluonEngine::GameObject*>(index.internalPointer());

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
    GluonEngine::GameObject *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = m_root;
    else
        parentItem = static_cast<GluonEngine::GameObject*>(parent.internalPointer());

    if(parentItem) return parentItem->childCount();
    return 0;
}

QModelIndex SceneModel::parent(const QModelIndex& child) const
{
    if (!child.isValid())
        return QModelIndex();

    GluonEngine::GameObject *childItem = static_cast<GluonEngine::GameObject*>(child.internalPointer());

    if(!childItem)
        return QModelIndex();

    GluonEngine::GameObject *parentItem = childItem->parentGameObject();

    if (parentItem == m_root)
        return QModelIndex();

    return createIndex(rowIndex(parentItem), 0, parentItem);
}

QModelIndex SceneModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    GluonEngine::GameObject *parentItem;

    if (!parent.isValid())
        parentItem = m_root;
    else
        parentItem = static_cast<GluonEngine::GameObject*>(parent.internalPointer());

    GluonEngine::GameObject *childItem = parentItem->childGameObject(row);
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

int SceneModel::rowIndex(GluonEngine::GameObject* object) const
{
    if(object)
    {
        if(object->parentGameObject())
        {
            return object->parentGameObject()->childIndex(object);
        }
    }
    return 0;
}


Qt::DropActions SceneModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}

Qt::ItemFlags SceneModel::flags(const QModelIndex& index) const
{
    if (index.isValid())
        return QAbstractItemModel::flags(index) | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    else
        return QAbstractItemModel::flags(index) | Qt::ItemIsDropEnabled | Qt::ItemIsEnabled;
}

QStringList
SceneModel::mimeTypes() const
{
    QStringList types;
    types << "application/gluon.object.gameobject";
    types << "application/gluon.text.componentclass";
    return types;
}

QMimeData* SceneModel::mimeData(const QModelIndexList& indexes) const
{
    return QAbstractItemModel::mimeData(indexes);
}

bool SceneModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent)
{
    DEBUG_FUNC_NAME

    if(action == Qt::IgnoreAction)
        return false;

    if(parent.isValid()) {
        GluonEngine::GameObject *gobj = qobject_cast<GluonEngine::GameObject*>((QObject*)parent.internalPointer());

        if(!gobj) {
            gobj = m_root;
        }

        foreach(QString something, data->formats())
        {
            DEBUG_TEXT(QString("Dropped mimetype %1 on object %2").arg(something).arg(gobj->fullyQualifiedName()));
        }

        if(data->hasFormat("application/gluon.text.componentclass")) {
            QByteArray encodedData = data->data("application/gluon.text.componentclass");
            QDataStream stream(&encodedData, QIODevice::ReadOnly);
            QStringList newItems;
            int rows = 0;

            while (!stream.atEnd())
            {
                QString text;
                stream >> text;
                newItems << text;
                ++rows;
            }
            foreach(QString text, newItems)
            {
                DEBUG_TEXT(QString("Adding component of class %1").arg(text));
                ObjectManager::instance()->createNewComponent(text, gobj);
            }
        }

        if(data->hasFormat("application/gluon.object.gameobject")) {
            DEBUG_TEXT("TODO: Implement move of objects");
        }
    }

    return true;
}

bool SceneModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    DEBUG_FUNC_NAME
    if(!index.isValid())
        return false;

    if (role == Qt::EditRole) {
        DEBUG_TEXT(value.typeName());
        static_cast<GluonCore::GluonObject*>(index.internalPointer())->setName(value.toString());
        emit dataChanged(index, index);
        return true;
    } else {
        DEBUG_TEXT(value.typeName());
        DEBUG_TEXT(value.toString());
    }
    return false;
}

bool SceneModel::insertRows(int row, int count, const QModelIndex& parent)
{
    beginInsertRows(parent, row, row + count - 1);

    GluonEngine::GameObject* obj = static_cast<GluonEngine::GameObject*>(parent.internalPointer());
    if(!obj)
        obj = m_root;

    for (int i = 0; i < count; ++i) {
        obj->addChild(new GluonEngine::GameObject());
    }

    endInsertRows();
    return true;
}

bool SceneModel::removeRows(int row, int count, const QModelIndex& parent)
{
    DEBUG_FUNC_NAME
    beginRemoveRows(parent, row, row + count - 1);
    GluonEngine::GameObject* obj = static_cast<GluonEngine::GameObject*>(parent.internalPointer());
    if(!obj) {
        obj = m_root;
    }

    while(count > 0)
    {
        GluonEngine::GameObject* child = obj->childGameObject(row);
        obj->removeChild(child);
        delete child;
        count--;
    }

    endRemoveRows();
    return true;
}

#include "scenemodel.moc"

