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
#include "debughelper.h"
#include <game.h>
#include <asset.h>
#include <gameproject.h>
#include <gluonobject.h>
#include <KDebug>
#include <KLocalizedString>
#include <objectmanager.h>
#include <QtCore/QMimeData>
#include <kmimetype.h>
#include <QtCore/QFileInfo>

using namespace Gluon::Creator;

class ProjectModel::ProjectModelPrivate
{
    public:
        ProjectModelPrivate() { project = 0; }

        QObject* root;
        Gluon::GameProject* project;
        QStringList acceptedMimeTypes;
};

Gluon::Creator::ProjectModel::ProjectModel(QObject* parent): QAbstractItemModel(parent)
{
    d = new ProjectModelPrivate;
    connect(ObjectManager::instance(), SIGNAL(newScene(Gluon::Scene*)), SIGNAL(layoutChanged()));
}

Gluon::Creator::ProjectModel::~ProjectModel()
{
    delete d;
}


Gluon::GameProject* Gluon::Creator::ProjectModel::project()
{
    return d->project;
}

void Gluon::Creator::ProjectModel::setProject(Gluon::GameProject* project)
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

    Gluon::GluonObject* gobj = qobject_cast<Gluon::GluonObject*>(item);
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

    if(parentItem && parentItem->metaObject()->className() != QString("Gluon::Scene")) return parentItem->children().count();
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
        if(obj->inherits("Gluon::Asset"))
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
        return QAbstractItemModel::flags(index) | Qt::ItemIsEnabled;
    }
}

QStringList
ProjectModel::mimeTypes() const
{
    if(d->acceptedMimeTypes.count() < 1)
    {
        DEBUG_FUNC_NAME
        d->acceptedMimeTypes.append("application/gluoncreator.projectmodel.gluonobject");
        d->acceptedMimeTypes.append("text/uri-list");
        d->acceptedMimeTypes.append(Gluon::GluonObjectFactory::instance()->objectMimeTypes());
        foreach(QString theName, d->acceptedMimeTypes)
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
    
    if(action == Qt::IgnoreAction)
        return false;
    
    if(!parent.isValid())
        return false;
    
    if(data->hasUrls())
    {
        Gluon::GluonObject *gobj = dynamic_cast<Gluon::GluonObject*>((QObject*)parent.internalPointer());
        foreach(const QUrl& theUrl, data->urls())
        {
            KMimeType::Ptr type = KMimeType::findByUrl(theUrl);
            DEBUG_TEXT(QString("Dropped file %1 of mimetype %2").arg(theUrl.toLocalFile()).arg(type->name()));
            Gluon::Asset* newChild = static_cast<Gluon::Asset*>(Gluon::GluonObjectFactory::instance()->instantiateObjectByMimetype(type->name()));
            if(gobj)
            {
                gobj->addChild(newChild);
                #warning Copy the file to newChild->fullyQualifiedName() + filetype, and set this as the filename in stead...
                newChild->setName(QFileInfo(theUrl.path()).fileName());
                newChild->setFile(theUrl);
            }
            else
            {
                //\TODO Some error handling might be nice here...
            }
        }
    }
    else if(data->hasFormat("application/gluoncreator.projectmodel.gluonobject"))
    {
    }
    else
    {
    }
    
    if(data->formats().length() < 1)
        return false;
    
    return QAbstractItemModel::dropMimeData(data, action, row, column, parent);
}


bool
ProjectModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        static_cast<Gluon::GluonObject*>(index.internalPointer())->setName(value.toString());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

#include "projectmodel.moc"
