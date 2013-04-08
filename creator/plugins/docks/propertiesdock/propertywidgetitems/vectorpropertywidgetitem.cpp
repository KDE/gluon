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
#include <core/gluonvarianttypes.h>
#include <Eigen/Core>

REGISTER_PROPERTYWIDGETITEM( GluonCreator, VectorPropertyWidgetItem )

using namespace GluonCreator;
using namespace Eigen;

class VectorPropertyWidgetItem::VectorPropertyWidgetItemPrivate
{
    public:
        VectorPropertyWidgetItemPrivate() 
            : vector2d( qMetaTypeId<Eigen::Vector2f>() )
            , vector3d( qMetaTypeId<Eigen::Vector3f>() )
            , vector4d( qMetaTypeId<Eigen::Vector4f>() )
        { }

        QDoubleSpinBox* x;
        QDoubleSpinBox* y;
        QDoubleSpinBox* z;
        QDoubleSpinBox* w;

        int vectorDim;

        const int vector2d;
        const int vector3d;
        const int vector4d;
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
    connect( d->x, SIGNAL(valueChanged(double)), SLOT(editValueChanged()) );

    d->y = new QDoubleSpinBox( this );
    d->y->setPrefix( "Y: " );
    d->y->setRange( -FLT_MAX, FLT_MAX );
    layout->addWidget( d->y );
    connect( d->y, SIGNAL(valueChanged(double)), SLOT(editValueChanged()) );

    d->z = new QDoubleSpinBox( this );
    d->z->setPrefix( "Z: " );
    d->z->setRange( -FLT_MAX, FLT_MAX );
    layout->addWidget( d->z );
    connect( d->z, SIGNAL(valueChanged(double)), SLOT(editValueChanged()) );

    d->w = new QDoubleSpinBox( this );
    d->w->setPrefix( "W: " );
    d->w->setRange( -FLT_MAX, FLT_MAX );
    layout->addWidget( d->w );
    connect( d->w, SIGNAL(valueChanged(double)), SLOT(editValueChanged()) );

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
    supportedTypes.append( "Vector2f" );
    supportedTypes.append( "Vector3f" );
    supportedTypes.append( "Vector4f" );
    return supportedTypes;
}

PropertyWidgetItem*
VectorPropertyWidgetItem::instantiate()
{
    return new VectorPropertyWidgetItem();
}

void VectorPropertyWidgetItem::setEditValue( const QVariant& value )
{
    int userType = value.userType();
    if( userType == d->vector2d )
    {
        const Vector2f* vector = static_cast<const Vector2f*>( value.data() );
        d->x->setValue( vector->x() );
        d->y->setValue( vector->y() );
        d->z->setVisible( false );
        d->w->setVisible( false );
        d->vectorDim = 2;
    }
    else if( userType == d->vector3d )
    {
        const Vector3f* vector = static_cast<const Vector3f*>( value.data() );
        d->x->setValue( vector->x() );
        d->y->setValue( vector->y() );
        d->z->setValue( vector->z() );
        d->w->setVisible( false );
        d->vectorDim = 3;
    }
    else if( userType == d->vector4d )
    {
        const Vector4f* vector = static_cast<const Vector4f*>( value.data() );
        d->x->setValue( vector->x() );
        d->y->setValue( vector->y() );
        d->z->setValue( vector->z() );
        d->w->setValue( vector->w() );
        d->vectorDim = 4;
    }
}

void VectorPropertyWidgetItem::editValueChanged()
{
    switch( d->vectorDim )
    {
        case 2:
            PropertyWidgetItem::valueChanged( qVariantFromValue<Vector2f>( Vector2f( d->x->value(), d->y->value() ) ) );
            break;
        case 3:
            PropertyWidgetItem::valueChanged( qVariantFromValue<Vector3f>( Vector3f( d->x->value(), d->y->value(), d->z->value() ) ) );
            break;
        case 4:
            PropertyWidgetItem::valueChanged( qVariantFromValue<Vector4f>( Vector4f( d->x->value(), d->y->value(), d->z->value(), d->w->value() ) ) );
            break;
        default:
            break;
    }
}
