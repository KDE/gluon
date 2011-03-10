/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Laszlo Papp <djszapi@archlinux.us>
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

#include "toolmanager.h"

#include <KDE/KXmlGuiWindow>

using namespace GluonCreator;

class ToolManager::Private
{
    public:
        explicit Private() {}
        virtual ~Private() {}
        // QList<QDockWidget*> tools;
        KXmlGuiWindow* mainWindow;
};

template<> GLUON_CREATOR_VISIBILITY ToolManager* GluonCore::Singleton<ToolManager>::m_instance = 0;

/*
void ToolManager::addTool( QDockWidget* tool, Qt::DockWidgetArea area, Qt::Orientation orient )
{
    if( d->mainWindow )
    {
        d->mainWindow->addDockWidget( area, dock, orient );
        d->tools.append( tool );
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
    foreach( QDockWidget* dock, d->docks )
    {
        dock->setEnabled( enabled );
    }
}
*/

KXmlGuiWindow* ToolManager::mainWindow()
{
    return d->mainWindow;
}

void ToolManager::setMainWindow( KXmlGuiWindow* window )
{
    d->mainWindow = window;
}

ToolManager::ToolManager()
    : d( new Private )
{

}

ToolManager::~ToolManager()
{
    delete d;
}
