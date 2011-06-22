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

using namespace GluonCreator;

class DockManager::DockManagerPrivate
{
    public:
        QList<QDockWidget*> docks;
        KXmlGuiWindow* mainWindow;
};

GLUON_DEFINE_SINGLETON( DockManager )

void DockManager::addDock( QDockWidget* dock, Qt::DockWidgetArea area, Qt::Orientation orient )
{
    if( d->mainWindow )
    {
        d->mainWindow->addDockWidget( area, dock, orient );
        d->docks.append( dock );
    }
}

void DockManager::removeDock( QDockWidget* dock )
{
    if( d->docks.indexOf( dock ) != -1 )
    {
        d->mainWindow->removeDockWidget( dock );
        d->docks.removeOne( dock );
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

DockManager::DockManager( QObject* parent )
    : Singleton< GluonCreator::DockManager >( parent ), d( new DockManagerPrivate )
{

}

DockManager::~DockManager()
{
    delete d;
}
