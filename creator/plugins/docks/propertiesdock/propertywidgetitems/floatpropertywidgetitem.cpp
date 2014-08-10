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


#include "floatpropertywidgetitem.h"

#include <QtWidgets/QDoubleSpinBox>
#include "cfloat"

REGISTER_PROPERTYWIDGETITEM( GluonCreator, FloatPropertyWidgetItem )

using namespace GluonCreator;

FloatPropertyWidgetItem::FloatPropertyWidgetItem( QWidget* parent, Qt::WindowFlags f )
    : PropertyWidgetItem( parent, f )
{
    QDoubleSpinBox* spinBox = new QDoubleSpinBox( this );
    spinBox->setMinimum( FLT_MIN );
    spinBox->setMaximum( FLT_MAX );
    setEditWidget( spinBox );
    connect( editWidget(), SIGNAL(valueChanged(double)), SLOT(floatValueChanged(double)) );
}

FloatPropertyWidgetItem::~FloatPropertyWidgetItem()
{

}

QList< QString >
FloatPropertyWidgetItem::supportedDataTypes() const
{
    QList<QString> supportedTypes;
    //supportedTypes.append("float");
    return supportedTypes;
}

PropertyWidgetItem*
FloatPropertyWidgetItem::instantiate()
{
    return new FloatPropertyWidgetItem();
}

void FloatPropertyWidgetItem::setEditProperty( const QString& value )
{
    GluonCreator::PropertyWidgetItem::setEditProperty( value );
}

void
FloatPropertyWidgetItem::setEditValue( const QVariant& value )
{
    editWidget()->setProperty( "value", value );
}

void
FloatPropertyWidgetItem::floatValueChanged( double value )
{
    PropertyWidgetItem::valueChanged( QVariant( value ) );
}
