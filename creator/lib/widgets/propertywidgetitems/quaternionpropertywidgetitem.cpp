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

#include "quaternionpropertywidgetitem.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QDoubleSpinBox>
#include <cfloat>

#include <core/gluonvarianttypes.h>

using namespace GluonCreator;

class QuaternionPropertyWidgetItem::QuaternionPropertyWidgetItemPrivate
{
    public:
        QuaternionPropertyWidgetItemPrivate() { }

        QDoubleSpinBox* x;
        QDoubleSpinBox* y;
        QDoubleSpinBox* z;
        QDoubleSpinBox* angle;

        Eigen::AngleAxisf value;
};

QuaternionPropertyWidgetItem::QuaternionPropertyWidgetItem(QWidget* parent, Qt::WindowFlags f): PropertyWidgetItem(parent, f)
{
    d = new QuaternionPropertyWidgetItemPrivate;

    QWidget* base = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout();
    base->setLayout(layout);

    QHBoxLayout* vectorLayout = new QHBoxLayout();
    layout->addLayout(vectorLayout);

    d->x = new QDoubleSpinBox(this);
    d->x->setPrefix("X: ");
    d->x->setRange(-FLT_MAX, FLT_MAX);
    vectorLayout->addWidget(d->x);
    connect(d->x, SIGNAL(valueChanged(double)), SLOT(xValueChanged(double)));

    d->y = new QDoubleSpinBox(this);
    d->y->setPrefix("Y: ");
    d->y->setRange(-FLT_MAX, FLT_MAX);
    vectorLayout->addWidget(d->y);
    connect(d->y, SIGNAL(valueChanged(double)), SLOT(yValueChanged(double)));

    d->z = new QDoubleSpinBox(this);
    d->z->setPrefix("Z: ");
    d->z->setRange(-FLT_MAX, FLT_MAX);
    vectorLayout->addWidget(d->z);
    connect(d->z, SIGNAL(valueChanged(double)), SLOT(zValueChanged(double)));

    d->angle = new QDoubleSpinBox(this);
    d->angle->setPrefix("Angle: ");
    d->angle->setRange(-FLT_MAX, FLT_MAX);
    layout->addWidget(d->angle);
    connect(d->angle, SIGNAL(valueChanged(double)), SLOT(angleValueChanged(double)));

    setEditWidget(base);
}

QuaternionPropertyWidgetItem::~QuaternionPropertyWidgetItem()
{
    delete d;
}


void QuaternionPropertyWidgetItem::setEditValue(const QVariant& value)
{
    Eigen::Quaternionf quat = value.value<Eigen::Quaternionf>();

    Eigen::AngleAxisf angleAxis(quat);
    d->value = angleAxis;

    d->x->setValue(angleAxis.axis().x());
    d->y->setValue(angleAxis.axis().y());
    d->z->setValue(angleAxis.axis().z());
    d->angle->setValue(angleAxis.angle() * (180/M_PI));
}

void QuaternionPropertyWidgetItem::xValueChanged(double value)
{
    d->value.axis().x() = value;

    Eigen::Quaternionf tempValue(d->value);
    PropertyWidgetItem::valueChanged(QVariant::fromValue<Eigen::Quaternionf>(tempValue));
}

void QuaternionPropertyWidgetItem::yValueChanged(double value)
{
    d->value.axis().y() = value;

    Eigen::Quaternionf tempValue(d->value);
    PropertyWidgetItem::valueChanged(QVariant::fromValue<Eigen::Quaternionf>(tempValue));
}

void QuaternionPropertyWidgetItem::zValueChanged(double value)
{
    d->value.axis().z() = value;

    Eigen::Quaternionf tempValue(d->value);
    PropertyWidgetItem::valueChanged(QVariant::fromValue<Eigen::Quaternionf>(tempValue));
}

void QuaternionPropertyWidgetItem::angleValueChanged(double value)
{
    d->value.angle() = value * (M_PI/180);

    Eigen::Quaternionf tempValue(d->value);
    PropertyWidgetItem::valueChanged(QVariant::fromValue<Eigen::Quaternionf>(tempValue));
}

#include "quaternionpropertywidgetitem.moc"
