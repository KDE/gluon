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
#include <QtGui/QQuaternion>
#include <cfloat>
#include <cmath>
#include <core/gluonvarianttypes.h>

REGISTER_PROPERTYWIDGETITEM(GluonCreator, QuaternionPropertyWidgetItem)

using namespace GluonCreator;

class QuaternionPropertyWidgetItem::QuaternionPropertyWidgetItemPrivate
{
    public:
        QuaternionPropertyWidgetItemPrivate() { }

        QDoubleSpinBox* x;
        QDoubleSpinBox* y;
        QDoubleSpinBox* z;
        QDoubleSpinBox* angle;

        QQuaternion value;

//        Eigen::AngleAxisf value;
};

QuaternionPropertyWidgetItem::QuaternionPropertyWidgetItem(QWidget* parent, Qt::WindowFlags f): PropertyWidgetItem(parent, f)
{
    d = new QuaternionPropertyWidgetItemPrivate;

    QWidget* base = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setSpacing(0);
    base->setLayout(layout);

    QHBoxLayout* vectorLayout = new QHBoxLayout();
    layout->addLayout(vectorLayout);

    d->x = new QDoubleSpinBox(this);
    d->x->setPrefix("X: ");
    d->x->setRange(0, 1);
    vectorLayout->addWidget(d->x);
    connect(d->x, SIGNAL(valueChanged(double)), this,  SLOT(valueChanged(double)));

    d->y = new QDoubleSpinBox(this);
    d->y->setPrefix("Y: ");
    d->y->setRange(0, 1);
    vectorLayout->addWidget(d->y);
    connect(d->y, SIGNAL(valueChanged(double)), this,  SLOT(valueChanged(double)));

    d->z = new QDoubleSpinBox(this);
    d->z->setPrefix("Z: ");
    d->z->setRange(0, 1);
    vectorLayout->addWidget(d->z);
    connect(d->z, SIGNAL(valueChanged(double)), this, SLOT(valueChanged(double)));

    d->angle = new QDoubleSpinBox(this);
    d->angle->setPrefix("Angle: ");
    d->angle->setRange(-FLT_MAX, FLT_MAX);
    layout->addWidget(d->angle);
    connect(d->angle, SIGNAL(valueChanged(double)), this, SLOT(valueChanged(double)));

    setEditWidget(base);
}

QuaternionPropertyWidgetItem::~QuaternionPropertyWidgetItem()
{
    delete d;
}

QList< QString >
QuaternionPropertyWidgetItem::supportedDataTypes() const
{
    QList<QString> supportedTypes;
    supportedTypes.append("QQuaternion");
    return supportedTypes;
}

PropertyWidgetItem*
QuaternionPropertyWidgetItem::instantiate()
{
    return new QuaternionPropertyWidgetItem();
}

void QuaternionPropertyWidgetItem::setEditValue(const QVariant& value)
{
    d->value = value.value<QQuaternion>();

    d->x->setValue(d->value.x() * sqrt(1 - d->value.scalar() * d->value.scalar()));
    d->y->setValue(d->value.y() * sqrt(1 - d->value.scalar() * d->value.scalar()));
    d->z->setValue(d->value.z() * sqrt(1 - d->value.scalar() * d->value.scalar()));

    d->angle->setValue((2 * acos(d->value.scalar())) * (180 / M_PI));

    /*angle = 2 * acos(qw)
    x = qx / sqrt(1-qw*qw)
    y = qy / sqrt(1-qw*qw)
    z = qz / sqrt(1-qw*qw)
    d->proxi->setX(quat.x());
    d->proxi->setY(quat.y());
    d->proxi->setZ(quat.z());
    d->proxi->setScalar(quat.scalar() * (180/M_PI) );*/

}

void QuaternionPropertyWidgetItem::valueChanged(QVariant value)
{
    valueChanged(value.toDouble());
}

void QuaternionPropertyWidgetItem::valueChanged(double value)
{
    Q_UNUSED(value)
    d->value = QQuaternion::fromAxisAndAngle(d->x->value(), d->y->value(), d->z->value(), d->angle->value());
    PropertyWidgetItem::valueChanged(d->value);
}

#include "quaternionpropertywidgetitem.moc"
