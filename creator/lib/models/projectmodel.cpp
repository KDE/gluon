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

#include "projectmodel.h"
#include <engine/game.h>
#include <core/gameproject.h>
#include <core/gluonobject.h>

#include <KDebug>
#include <KLocalizedString>

#include <objectmanager.h>

using namespace GluonCreator;

class ProjectModel::ProjectModelPrivate
{
    public:
        ProjectModelPrivate() { project = 0; }

        QObject* root;
        GluonCore::GameProject* project;

};

ProjectModel::ProjectModel(QObject* parent): QAbstractItemModel(parent)
{
    d = new ProjectModelPrivate;
    connect(ObjectManager::instance(), SIGNAL(newScene(GluonEngine::Scene*)), SIGNAL(layoutChanged()));
}

ProjectModel::~ProjectModel()
{
    delete d;
}


GluonCore::GameProject* ProjectModel::project()
{
    return d->project;
}

void ProjectModel::setProject(GluonCore::GameProject* project)
{
    d->root = new QObject(this);
    d->project = project;
    project->setParent(d->root);

    reset();
}

QVariant ProjectModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    QObject *item = static_cast<QObject*>(index.internalPointer());

    GluonCore::GluonObject* gobj = qobject_cast<GluonCore::GluonObject*>(item);
    if(gobj) return gobj->name();

    return item->objectName() + item->metaObject()->className();
}

int ProjectModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return 1;
}

int ProjectModel::rowCount(const QModelIndex& parent) const
{
    QObject *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = d->root;
    else
        parentItem = static_cast<QObject*>(parent.internalPointer());

    if(parentItem && parentItem->metaObject()->className() != QString("GluonEngine::Scene")) return parentItem->children().count();
    return 0;
}

QModelIndex ProjectModel::parent(const QModelIndex& child) const
{
    if (!child.isValid())
        return QModelIndex();

    QObject *childItem = static_cast<QObject*>(child.internalPointer());
    QObject *parentItem = childItem->parent();

    if (parentItem == d->root)
        return QModelIndex();

    return createIndex(parentItem->children().indexOf(childItem), 0, parentItem);
}

QModelIndex ProjectModel::index(int row, int column, const QModelIndex& parent) const
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

QVariant ProjectModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section)
    Q_UNUSED(orientation)
    Q_UNUSED(role)

    return QVariant();
}

#include "projectmodel.moc"
