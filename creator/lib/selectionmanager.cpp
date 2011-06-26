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

#include "selectionmanager.h"
#include "engine/asset.h"
#include "engine/savable.h"

using namespace GluonCreator;

class SelectionManager::SelectionManagerPrivate
{
    public:
        SelectionManagerPrivate()
            : savableContext( 0 )
        { }

        SelectionList selection;
        GluonEngine::Asset* savableContext;
};

GLUON_DEFINE_SINGLETON( SelectionManager )

SelectionManager::SelectionManager( QObject* parent )
    : Singleton< GluonCreator::SelectionManager >( parent ), d( new SelectionManagerPrivate )
{

}

SelectionManager::~SelectionManager()
{
    delete d;
}

SelectionManager::SelectionList SelectionManager::selection() const
{
    return d->selection;
}

GluonEngine::Asset* SelectionManager::savableContext() const
{
    return d->savableContext;
}

void SelectionManager::setSelection( const SelectionManager::SelectionList& selection )
{
    d->selection = selection;

    GluonEngine::Asset* newSavableContext;
    foreach(GluonCore::GluonObject* item, selection)
    {
        QObject* theParent = item;
        while( theParent )
        {
            GluonEngine::Savable* tmpSavable = dynamic_cast<GluonEngine::Savable*>( theParent );
            if( tmpSavable )
            {
                newSavableContext = qobject_cast< GluonEngine::Asset* >( theParent );
                break;
            }
            theParent = item->parent();
        }
        if( newSavableContext )
            break;
    }
    d->savableContext = newSavableContext;

    emit selectionChanged( selection );
}

void SelectionManager::clearSelection()
{
    d->selection.clear();
    d->savableContext = 0;
    emit selectionChanged( d->selection );
}
