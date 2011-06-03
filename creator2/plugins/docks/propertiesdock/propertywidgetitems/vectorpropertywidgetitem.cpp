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


#include "vectorpropertywidgetitem.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QDoubleSpinBox>
#include <cfloat>
#include <QVector3D>
#include <core/gluonvarianttypes.h>
#include <QVector2D>

REGISTER_PROPERTYWIDGETITEM( GluonCreator, VectorPropertyWidgetItem )

using namespace GluonCreator;

class VectorPropertyWidgetItem::VectorPropertyWidgetItemPrivate
{
    public:
        VectorPropertyWidgetItemPrivate() { }

        QDoubleSpinBox* x;
        QDoubleSpinBox* y;
        QDoubleSpinBox* z;
        QDoubleSpinBox* w;

        QVariant::Type type;
};

VectorPropertyWidgetItem::VectorPropertyWidgetItem( QWidget* parent, Qt::WindowFlags f ): PropertyWidgetItem( parent, f )
{
    d = new VectorPropertyWidgetItemPrivate;

    QWidget* base = new QWidget( this );
    QHBoxLayout* layout = new QHBoxLayout();
    layout->setSpacing( 0 );
    base->setLayout( layout );

    d->x = new QDoubleSpinBox( this );
    d->x->setPrefix( "X: " );
    d->x->setRange( -FLT_MAX, FLT_MAX );
    layout->addWidget( d->x );
    connect( d->x, SIGNAL( valueChanged( double ) ), SLOT( editValueChanged() ) );

    d->y = new QDoubleSpinBox( this );
    d->y->setPrefix( "Y: " );
    d->y->setRange( -FLT_MAX, FLT_MAX );
    layout->addWidget( d->y );
    connect( d->y, SIGNAL( valueChanged( double ) ), SLOT( editValueChanged() ) );

    d->z = new QDoubleSpinBox( this );
    d->z->setPrefix( "Z: " );
    d->z->setRange( -FLT_MAX, FLT_MAX );
    layout->addWidget( d->z );
    connect( d->z, SIGNAL( valueChanged( double ) ), SLOT( editValueChanged() ) );

    d->w = new QDoubleSpinBox( this );
    d->w->setPrefix( "W: " );
    d->w->setRange( -FLT_MAX, FLT_MAX );
    layout->addWidget( d->w );
    connect( d->w, SIGNAL( valueChanged( double ) ), SLOT( editValueChanged() ) );

    setEditWidget( base );
}

VectorPropertyWidgetItem::~VectorPropertyWidgetItem()
{
    delete d;
}

QStringList
VectorPropertyWidgetItem::supportedDataTypes() const
{
    QStringList supportedTypes;
    supportedTypes.append( "QVector2D" );
    supportedTypes.append( "QVector3D" );
    supportedTypes.append( "QVector4D" );
    return supportedTypes;
}

PropertyWidgetItem*
VectorPropertyWidgetItem::instantiate()
{
    return new VectorPropertyWidgetItem();
}

void VectorPropertyWidgetItem::setEditValue( const QVariant& value )
{

    switch( value.type() )
    {
        case QVariant::Vector2D:
        {
            const QVector2D* vector = static_cast<const QVector2D*>( value.data() );
            d->x->setValue( vector->x() );
            d->y->setValue( vector->y() );
            d->z->setVisible( false );
            d->w->setVisible( false );
            d->type = QVariant::Vector2D;
            break;
        }
        case QVariant::Vector3D:
        {
            const QVector3D* vector = static_cast<const QVector3D*>( value.data() );
            d->x->setValue( vector->x() );
            d->y->setValue( vector->y() );
            d->z->setValue( vector->z() );
            d->w->setVisible( false );
            d->type = QVariant::Vector3D;
            break;
        }
        case QVariant::Vector4D:
        {
            const QVector4D* vector = static_cast<const QVector4D*>( value.data() );
            d->x->setValue( vector->x() );
            d->y->setValue( vector->y() );
            d->z->setValue( vector->z() );
            d->w->setValue( vector->w() );
            d->type = QVariant::Vector4D;
            break;
        }
        default:
            break;
    }
}

void VectorPropertyWidgetItem::editValueChanged()
{
    switch( d->type )
    {
        case QVariant::Vector2D:
            PropertyWidgetItem::valueChanged( QVariant::fromValue<QVector2D>( QVector2D( d->x->value(), d->y->value() ) ) );
            break;
        case QVariant::Vector3D:
            PropertyWidgetItem::valueChanged( QVariant::fromValue<QVector3D>( QVector3D( d->x->value(), d->y->value(), d->z->value() ) ) );
            break;
        case QVariant::Vector4D:
            PropertyWidgetItem::valueChanged( QVariant::fromValue<QVector4D>( QVector4D( d->x->value(), d->y->value(), d->z->value(), d->w->value() ) ) );
            break;
        default:
            break;
    }
}
