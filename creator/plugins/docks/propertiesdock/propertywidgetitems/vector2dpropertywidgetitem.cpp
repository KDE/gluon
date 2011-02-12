/******************************************************************************
 * This file is part of the Gluon Development Platform
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


#include "vector2dpropertywidgetitem.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QDoubleSpinBox>
#include <cfloat>
#include <QVector2D>
#include <core/gluonvarianttypes.h>

REGISTER_PROPERTYWIDGETITEM( GluonCreator, Vector2DPropertyWidgetItem )

using namespace GluonCreator;

class Vector2DPropertyWidgetItem::Private
{
    public:
        Private() { }

        QDoubleSpinBox* x;
        QDoubleSpinBox* y;

        QVector2D value;
};

Vector2DPropertyWidgetItem::Vector2DPropertyWidgetItem( QWidget* parent, Qt::WindowFlags f )
    : PropertyWidgetItem( parent, f ), d(new Private)
{
    QWidget* base = new QWidget( this );
    QHBoxLayout* layout = new QHBoxLayout();
    layout->setSpacing( 0 );
    base->setLayout( layout );

    d->x = new QDoubleSpinBox( this );
    d->x->setPrefix( "X: " );
    d->x->setRange( -FLT_MAX, FLT_MAX );
    layout->addWidget( d->x );
    connect( d->x, SIGNAL( valueChanged( double ) ), SLOT( xValueChanged( double ) ) );

    d->y = new QDoubleSpinBox( this );
    d->y->setPrefix( "Y: " );
    d->y->setRange( -FLT_MAX, FLT_MAX );
    layout->addWidget( d->y );
    connect( d->y, SIGNAL( valueChanged( double ) ), SLOT( yValueChanged( double ) ) );

    setEditWidget( base );
}

Vector2DPropertyWidgetItem::~Vector2DPropertyWidgetItem()
{
    delete d;
}

QStringList
Vector2DPropertyWidgetItem::supportedDataTypes() const
{
    QStringList supportedTypes;
    supportedTypes.append( "QVector2D" );
    return supportedTypes;
}

PropertyWidgetItem*
Vector2DPropertyWidgetItem::instantiate()
{
    return new Vector2DPropertyWidgetItem();
}

void Vector2DPropertyWidgetItem::setEditValue( const QVariant& value )
{
    const QVector2D* vector = static_cast<const QVector2D*>( value.data() );

    d->x->setValue( vector->x() );
    d->y->setValue( vector->y() );
}

void Vector2DPropertyWidgetItem::xValueChanged( double value )
{
    d->value = QVector2D( value, d->y->value() );
    PropertyWidgetItem::valueChanged( QVariant::fromValue<QVector2D>( d->value ) );
}

void Vector2DPropertyWidgetItem::yValueChanged( double value )
{
    d->value = QVector2D( d->x->value(), value );
    PropertyWidgetItem::valueChanged( QVariant::fromValue<QVector2D>( d->value ) );
}
