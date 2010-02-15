/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "colorpropertywidgetitem.h"

#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QColor>

#include <cfloat>

#include <core/gluonvarianttypes.h>

REGISTER_PROPERTYWIDGETITEM(GluonCreator,ColorPropertyWidgetItem)

using namespace GluonCreator;

class ColorPropertyWidgetItem::ColorPropertyWidgetItemPrivate
{
    public:
        ColorPropertyWidgetItemPrivate() { }

        QDoubleSpinBox* r;
        QDoubleSpinBox* g;
        QDoubleSpinBox* b;

        QColor value;
};

ColorPropertyWidgetItem::ColorPropertyWidgetItem(QWidget* parent, Qt::WindowFlags f): PropertyWidgetItem(parent, f)
{
    d = new ColorPropertyWidgetItemPrivate;

    QWidget* base = new QWidget(this);
    QHBoxLayout* layout = new QHBoxLayout();
    base->setLayout(layout);

    d->r = new QDoubleSpinBox(this);
    d->r->setPrefix("R: ");
    d->r->setRange(0.0f, 1.0f);
    d->r->setSingleStep(0.01f);
    layout->addWidget(d->r);
    connect(d->r, SIGNAL(valueChanged(double)), SLOT(rValueChanged(double)));

    d->g = new QDoubleSpinBox(this);
    d->g->setPrefix("G: ");
    d->g->setRange(0.0f, 1.0f);
    d->g->setSingleStep(0.01f);
    layout->addWidget(d->g);
    connect(d->g, SIGNAL(valueChanged(double)), SLOT(gValueChanged(double)));

    d->b = new QDoubleSpinBox(this);
    d->b->setPrefix("B: ");
    d->b->setRange(0.0f, 1.0f);
    d->b->setSingleStep(0.01f);
    layout->addWidget(d->b);
    connect(d->b, SIGNAL(valueChanged(double)), SLOT(bValueChanged(double)));

    setEditWidget(base);
}

ColorPropertyWidgetItem::~ColorPropertyWidgetItem()
{
    delete d;
}

QList< QString >
ColorPropertyWidgetItem::supportedDataTypes() const
{
    QList<QString> supportedTypes;
    supportedTypes.append("QColor");
    return supportedTypes;
}

PropertyWidgetItem*
ColorPropertyWidgetItem::instantiate()
{
    return new ColorPropertyWidgetItem();
}

void
ColorPropertyWidgetItem::setEditValue(const QVariant& value)
{
    QColor color = value.value<QColor>();
    d->value = color;

    d->r->setValue(color.redF());
    d->g->setValue(color.greenF());
    d->b->setValue(color.blueF());
}

void
ColorPropertyWidgetItem::rValueChanged(double value)
{
    d->value.setRedF(value);
    PropertyWidgetItem::valueChanged(QVariant::fromValue<QColor>(d->value));
}

void
ColorPropertyWidgetItem::gValueChanged(double value)
{
    d->value.setGreenF(value);
    PropertyWidgetItem::valueChanged(QVariant::fromValue<QColor>(d->value));
}

void
ColorPropertyWidgetItem::bValueChanged(double value)
{
    d->value.setBlueF(value);
    PropertyWidgetItem::valueChanged(QVariant::fromValue<QColor>(d->value));
}

#include "colorpropertywidgetitem.moc"
