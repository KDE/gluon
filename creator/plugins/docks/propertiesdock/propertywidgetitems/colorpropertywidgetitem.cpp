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


#include "colorpropertywidgetitem.h"

#include <QtGui/QColor>
#include <KColorButton>

#include <core/gluonvarianttypes.h>

REGISTER_PROPERTYWIDGETITEM( GluonCreator, ColorPropertyWidgetItem )

using namespace GluonCreator;

class ColorPropertyWidgetItem::ColorPropertyWidgetItemPrivate
{
    public:
        ColorPropertyWidgetItemPrivate() { }

        KColorButton* button;
};

ColorPropertyWidgetItem::ColorPropertyWidgetItem( QWidget* parent, Qt::WindowFlags f ): PropertyWidgetItem( parent, f )
{
    d = new ColorPropertyWidgetItemPrivate;

    d->button = new KColorButton( this );
    connect( d->button, SIGNAL( changed( const QColor& ) ), this, SLOT( colorValuechanged( const QColor& ) ) );
    setEditWidget( d->button );
}

ColorPropertyWidgetItem::~ColorPropertyWidgetItem()
{
    delete d;
}

QStringList
ColorPropertyWidgetItem::supportedDataTypes() const
{
    QStringList supportedTypes;
    supportedTypes.append( "QColor" );
    return supportedTypes;
}

PropertyWidgetItem*
ColorPropertyWidgetItem::instantiate()
{
    return new ColorPropertyWidgetItem();
}

void
ColorPropertyWidgetItem::setEditValue( const QVariant& value )
{
    QColor color = value.value<QColor>();
    d->button->setColor( color );
}

void
ColorPropertyWidgetItem::colorValuechanged( const QColor& value )
{
    PropertyWidgetItem::valueChanged( qVariantFromValue<QColor>( value ) );
}
