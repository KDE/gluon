/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "viewmanager.h"

#include <KDE/KXmlGuiWindow>

#include <QtGui/QWidget>

using namespace GluonCreator;

class ViewManager::ViewManagerPrivate
{
    public:
        QList<QWidget*> views;
        KXmlGuiWindow* mainWindow;
};

template<> GLUON_CREATOR_VISIBILITY ViewManager* GluonCore::Singleton<ViewManager>::m_instance = 0;

void ViewManager::addView( QWidget *view, Qt::Orientation orient )
{
    if( d->mainWindow )
    {
        d->views.append( view );
    }
}

void ViewManager::removeView( QWidget* view )
{
    if( d->views.indexOf( view ) != -1 )
    {
        // d->mainWindow->removeDockWidget( dock );
        d->views.removeOne( view );
    }
}

void ViewManager::setViewsEnabled( bool enabled )
{
    foreach( QWidget *view, d->views )
    {
        view->setEnabled( enabled );
    }
}

KXmlGuiWindow* ViewManager::mainWindow()
{
    return d->mainWindow;
}

void ViewManager::setMainWindow( KXmlGuiWindow* window )
{
    d->mainWindow = window;
}

ViewManager::ViewManager()
    : d( new ViewManagerPrivate )
{

}

ViewManager::~ViewManager()
{
    delete d;
}
