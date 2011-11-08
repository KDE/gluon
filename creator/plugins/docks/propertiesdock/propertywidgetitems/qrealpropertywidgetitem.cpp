/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Kim Jung Nissen <jungnissen@gmail.com>
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

#include "qrealpropertywidgetitem.h"

#include <cfloat>
#include <core/gluonobject.h>
#include <core/metainfo.h>

#include <knuminput.h>

#include <QtGui/QDoubleSpinBox>
REGISTER_PROPERTYWIDGETITEM( GluonCreator, QRealPropertyWidgetItem )

using namespace GluonCreator;

QRealPropertyWidgetItem::QRealPropertyWidgetItem( QWidget* parent, Qt::WindowFlags f )
    : PropertyWidgetItem( parent, f )
{
}

QRealPropertyWidgetItem::~QRealPropertyWidgetItem()
{
}

QStringList
QRealPropertyWidgetItem::supportedDataTypes() const
{
    QList<QString> supportedTypes;
    supportedTypes.append( "qreal" );
    supportedTypes.append( "float" );
    supportedTypes.append( "double" );
    return supportedTypes;
}

PropertyWidgetItem*
QRealPropertyWidgetItem::instantiate()
{
    return new QRealPropertyWidgetItem();
}

void
QRealPropertyWidgetItem::setEditProperty( const QString& value )
{
    // Clean up any possible leftovers
    delete editWidget();

    GluonCore::GluonObject* theObject = qobject_cast<GluonCore::GluonObject*>( editObject() );
    bool noPropertyRange = true;;
    if( theObject )
    {
        if( theObject->hasMetaInfo() )
        {
            if( theObject->metaInfo()->hasPropertyRange( value ) )
            {
                noPropertyRange = false;
                KDoubleNumInput* editor = new KDoubleNumInput( this );
                editor->setRange( theObject->metaInfo()->propertyRangeMin( value ), theObject->metaInfo()->propertyRangeMax( value ) );
                setEditWidget( editor );
            }
        }
    }

    if( noPropertyRange )
    {
        QDoubleSpinBox* spinBox = new QDoubleSpinBox( this );
        spinBox->setMinimum( -FLT_MAX );
        spinBox->setMaximum( FLT_MAX );
        spinBox->setSingleStep( 0.01f );
        setEditWidget( spinBox );

    }

    connect( editWidget(), SIGNAL(valueChanged(double)), SLOT(qrealValueChanged(double)) );
    GluonCreator::PropertyWidgetItem::setEditProperty( value );
}

void
QRealPropertyWidgetItem::setEditValue( const QVariant& value )
{
    editWidget()->setProperty( "value", value );
}

void
QRealPropertyWidgetItem::qrealValueChanged( double value )
{
    PropertyWidgetItem::valueChanged( QVariant( value ) );
}
