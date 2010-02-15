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

#include "vectorpropertywidgetitem.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QDoubleSpinBox>
#include <cfloat>

#include <core/gluonvarianttypes.h>

REGISTER_PROPERTYWIDGETITEM(GluonCreator,VectorPropertyWidgetItem)

using namespace GluonCreator;

class VectorPropertyWidgetItem::VectorPropertyWidgetItemPrivate
{
    public:
        VectorPropertyWidgetItemPrivate() { }

        QDoubleSpinBox* x;
        QDoubleSpinBox* y;
        QDoubleSpinBox* z;

        Eigen::Vector3f value;
};

VectorPropertyWidgetItem::VectorPropertyWidgetItem(QWidget* parent, Qt::WindowFlags f): PropertyWidgetItem(parent, f)
{
    d = new VectorPropertyWidgetItemPrivate;

    QWidget* base = new QWidget(this);
    QHBoxLayout* layout = new QHBoxLayout();
    base->setLayout(layout);

    d->x = new QDoubleSpinBox(this);
    d->x->setPrefix("X: ");
    d->x->setRange(-FLT_MAX, FLT_MAX);
    layout->addWidget(d->x);
    connect(d->x, SIGNAL(valueChanged(double)), SLOT(xValueChanged(double)));

    d->y = new QDoubleSpinBox(this);
    d->y->setPrefix("Y: ");
    d->y->setRange(-FLT_MAX, FLT_MAX);
    layout->addWidget(d->y);
    connect(d->y, SIGNAL(valueChanged(double)), SLOT(yValueChanged(double)));

    d->z = new QDoubleSpinBox(this);
    d->z->setPrefix("Z: ");
    d->z->setRange(-FLT_MAX, FLT_MAX);
    layout->addWidget(d->z);
    connect(d->z, SIGNAL(valueChanged(double)), SLOT(zValueChanged(double)));

    setEditWidget(base);
}

VectorPropertyWidgetItem::~VectorPropertyWidgetItem()
{
    delete d;
}

QList< QString >
VectorPropertyWidgetItem::supportedDataTypes() const
{
    QList<QString> supportedTypes;
    supportedTypes.append("QVector3D");
    return supportedTypes;
}

PropertyWidgetItem*
VectorPropertyWidgetItem::instantiate()
{
    return new VectorPropertyWidgetItem();
}

void VectorPropertyWidgetItem::setEditValue(const QVariant& value)
{
    const Eigen::Vector3f *vector = static_cast<const Eigen::Vector3f*>(value.data());

    d->x->setValue(vector->x());
    d->y->setValue(vector->y());
    d->z->setValue(vector->z());
}

void VectorPropertyWidgetItem::xValueChanged(double value)
{
    d->value = Eigen::Vector3f(value, d->y->value(), d->z->value());
    PropertyWidgetItem::valueChanged(QVariant::fromValue<Eigen::Vector3f>(d->value));
}

void VectorPropertyWidgetItem::yValueChanged(double value)
{
    d->value = Eigen::Vector3f(d->x->value(), value, d->z->value());
    PropertyWidgetItem::valueChanged(QVariant::fromValue<Eigen::Vector3f>(d->value));
}

void VectorPropertyWidgetItem::zValueChanged(double value)
{
    d->value = Eigen::Vector3f(d->x->value(), d->y->value(), value);
    PropertyWidgetItem::valueChanged(QVariant::fromValue<Eigen::Vector3f>(d->value));
}

#include "vectorpropertywidgetitem.moc"
