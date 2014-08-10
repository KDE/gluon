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

#include "nullpropertywidgetitem.h"

#include <KI18n/KLocalizedString>

#include <QtWidgets/QLabel>

// This is commented out specifically to inform you that this should not be done.
// As this class is not supposed to be used normally, it is a special case
// and as such does not register in the normal way (the registration would be a NOOP
// at any rate, as this does not support any data types. See the
// ::supportedDataTypes() function below)
// REGISTER_PROPERTYWIDGETITEM(GluonCreator,NullPropertyWidgetItem)

using namespace GluonCreator;

NullPropertyWidgetItem::NullPropertyWidgetItem( QWidget* parent, Qt::WindowFlags f ): PropertyWidgetItem( parent, f )
{
    setEditWidget( new QLabel( i18n( "Unknown Type" ) ) );
}

NullPropertyWidgetItem::~NullPropertyWidgetItem()
{

}

QStringList
NullPropertyWidgetItem::supportedDataTypes() const
{
    QStringList supportedTypes;
    return supportedTypes;
}

PropertyWidgetItem*
NullPropertyWidgetItem::instantiate()
{
    return new NullPropertyWidgetItem();
}

void
NullPropertyWidgetItem::setEditValue( const QVariant& value )
{
    editWidget()->setProperty( "text", QString( "Unknown: %1(%2)" ).arg( value.typeName() ).arg( value.toString() ) );
}
