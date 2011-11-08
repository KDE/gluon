/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

#include "qurlpropertywidgetitem.h"

#include <QtCore/QUrl>
#include <QtGui/QLayout>
#include <KLineEdit>

REGISTER_PROPERTYWIDGETITEM( GluonCreator, QUrlPropertyWidgetItem )

using namespace GluonCreator;

QUrlPropertyWidgetItem::QUrlPropertyWidgetItem( QWidget* parent, Qt::WindowFlags f )
    : PropertyWidgetItem( parent, f )
{
    KLineEdit* input = new KLineEdit( this );
    //input->setInputMask("");
    connect( input, SIGNAL(editingFinished()), this, SLOT(urlValueChanged()) );
    setEditWidget( input );
}

QUrlPropertyWidgetItem::~QUrlPropertyWidgetItem()
{ }

GluonCreator::PropertyWidgetItem*
QUrlPropertyWidgetItem::instantiate()
{
    return new QUrlPropertyWidgetItem();
}

QStringList
QUrlPropertyWidgetItem::supportedDataTypes() const
{
    QStringList supportedTypes;
    supportedTypes.append( "QUrl" );
    return supportedTypes;
}

void
QUrlPropertyWidgetItem::setEditValue( const QVariant& value )
{
    editWidget()->setProperty( "text", value.value<QUrl>().toString() );
}

void
QUrlPropertyWidgetItem::urlValueChanged()
{
    PropertyWidgetItem::valueChanged( QVariant( QUrl( editWidget()->property( "text" ).toString() ) ) );
}
