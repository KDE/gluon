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

#include "componentsview.h"

#include <creator/lib/models/componentmodel.h>
#include <creator/lib/models/modeltest.h>

#include <core/gluonobjectfactory.h>
#include <core/gluonobject.h>
#include <engine/component.h>

#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>

using namespace GluonCreator;

class ComponentsView::ComponentsViewPrivate
{
    public:
        ComponentsViewPrivate()
            : view( 0 )
            , model( 0 )
        { };

        QTreeView* view;
        ComponentModel* model;
};

ComponentsView::ComponentsView( const QString& title, QWidget* parent, Qt::WindowFlags flags )
    : QWidget( parent, flags )
{
    setObjectName( "ComponentsView" );

    d = new ComponentsViewPrivate();

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

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget( d->view );
    setLayout(layout);
}

ComponentsView::~ComponentsView()
{
    delete d;
}
