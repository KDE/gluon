/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#include "qsizefpropertywidgetitem.h"

#include <QtGui/QDoubleSpinBox>
#include <QtGui/QHBoxLayout>

#include <cfloat>

REGISTER_PROPERTYWIDGETITEM(GluonCreator,QSizeFPropertyWidgetItem)

using namespace GluonCreator;

class QSizeFPropertyWidgetItem::QSizeFPropertyWidgetItemPrivate
{
    public:
        QSizeFPropertyWidgetItemPrivate() {};

        QDoubleSpinBox *height;
        QDoubleSpinBox *width;

        QSizeF value;
};

QSizeFPropertyWidgetItem::QSizeFPropertyWidgetItem(QWidget* parent, Qt::WindowFlags f)
    : PropertyWidgetItem(parent, f)
{
    d = new QSizeFPropertyWidgetItemPrivate;

    QWidget *widget = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setSpacing(0);
    widget->setLayout(layout);

    d->height = new QDoubleSpinBox(this);
    d->height->setPrefix(tr("Height: "));
    d->height->setRange(-FLT_MAX, FLT_MAX);
    layout->addWidget(d->height);
    connect(d->height, SIGNAL(valueChanged(double)), SLOT(heightValueChanged(double)));

    d->width = new QDoubleSpinBox(this);
    d->width->setPrefix(tr("Width: "));
    d->width->setRange(-FLT_MAX, FLT_MAX);
    layout->addWidget(d->width);
    connect(d->width, SIGNAL(valueChanged(double)), SLOT(widthValueChanged(double)));

    setEditWidget(widget);
}

QSizeFPropertyWidgetItem::~QSizeFPropertyWidgetItem()
{
    delete d;
}

QList< QString >
QSizeFPropertyWidgetItem::supportedDataTypes() const
{
    QList<QString> supportedTypes;
    supportedTypes.append("QSizeF");
    return supportedTypes;
}

PropertyWidgetItem*
QSizeFPropertyWidgetItem::instantiate()
{
    return new QSizeFPropertyWidgetItem();
}

void
QSizeFPropertyWidgetItem::setEditValue(const QVariant& value)
{
    d->value = value.toSizeF();

    d->height->setValue(d->value.height());
    d->width->setValue(d->value.width());
}

void
QSizeFPropertyWidgetItem::heightValueChanged(double value)
{
    d->value.setHeight(value);
    PropertyWidgetItem::valueChanged(QVariant(d->value));
}

void
QSizeFPropertyWidgetItem::widthValueChanged(double value)
{
    d->value.setWidth(value);
    PropertyWidgetItem::valueChanged(QVariant(d->value));
}

#include "qsizefpropertywidgetitem.moc"
