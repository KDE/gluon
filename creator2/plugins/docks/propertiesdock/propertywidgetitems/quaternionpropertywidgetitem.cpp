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


#include "quaternionpropertywidgetitem.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QtGui/QQuaternion>
#include <cfloat>
#include <cmath>
#include <core/gluonvarianttypes.h>

REGISTER_PROPERTYWIDGETITEM( GluonCreator, QuaternionPropertyWidgetItem )

using namespace GluonCreator;

class QuaternionPropertyWidgetItem::QuaternionPropertyWidgetItemPrivate
{
    public:
        QuaternionPropertyWidgetItemPrivate() { }

        QDoubleSpinBox* x;
        QDoubleSpinBox* y;
        QDoubleSpinBox* z;
        QDoubleSpinBox* angle;

        QQuaternion value;
};

QuaternionPropertyWidgetItem::QuaternionPropertyWidgetItem( QWidget* parent, Qt::WindowFlags f ): PropertyWidgetItem( parent, f )
{
    d = new QuaternionPropertyWidgetItemPrivate;

    QWidget* base = new QWidget( this );
    QVBoxLayout* layout = new QVBoxLayout( base );
    layout->setSpacing( 0 );
    base->setLayout( layout );

    QHBoxLayout* vectorLayout = new QHBoxLayout();
    layout->addLayout( vectorLayout );

    d->x = new QDoubleSpinBox( this );
    d->x->setPrefix( "X: " );
    d->x->setRange( -1, 1 );
    d->x->setDecimals( 3 );
    d->x->setSingleStep( 0.01 );
    vectorLayout->addWidget( d->x );
    connect( d->x, SIGNAL( valueChanged( double ) ), this,  SLOT( valueChanged( double ) ) );

    d->y = new QDoubleSpinBox( this );
    d->y->setPrefix( "Y: " );
    d->y->setRange( -1, 1 );
    d->y->setDecimals( 3 );
    d->y->setSingleStep( 0.01 );
    vectorLayout->addWidget( d->y );
    connect( d->y, SIGNAL( valueChanged( double ) ), this,  SLOT( valueChanged( double ) ) );

    d->z = new QDoubleSpinBox( this );
    d->z->setPrefix( "Z: " );
    d->z->setRange( -1, 1 );
    d->z->setDecimals( 3 );
    d->z->setSingleStep( 0.01 );
    vectorLayout->addWidget( d->z );
    connect( d->z, SIGNAL( valueChanged( double ) ), this, SLOT( valueChanged( double ) ) );

    d->angle = new QDoubleSpinBox( this );
    d->angle->setPrefix( "Angle: " );
    d->angle->setRange( -FLT_MAX, FLT_MAX );
    layout->addWidget( d->angle );
    connect( d->angle, SIGNAL( valueChanged( double ) ), this, SLOT( valueChanged( double ) ) );

    setEditWidget( base );
}

QuaternionPropertyWidgetItem::~QuaternionPropertyWidgetItem()
{
    delete d;
}

QStringList
QuaternionPropertyWidgetItem::supportedDataTypes() const
{
    QStringList supportedTypes;
    supportedTypes.append( "QQuaternion" );
    return supportedTypes;
}

PropertyWidgetItem*
QuaternionPropertyWidgetItem::instantiate()
{
    return new QuaternionPropertyWidgetItem();
}

void QuaternionPropertyWidgetItem::setEditValue( const QVariant& value )
{
    d->value = value.value<QQuaternion>();

    d->x->setValue( d->value.x() * sqrt( 1 - d->value.scalar() * d->value.scalar() ) );
    d->y->setValue( d->value.y() * sqrt( 1 - d->value.scalar() * d->value.scalar() ) );
    d->z->setValue( d->value.z() * sqrt( 1 - d->value.scalar() * d->value.scalar() ) );

    d->angle->setValue( ( 2 * acos( d->value.scalar() ) ) * ( 180 / M_PI ) );
}

void QuaternionPropertyWidgetItem::valueChanged( QVariant value )
{
    valueChanged( value.toDouble() );
}

void QuaternionPropertyWidgetItem::valueChanged( double /* value */ )
{
    d->value = QQuaternion::fromAxisAndAngle( d->x->value(), d->y->value(), d->z->value(), d->angle->value() );
    PropertyWidgetItem::valueChanged( d->value );
}
