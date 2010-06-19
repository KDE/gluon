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

namespace GluonCreator
{
    struct ComponentModelItem
    {
        public:
            ComponentModelItem() {};
            ComponentModelItem(const ComponentModelItem& other)
                : name(other.name)
                , category(other.category)
                , className(other.className)
            {};
            ~ComponentModelItem() {};
            
            QString name;
            QString category;
            QString className;
    };
    struct ComponentModelCategory
    {
        public:
            ComponentModelCategory() {};
            ComponentModelCategory(const QString& name)
                :name(name)
            {};
            ComponentModelCategory(const ComponentModelCategory& other)
                : name(other.name)
                , items(other.items)
            {};
            ~ComponentModelCategory() {};
            
            QString name;
            QList<ComponentModelItem> items;
    };
}
Q_DECLARE_METATYPE(GluonCreator::ComponentModelItem);
Q_DECLARE_METATYPE(GluonCreator::ComponentModelCategory);

using namespace GluonCreator;

class ComponentModel::ComponentModelPrivate
{
    public:
        ComponentModelPrivate()
        {};

        QHash<QString, ComponentModelCategory> categories;
        QHash<int, QString> categoryIndexes;
};

ComponentModel::ComponentModel(QObject* parent)
    : QAbstractItemModel(parent)
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
            
            if(!d->categories.contains(item.category))
                d->categories.insert(item.category, ComponentModelCategory(item.category));
            
            d->categories[item.category].items.append(item);
            d->categoryIndexes.insert(i, item.category);
            
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
    
    if(item)
    {
        switch(role)
        {
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
    else
    {
        const ComponentModelCategory* category = static_cast<ComponentModelCategory*>(index.internalPointer());
        if(category)
        {
            switch(role)
            {
                case Qt::DisplayRole:
                    switch(index.column())
                    {
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
        else
            return QVariant();
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
        return createIndex(row, column, &d->categories[d->categoryIndexes[row]]);

    const ComponentModelCategory* category = static_cast<ComponentModelCategory*>(parent.internalPointer());
    if(category)
    {
        return createIndex(row, column, &d->categories[category->name].items[row]);
    }

    return QModelIndex();
}

QModelIndex
ComponentModel::parent(const QModelIndex& child) const
{
    if(!child.isValid())
        return QModelIndex();
    
    const ComponentModelCategory* category = static_cast<ComponentModelCategory*>(child.internalPointer());
    if(category)
    {
        return QModelIndex();
    }
    
    const ComponentModelItem* item = static_cast<ComponentModelItem*>(child.internalPointer());
    if(item)
    {
        return createIndex(d->categoryIndexes.key(item->category), 0, &d->categories[item->category]);
    }
    
    return QModelIndex();
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
            const ComponentModelItem* item = static_cast<ComponentModelItem*>(index.internalPointer());
            if(item)
            {
                QString text = item->className;
                stream << text;
            }
        }
    }

    mimeData->setData("application/gluon.text.componentclass", encodedData);
    return mimeData;
}

int
ComponentModel::rowCount(const QModelIndex& parent) const
{
    if(parent.isValid())
    {
        const ComponentModelCategory* category = static_cast<ComponentModelCategory*>(parent.internalPointer());
        if(category)
            return d->categories[category->name].items.count();
        else
            return 0;
    }
    return d->categories.count();
}

int
ComponentModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return 1;
}

#include "componentmodel.moc"
