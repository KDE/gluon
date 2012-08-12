/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2011 Laszlo Papp <lpapp@kde.org>
 * Copyright (c) 2012 Shreya Pandit <shreya@shreyapandit.com>
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

#include "propertiesdock.h"

#include <creator/lib/widgets/propertywidget.h>
#include <creator/lib/objectmanager.h>
#include <creator/lib/historymanager.h>
#include <QList>
#include <QMetaObject>
#include <QMetaProperty>
#include <creator/lib/widgets/propertywidgetitem.h>
#include <QDebug>
#include <engine/game.h>
#include <engine/component.h>


using namespace GluonCreator;

class PropertiesDock::PropertiesDockPrivate
{
    public:
        PropertiesDockPrivate( PropertyWidget* widget )
            : widget( widget )
        { }

        PropertyWidget* widget;
};

PropertiesDock::PropertiesDock( const QString& title, QWidget* parent, Qt::WindowFlags flags )
    : QDockWidget( title, parent, flags )
    , d( new PropertiesDockPrivate( new PropertyWidget( this ) ) )
{
    setObjectName( "PropertiesDock" );
    setWidget( d->widget );
    countCalls = 0;
    connect( SelectionManager::instance(), SIGNAL(selectionChanged(SelectionManager::SelectionList)), SLOT(selectionChanged(SelectionManager::SelectionList)) );
    connect( d->widget, SIGNAL(propertyChanged(QObject*,QString,QVariant,QVariant)), SLOT(propertyChanged(QObject*,QString,QVariant,QVariant)) );
    connect( ObjectManager::instance(), SIGNAL(newComponent(GluonEngine::Component*)), SLOT(newComponent(GluonEngine::Component*)) );
    connect( ObjectManager::instance(), SIGNAL(propchanged(GluonCore::GluonObject*,QString,QVariant)),d->widget,SIGNAL(propChangedSignal(GluonCore::GluonObject*,QString,QVariant)));
  
}

PropertiesDock::~PropertiesDock()
{
    delete d;
}

void PropertiesDock::selectionChanged( SelectionManager::SelectionList selection )
{
    d->widget->clear();
    if( !selection.empty() )
        d->widget->setObject( selection.at( 0 ) );
}

void PropertiesDock::newComponent( GluonEngine::Component* comp )
{
    if( comp->parent() == d->widget->object() )
    {
        d->widget->setObject( d->widget->object() );
    }
}
  
void PropertiesDock::propertyChanged( QObject* object, QString property, QVariant oldValue, QVariant newValue )
{
    GluonCore::GluonObject* obj = qobject_cast<GluonCore::GluonObject*>( object );
    if( (obj) && (obj->countCalls==0))
    {  ObjectManager::instance()->changeProperty( obj, property, oldValue, newValue);
	obj->countCalls++;
	obj->onRedo = false;
    }
    if(obj->onRedo){obj->countCalls=0;}
}


