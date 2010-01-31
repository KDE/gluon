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

    QHBoxLayout *layout = new QHBoxLayout(this);

    d->height = new QDoubleSpinBox(this);
    d->height->setPrefix(tr("Height: "));
    layout->addWidget(d->height);
    connect(d->height, SIGNAL(valueChanged(double)), SLOT(heightValueChanged(double)));

    d->width = new QDoubleSpinBox(this);
    d->width->setPrefix(tr("Width: "));
    layout->addWidget(d->width);
    connect(d->width, SIGNAL(valueChanged(double)), SLOT(widthValueChanged(double)));

    QWidget *widget = new QWidget(this);
    widget->setLayout(layout);
    setEditWidget(widget);
}

QSizeFPropertyWidgetItem::~QSizeFPropertyWidgetItem()
{
    delete d;
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
    d->value = QSizeF(value, d->value.width());
    PropertyWidgetItem::valueChanged(QVariant(d->value));
}

void
QSizeFPropertyWidgetItem::widthValueChanged(double value)
{
    d->value = QSizeF(d->value.height(), value);
    PropertyWidgetItem::valueChanged(QVariant(d->value));
}

#include "qsizefpropertywidgetitem.moc"
