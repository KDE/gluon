/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
 * Copyright (c) 2010 Arjen Hiemstra <>
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

#include <QtGui/QSpinBox>

REGISTER_PROPERTYWIDGETITEM(GluonCreator, IntPropertyWidgetItem)

using namespace GluonCreator;

IntPropertyWidgetItem::IntPropertyWidgetItem(QWidget* parent, Qt::WindowFlags f)
        : PropertyWidgetItem(parent, f)
{
    QSpinBox *spinBox = new QSpinBox(this);
    setEditWidget(spinBox);
    connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(intValueChanged(int)));
}

IntPropertyWidgetItem::~IntPropertyWidgetItem()
{

}

QList< QString >
IntPropertyWidgetItem::supportedDataTypes() const
{
    QList<QString> supportedTypes;
    supportedTypes.append("int");
    return supportedTypes;
}

PropertyWidgetItem*
IntPropertyWidgetItem::instantiate()
{
    return new IntPropertyWidgetItem();
}

void
IntPropertyWidgetItem::setEditValue(const QVariant& value)
{
    editWidget()->setProperty("value", value);
}

void
IntPropertyWidgetItem::intValueChanged(int value)
{
    PropertyWidgetItem::valueChanged(QVariant(value));
}

#include "intpropertywidgetitem.moc"
