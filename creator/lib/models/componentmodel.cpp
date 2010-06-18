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
#include <KCategorizedSortFilterProxyModel>

namespace GluonCreator
{
    struct ComponentModelItem
    {
        public:
            explicit ComponentModelItem() {};
            explicit ComponentModelItem(const ComponentModelItem& other)
                : name(other.name)
                , category(other.category)
                , className(other.className)
            {};
            ~ComponentModelItem() {};
            
            QString name;
            QString category;
            QString className;
    };
}
Q_DECLARE_METATYPE(GluonCreator::ComponentModelItem);

using namespace GluonCreator;

class ComponentModel::ComponentModelPrivate
{
    public:
        ComponentModelPrivate()
        {};

        QList<ComponentModelItem> items;
        QList<QString> categories;
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
            
            ComponentModelItem item;
            item.name = ObjectManager::instance()->humanifyClassName(name);
            item.category = name.left(name.lastIndexOf("::")).replace("::", "/");
            item.className = name;
            d->items.append(item);
            
            if(!d->categories.contains(item.category))
                d->categories.append(item.category);
            
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
    
    const ComponentModelItem* item = static_cast<ComponentModelItem*>(index.internalPointer());
    
    if(!item)
        return QVariant();
    
    switch(role)
    {
        case KCategorizedSortFilterProxyModel::CategoryDisplayRole:
        case KCategorizedSortFilterProxyModel::CategorySortRole:
            return item->category;
            break;
        case Qt::ToolTipRole:
            return item->category;
            break;
        case Qt::DisplayRole:
            switch(index.column())
            {
                case 2:
                    return item->className;
                    break;
                case 1:
                    return item->category;
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
            case 2:
                return i18n("Class Name");
                break;
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

QModelIndex
ComponentModel::index(int row, int column, const QModelIndex& parent) const
{
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    if(parent.isValid())
        return QModelIndex();
    
    return createIndex(row, column, &d->items[row]);
}

Qt::ItemFlags
ComponentModel::flags(const QModelIndex &index) const
{
    //Qt::ItemFlags defaultFlags = QAbstractListModel::flags(index);
    if (index.isValid())
        return Qt::ItemIsDragEnabled | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    else
        return 0;
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
            QString text = data(createIndex(index.row(), 2, 0), Qt::DisplayRole).toString();
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
    return d->items.count();
}

#include "componentmodel.moc"
