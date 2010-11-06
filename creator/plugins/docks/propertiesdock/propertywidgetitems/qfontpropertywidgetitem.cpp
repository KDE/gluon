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


#include "qfontpropertywidgetitem.h"

#include <KFontRequester>

REGISTER_PROPERTYWIDGETITEM( GluonCreator, QFontPropertyWidgetItem );

using namespace GluonCreator;

QFontPropertyWidgetItem::QFontPropertyWidgetItem( QWidget* parent, Qt::WindowFlags f )
    : PropertyWidgetItem( parent, f )
{
    KFontRequester* theFontReq = new KFontRequester( this );
    connect( theFontReq, SIGNAL( fontSelected( const QFont& ) ), this, SLOT( fontChanged( const QFont& ) ) );
    setEditWidget( theFontReq );
}

QFontPropertyWidgetItem::~QFontPropertyWidgetItem()
{
}

QStringList
QFontPropertyWidgetItem::supportedDataTypes() const
{
    QStringList supportedTypes;
    supportedTypes.append( "QFont" );
    return supportedTypes;
}

GluonCreator::PropertyWidgetItem*
QFontPropertyWidgetItem::instantiate()
{
    return new QFontPropertyWidgetItem();
}

void
QFontPropertyWidgetItem::setEditValue( const QVariant& value )
{
    editWidget()->setProperty( "font", value );
    GluonCreator::PropertyWidgetItem::setEditValue( value );
}

void QFontPropertyWidgetItem::fontChanged( const QFont& value )
{
    PropertyWidgetItem::valueChanged( QVariant( value ) );
}


// #include "qfontpropertywidgetitem.moc"
