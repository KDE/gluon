/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "componentsdock.h"
#include "models/componentmodel.h"
#include "models/modeltest.h"

#include "core/gluonobjectfactory.h"
#include "core/gluonobject.h"
#include "engine/component.h"

#include <QtGui/QTreeView>

using namespace GluonCreator;

class ComponentsDock::ComponentsDockPrivate
{
    public:
        ComponentsDockPrivate()
            : view( 0 )
            , model( 0 )
        { };

        QTreeView* view;
        ComponentModel* model;
};

ComponentsDock::ComponentsDock( const QString& title, QWidget* parent, Qt::WindowFlags flags )
    : QDockWidget( title, parent, flags )
{
    setObjectName( "ComponentsDock" );

    d = new ComponentsDockPrivate();

    d->view = new QTreeView( this );
    d->view->setSelectionMode( QAbstractItemView::SingleSelection );
    d->view->setDragEnabled( true );
    d->view->setAcceptDrops( false );
    d->view->setDropIndicatorShown( false );
    d->view->setHeaderHidden( true );
    d->view->setIndentation( 0 );
    d->view->setRootIsDecorated( false );
    QString style( "QTreeView::item:has-children {"
                   "color: palette(button-text);"
                   "background-color: palette(button);"
                   "border: 1px solid palette(dark);"
                   "border-radius: 2px;"
                   "}" );
    d->view->setStyleSheet( style );

    d->model = new ComponentModel( this );
    d->view->setModel( d->model );
    d->view->expandAll();

    new ModelTest( d->model, this );

    setWidget( d->view );
}

ComponentsDock::~ComponentsDock()
{
    delete d;
}
