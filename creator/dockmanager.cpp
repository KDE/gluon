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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301  USA
 */

#include "dockmanager.h"

#include <KDE/KXmlGuiWindow>

#include <QtGui/QDockWidget>
#include <QtGui/QAction>

using namespace GluonCreator;

class DockManager::DockManagerPrivate
{
    public:
        QList<QDockWidget*> docks;
        QList<QAction*> dockVisibilityActions;
        KXmlGuiWindow* mainWindow;
};

bool sortActions( QAction* first, QAction* second )
{
    return first->text() < second->text();
}

GLUON_DEFINE_SINGLETON( DockManager )

void DockManager::addDock( QDockWidget* dock, Qt::DockWidgetArea area, Qt::Orientation orient )
{
    if( d->mainWindow )
    {
        d->mainWindow->addDockWidget( area, dock, orient );
        d->docks.append( dock );
        d->dockVisibilityActions.append( dock->toggleViewAction() );

        updateDockActions();
    }
}

void DockManager::removeDock( QDockWidget* dock )
{
    if( d->docks.indexOf( dock ) != -1 )
    {
        d->mainWindow->removeDockWidget( dock );
        d->docks.removeOne( dock );
        d->dockVisibilityActions.removeOne( dock->toggleViewAction() );

        updateDockActions();
    }
}

void DockManager::setDocksEnabled( bool enabled )
{
    foreach( QDockWidget * dock, d->docks )
    {
        dock->setEnabled( enabled );
    }
}

void DockManager::setDocksLocked( bool locked )
{
    foreach( QDockWidget * dock, d->docks )
    {
        if( locked )
        {
            dock->setFeatures( QDockWidget::NoDockWidgetFeatures );
        }
        else
        {
            dock->setFeatures( QDockWidget::AllDockWidgetFeatures );
        }
    }
}

KXmlGuiWindow* DockManager::mainWindow()
{
    return d->mainWindow;
}

void DockManager::setMainWindow( KXmlGuiWindow* window )
{
    d->mainWindow = window;
}

void DockManager::updateDockActions()
{
    if( d->mainWindow )
    {
        d->mainWindow->unplugActionList( "dock_visibility_actions" );
        qSort( d->dockVisibilityActions.begin(), d->dockVisibilityActions.end(), sortActions );
        d->mainWindow->plugActionList( "dock_visibility_actions", d->dockVisibilityActions );
    }
}

DockManager::DockManager( QObject* parent )
    : GluonCore::Singleton< GluonCreator::DockManager >( parent ), d( new DockManagerPrivate )
{

}

DockManager::~DockManager()
{
    delete d;
}
