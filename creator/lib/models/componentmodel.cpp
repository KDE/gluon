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

#include "componentmodel.h"
#include "core/gluonobject.h"
#include "creator/lib/objectmanager.h"

#include <QtCore/QMimeData>
#include <KLocalizedString>

using namespace GluonCreator;

class ComponentModel::ComponentModelPrivate
{
    public:
        ComponentModelPrivate()
        {};

        QHash<int, QString> names;
        QHash<int, QString> categories;
};

ComponentModel::ComponentModel(QObject* parent)
    : QAbstractListModel(parent)
    , d(new ComponentModelPrivate)
{
    QHash<QString, GluonCore::GluonObject*> objectTypes = GluonCore::GluonObjectFactory::instance()->objectTypes();
    QStringList list;
    int i = 0;
    foreach(GluonCore::GluonObject* obj, objectTypes)
    {
        if (obj->inherits("GluonEngine::Component"))
        {
            QString name(obj->metaObject()->className());
            d->names.insert(i, ObjectManager::instance()->humanifyClassName(name));
            d->categories.insert(i, name.right(name.length() - name.lastIndexOf("::") - 1).replace("::", "/"));
            ++i;
        }
    }
}

ComponentModel::~ComponentModel()
{
    delete d;
}

QVariant
ComponentModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= d->names.count())
        return QVariant();

    if(role == Qt::DisplayRole)
    {
        switch(index.column())
        {
            case 1:
                return d->categories[index.row()];
                break;
            case 0:
            default:
                return d->names[index.row()];
                break;
        }
    }
    return QVariant();
}

QVariant
ComponentModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    
    if (orientation == Qt::Horizontal)
    {
        switch(section)
        {
            case 1:
                return i18n("Category");
                break;
            case 0:
            default:
                return i18n("Component");
                break;
        }
    }
    else
        return QString("Row %1").arg(section);
}

Qt::ItemFlags
ComponentModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractListModel::flags(index);

    if (index.isValid())
        return Qt::ItemIsDragEnabled | defaultFlags;
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
ComponentModel::mimeData(const QModelIndexList& indexes) const
{
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    // There should really only be one, but let's do the loop-de-loop anyway
    foreach(const QModelIndex &index, indexes)
    {
        if (index.isValid())
        {
            QString text = data(index, Qt::DisplayRole).toString();
            stream << text;
        }
    }

    mimeData->setData("application/gluon.text.componentclass", encodedData);
    return mimeData;
}
int ComponentModel::rowCount(const QModelIndex& parent) const
{
    if(parent.isValid())
        return 0;
    return d->names.count();
}

#include "componentmodel.moc"
