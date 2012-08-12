/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "textpropertywidgetitem.h"

REGISTER_PROPERTYWIDGETITEM( GluonCreator, TextPropertyWidgetItem )

using namespace GluonCreator;

TextPropertyWidgetItem::TextPropertyWidgetItem( QWidget* parent, Qt::WindowFlags f ): PropertyWidgetItem( parent, f )
{
    lineEdit = new KLineEdit( this );
    setEditWidget(lineEdit);
    connect( editWidget(), SIGNAL(textEdited(QString)), SLOT(textEdited(QString)) );
}

TextPropertyWidgetItem::~TextPropertyWidgetItem()
{

}

QStringList
TextPropertyWidgetItem::supportedDataTypes() const
{
    QStringList supportedTypes;
    supportedTypes.append( "QString" );
    return supportedTypes;
}
void TextPropertyWidgetItem::update(QVariant value)
{
  setEditValue(value); 
}

PropertyWidgetItem*
TextPropertyWidgetItem::instantiate()
{
    return new TextPropertyWidgetItem();
}

void
TextPropertyWidgetItem::setEditValue( const QVariant& value )
{
    lineEdit->setText(value.toString());
    editWidget()->setProperty( "text", value );
}

void
TextPropertyWidgetItem::textEdited( QString value )
{
    PropertyWidgetItem::valueChanged( QVariant( value ) );
}
