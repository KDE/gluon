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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "propertiesview.h"

#include <creator/lib/widgets/propertywidget.h>
#include <creator/lib/objectmanager.h>
#include <creator/lib/historymanager.h>

#include <engine/game.h>
#include <engine/component.h>

#include <QtGui/QVBoxLayout>

using namespace GluonCreator;

class PropertiesView::PropertiesViewPrivate
{
    public:
        PropertiesViewPrivate( PropertyWidget* widget )
            : widget( widget )
        { }

        PropertyWidget* widget;
};

PropertiesView::PropertiesView( QWidget* parent, Qt::WindowFlags flags )
    : QWidget( parent, flags )
    , d( new PropertiesViewPrivate( new PropertyWidget( this ) ) )
{
    setObjectName( "PropertiesView" );

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget( d->widget );
    setLayout( layout );

    connect( SelectionManager::instance(), SIGNAL( selectionChanged( SelectionManager::SelectionList ) ), SLOT( selectionChanged( SelectionManager::SelectionList ) ) );
    connect( d->widget, SIGNAL( propertyChanged( QObject*, QString, QVariant, QVariant ) ), SLOT( propertyChanged( QObject*, QString, QVariant, QVariant ) ) );
    connect( ObjectManager::instance(), SIGNAL( newComponent( GluonEngine::Component* ) ), SLOT( newComponent( GluonEngine::Component* ) ) );
}

PropertiesView::~PropertiesView()
{
    delete d;
}

void PropertiesView::selectionChanged( SelectionManager::SelectionList selection )
{
    d->widget->clear();
    if( !selection.empty() )
        d->widget->setObject( selection.at( 0 ) );
}

void PropertiesView::newComponent( GluonEngine::Component* comp )
{
    if( comp->parent() == d->widget->object() )
    {
        d->widget->setObject( d->widget->object() );
    }
}

void PropertiesView::propertyChanged( QObject* object, QString property, QVariant oldValue, QVariant newValue )
{
    GluonCore::GluonObject* obj = qobject_cast<GluonCore::GluonObject*>( object );

    if( obj )
        ObjectManager::instance()->changeProperty( obj, property, oldValue, newValue );
}


