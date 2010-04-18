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

#include <QtGui/QDoubleSpinBox>

#include <cfloat>

REGISTER_PROPERTYWIDGETITEM(GluonCreator, QRealPropertyWidgetItem)

using namespace GluonCreator;

QRealPropertyWidgetItem::QRealPropertyWidgetItem(QWidget* parent, Qt::WindowFlags f)
        : PropertyWidgetItem(parent, f)
{
	QDoubleSpinBox *spinBox = new QDoubleSpinBox(this);
    setEditWidget(spinBox);
    connect(editWidget(), SIGNAL(valueChanged(double)), SLOT(qrealValueChanged(double)));
}

QRealPropertyWidgetItem::~QRealPropertyWidgetItem()
{
}

QList< QString >
QRealPropertyWidgetItem::supportedDataTypes() const
{
    QList<QString> supportedTypes;
    supportedTypes.append("qreal");
    return supportedTypes;
}

PropertyWidgetItem*
QRealPropertyWidgetItem::instantiate()
{
    return new QRealPropertyWidgetItem();
}

void
QRealPropertyWidgetItem::setEditValue(const QVariant& value)
{
    editWidget()->setProperty("value", value);
}

void
QRealPropertyWidgetItem::qrealValueChanged(double value)
{
    PropertyWidgetItem::valueChanged(QVariant(value));
}

#include "qrealpropertywidgetitem.moc"
