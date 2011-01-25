/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
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
#include "core/debughelper.h"
#include "creator/lib/objectmanager.h"

#include <engine/component.h>

#include <KLocalizedString>

namespace GluonCreator
{
    class ComponentModelItem : public QStandardItem
    {
        public:
            ComponentModelItem()
                : parent( 0 )
            {};

            ComponentModelItem( const ComponentModelItem& other )
                : QStandardItem( )
                , name( other.name )
                , className( other.className )
            {}
            ~ComponentModelItem()
            {
                qDeleteAll( items );
            }
            int row()
            {
                if( parent )
                    return parent->items.indexOf( this );
                return -1;
            }

            QString name;
            QString className;

            ComponentModelItem* parent;
            QList<ComponentModelItem*> items;
            QHash<QString, int> itemNames;
    };
}


using namespace GluonCreator;

class ComponentModel::ComponentModelPrivate
{
    public:
        ComponentModelPrivate()
         : root( new ComponentModelItem() )
        {}

        ComponentModelItem* root;

};

ComponentModel::ComponentModel( QObject* parent )
    : QStandardItemModel( parent )
    , d( new ComponentModelPrivate )
{
    DEBUG_BLOCK

    QHash<QString, const QMetaObject*> objectTypes = GluonCore::GluonObjectFactory::instance()->objectTypes();
    int i = 0;
    foreach( const QMetaObject * obj, objectTypes )
    {
        GluonEngine::Component* comp = qobject_cast<GluonEngine::Component*>( obj->newInstance() );
        if( comp )
        {
            QString name( obj->className() );

            ComponentModelItem* item = new ComponentModelItem();
            item->name = ObjectManager::instance()->humanifyClassName( name );
            item->className = name;

            // Ensure the category exists before attempting to insert anything into it... ;)
            QString category = comp->category();
            if( !d->root->itemNames.contains( category ) )
            {
                ComponentModelItem* categoryItem = new ComponentModelItem();
                categoryItem->name = category;
                categoryItem->parent = d->root;
                d->root->items.append( categoryItem );
                d->root->itemNames.insert( category, i );
                ++i;
            }

            item->parent = d->root->items[ d->root->itemNames[category] ];
            d->root->items[ d->root->itemNames[category] ]->itemNames.insert( item->name, d->root->items[ d->root->itemNames[category] ]->items.count() );
            d->root->items[ d->root->itemNames[category] ]->items.append( item );
        }
        else
        {
            QObject* anobj = obj->newInstance();
            if( anobj )
            {
                if( anobj->inherits( "GluonEngine::Component" ) )
                {
                    DEBUG_TEXT2( "The Component %1 is lacking the Q_INTERFACES(GluonEngine::Component) macro", obj->className() );
                }
            }
        }
    }
}

ComponentModel::~ComponentModel()
{
    delete d;
}
