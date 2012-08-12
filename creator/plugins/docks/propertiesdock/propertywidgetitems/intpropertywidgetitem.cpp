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


#include "intpropertywidgetitem.h"
#include <QtCore/QDebug>
#include <core/gluonobject.h>
#include <core/metainfo.h>

REGISTER_PROPERTYWIDGETITEM( GluonCreator, IntPropertyWidgetItem )

using namespace GluonCreator;

IntPropertyWidgetItem::IntPropertyWidgetItem( QWidget* parent, Qt::WindowFlags f )
    : PropertyWidgetItem( parent, f )
{
}

IntPropertyWidgetItem::~IntPropertyWidgetItem()
{

}

QStringList
IntPropertyWidgetItem::supportedDataTypes() const
{
    QStringList supportedTypes;
    supportedTypes.append( "int" );
    supportedTypes.append( "uint" );
    return supportedTypes;
}

PropertyWidgetItem*
IntPropertyWidgetItem::instantiate()
{
    return new IntPropertyWidgetItem();
}

void
IntPropertyWidgetItem::setEditValue( const QVariant value )
{
  qDebug()<<"In set edit value for int";
  spinBox->setValue(value.toInt());
  editWidget()->setProperty( "value", value );
}

void
IntPropertyWidgetItem::intValueChanged( int value )
{
    PropertyWidgetItem::valueChanged( QVariant( value ) );
}

void
IntPropertyWidgetItem::uintValueChanged( int value )
{
    PropertyWidgetItem::valueChanged( qVariantFromValue<uint>( value ) );
}

void IntPropertyWidgetItem::update(QVariant value)
{
  
}

void IntPropertyWidgetItem::setEditProperty( const QString& propertyName )
{
    spinBox = new QSpinBox( this );
    setEditWidget( spinBox );

    qDebug() << editObject()->property( propertyName.toUtf8() ).typeName();
    if( editObject()->property( propertyName.toUtf8() ).typeName() == QString( "uint" ) )
    {
        spinBox->setMinimum( 3 );
        connect( spinBox, SIGNAL(valueChanged(int)), this, SLOT(uintValueChanged(int)) );
    }
    else
    {
        connect( spinBox, SIGNAL(valueChanged(int)), this, SLOT(intValueChanged(int)) );
    }

    GluonCore::GluonObject* object = qobject_cast<GluonCore::GluonObject*>( editObject() );
    if( object && object->hasMetaInfo() )
    {
        GluonCore::MetaInfo* metaInfo = object->metaInfo();
        if( metaInfo->hasPropertyRange( propertyName ) )
        {
            spinBox->setRange( metaInfo->propertyRangeMin( propertyName ),
                               metaInfo->propertyRangeMax( propertyName ) );
        }
    }

    GluonCreator::PropertyWidgetItem::setEditProperty( propertyName );
}
