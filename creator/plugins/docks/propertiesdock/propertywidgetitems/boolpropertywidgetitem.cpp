/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

#include "boolpropertywidgetitem.h"

#include <QtWidgets/QCheckBox>

REGISTER_PROPERTYWIDGETITEM( GluonCreator, BoolPropertyWidgetItem )

using namespace GluonCreator;

BoolPropertyWidgetItem::BoolPropertyWidgetItem( QWidget* parent, Qt::WindowFlags f )
    : PropertyWidgetItem( parent, f )
{
    setEditWidget( new QCheckBox( this ) );
    connect( editWidget(), SIGNAL(toggled(bool)), SLOT(toggled(bool)) );
}

BoolPropertyWidgetItem::~BoolPropertyWidgetItem()
{

}

QStringList
BoolPropertyWidgetItem::supportedDataTypes() const
{
    QStringList supportedTypes;
    supportedTypes.append( "bool" );
    return supportedTypes;
}

PropertyWidgetItem*
BoolPropertyWidgetItem::instantiate()
{
    return new BoolPropertyWidgetItem();
}

void
BoolPropertyWidgetItem::setEditValue( const QVariant& value )
{
    editWidget()->setProperty( "checked", value );
}

void
BoolPropertyWidgetItem::toggled( bool checked )
{
    PropertyWidgetItem::valueChanged( QVariant( checked ) );
}
