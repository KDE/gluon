/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <>
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

ProjectModel::ProjectModel(QObject* parent): QAbstractItemModel(parent), d(new ProjectModelPrivate)
{
    connect(HistoryManager::instance(), SIGNAL(historyChanged()), SIGNAL(layoutChanged()));
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
ProjectModel::setProject(GluonEngine::GameProject* project)
{
    d->root = new QObject(this);
    d->project = project;
    project->setParent(d->root);

    reset();
}

QVariant
ProjectModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        GluonCore::GluonObject* gobj = qobject_cast<GluonCore::GluonObject*>(static_cast<QObject*>(index.internalPointer()));
        if (gobj)
            return gobj->name();
    }

    return QVariant();
}

int
ProjectModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return 1;
}

int
ProjectModel::rowCount(const QModelIndex& parent) const
{
    QObject *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = d->root;
    else
        parentItem = static_cast<QObject*>(parent.internalPointer());

    if (parentItem)
        if (!qobject_cast<GluonEngine::Scene*>(parentItem))
            return parentItem->children().count();

    return 0;
}

QModelIndex
ProjectModel::parent(const QModelIndex& child) const
{
    if (!child.isValid())
        return QModelIndex();

    QObject *childItem = static_cast<QObject*>(child.internalPointer());
    QObject *parentItem = childItem->parent();

    if (parentItem == d->root)
        return QModelIndex();

    return createIndex(parentItem->children().indexOf(childItem), 0, parentItem);
}

QModelIndex
ProjectModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    QObject *parentItem;

    if (!parent.isValid())
        parentItem = d->root;
    else
        parentItem = static_cast<QObject*>(parent.internalPointer());

    QObject *childItem = parentItem->children().at(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QVariant
ProjectModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section)
    Q_UNUSED(orientation)
    Q_UNUSED(role)

    return QVariant();
}

Qt::DropActions
ProjectModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction | Qt::LinkAction;
}

Qt::ItemFlags
ProjectModel::flags(const QModelIndex& index) const
{
    if (index.isValid())
    {
        QObject * obj = static_cast<QObject*>(index.internalPointer());
        //Gluon::Asset *obj = qobject_cast<Gluon::Asset*>();
        // One does not simply drop Assets into Mord...other Assets!
        if (obj->inherits("GluonEngine::Asset"))
        {
            return QAbstractItemModel::flags(index) | Qt::ItemIsDragEnabled | Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        }
        else
        {
            return QAbstractItemModel::flags(index) | Qt::ItemIsDragEnabled | Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDropEnabled;
        }
    }
    else
    {
        return QAbstractItemModel::flags(index) | Qt::ItemIsEnabled | Qt::ItemIsDropEnabled;
    }
}

QStringList
ProjectModel::mimeTypes() const
{
    if (d->acceptedMimeTypes.count() < 1)
    {
        DEBUG_FUNC_NAME
        d->acceptedMimeTypes.append("application/gluoncreator.projectmodel.gluonobject");
        d->acceptedMimeTypes.append("text/uri-list");
        d->acceptedMimeTypes.append(GluonCore::GluonObjectFactory::instance()->objectMimeTypes());
        foreach(const QString &theName, d->acceptedMimeTypes)
        {
            DEBUG_TEXT(QString("%1").arg(theName));
        }
    }

    return d->acceptedMimeTypes;
}

bool
ProjectModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent)
{
    Q_UNUSED(row)
    Q_UNUSED(column)
    DEBUG_FUNC_NAME

    if (action == Qt::IgnoreAction)
        return false;

    if (data->hasUrls())
    {
        GluonCore::GluonObject *gobj = static_cast<GluonCore::GluonObject*>(parent.internalPointer());
        foreach(const QUrl& theUrl, data->urls())
        {
            ObjectManager::instance()->createNewAsset(theUrl.toLocalFile());
        }
    }
    else if (data->hasFormat("application/gluoncreator.projectmodel.gluonobject"))
    {
    }
    else
    {
    }

    if (data->formats().length() < 1)
        return false;

    return QAbstractItemModel::dropMimeData(data, action, row, column, parent);
}


bool
ProjectModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        static_cast<GluonCore::GluonObject*>(index.internalPointer())->setName(value.toString());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool
ProjectModel::removeRows(int row, int count, const QModelIndex& parent)
{
    DEBUG_FUNC_NAME
    if (!parent.isValid())
        return false;

    GluonCore::GluonObject * parentObject = static_cast<GluonCore::GluonObject*>(parent.internalPointer());
    DEBUG_TEXT("Object removal begins...");

    beginRemoveRows(parent, row, row + count);
    for (int i = row; i < row + count; ++i)
    {
        DEBUG_TEXT(QString("Removing child at row %1").arg(i));
        GluonCore::GluonObject * child = parentObject->child(row);
        if (parentObject->removeChild(child))
            delete(child);
    }
    endRemoveRows();

    return true;
}


#include "projectmodel.moc"
