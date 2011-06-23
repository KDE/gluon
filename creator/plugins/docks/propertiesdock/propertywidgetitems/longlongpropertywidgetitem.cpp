/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Felix Rohrbach <fxrh@gmx.de>
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

#include "longlongpropertywidgetitem.h"

#include <QtGui/QLineEdit>
#include <QtGui/QRegExpValidator>

REGISTER_PROPERTYWIDGETITEM( GluonCreator, LongLongPropertyWidgetItem )

using namespace GluonCreator;

LongLongPropertyWidgetItem::LongLongPropertyWidgetItem( QWidget* parent, Qt::WindowFlags f )
    : PropertyWidgetItem(parent, f)
{
}

LongLongPropertyWidgetItem::~LongLongPropertyWidgetItem()
{
}

QStringList LongLongPropertyWidgetItem::supportedDataTypes() const
{
    QStringList types;
    types.append( "qlonglong" );
    return types;
}

PropertyWidgetItem* LongLongPropertyWidgetItem::instantiate()
{
    return new LongLongPropertyWidgetItem();
}

void LongLongPropertyWidgetItem::setEditValue( const QVariant& value )
{
    editWidget()->setProperty( "text", value );
}

void LongLongPropertyWidgetItem::setEditProperty( const QString& propertyName )
{
    QLineEdit* lineEdit = new QLineEdit( this );
    QRegExp rx( "-?\\d+" );
    QRegExpValidator* validator = new QRegExpValidator( rx, this );
    lineEdit->setValidator(validator);
    setEditWidget( lineEdit );

    connect( lineEdit, SIGNAL(textChanged(QString)), this, SLOT(stringValueChanged(QString)) );

    PropertyWidgetItem::setEditProperty( propertyName );
}

void LongLongPropertyWidgetItem::stringValueChanged( QString value )
{
    bool ok;
    qlonglong number = value.toLongLong(&ok);
    if( !ok )
        number = 0;
    PropertyWidgetItem::valueChanged( QVariant::fromValue<qlonglong>( number ) );
}
