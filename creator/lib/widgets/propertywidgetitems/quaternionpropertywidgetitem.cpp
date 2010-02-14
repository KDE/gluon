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

using namespace GluonCreator;

class QuaternionPropertyWidgetItem::QuaternionPropertyWidgetItemPrivate
{
    public:
        QuaternionPropertyWidgetItemPrivate() { }

        QDoubleSpinBox* x;
        QDoubleSpinBox* y;
        QDoubleSpinBox* z;
        QDoubleSpinBox* angle;
        
        QQuaternion* proxi;

//        Eigen::AngleAxisf value;
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
    connect(d->x, SIGNAL(valueChanged(double)),this,  SLOT(xValueChanged(double)));

    d->y = new QDoubleSpinBox(this);
    d->y->setPrefix("Y: ");
    d->y->setRange(-FLT_MAX, FLT_MAX);
    vectorLayout->addWidget(d->y);
    connect(d->y, SIGNAL(valueChanged(double)),this,  SLOT(yValueChanged(double)));

    d->z = new QDoubleSpinBox(this);
    d->z->setPrefix("Z: ");
    d->z->setRange(-FLT_MAX, FLT_MAX);
    vectorLayout->addWidget(d->z);
    connect(d->z, SIGNAL(valueChanged(double)),this, SLOT(zValueChanged(double)));

    d->angle = new QDoubleSpinBox(this);
    d->angle->setPrefix("Angle: ");
    d->angle->setRange(-FLT_MAX, FLT_MAX);
    layout->addWidget(d->angle);
    connect(d->angle, SIGNAL(valueChanged(double)),this, SLOT(angleValueChanged(double)));
    
    d->proxi = new QQuaternion();

    setEditWidget(base);
}

QuaternionPropertyWidgetItem::~QuaternionPropertyWidgetItem()
{
    delete d;
}


void QuaternionPropertyWidgetItem::setEditValue(const QVariant& value)
{
   QQuaternion quat = value.value<QQuaternion>();
   
   d->proxi->setX(quat.x());
   d->proxi->setY(quat.y());
   d->proxi->setZ(quat.z());
   d->proxi->setScalar(quat.scalar() * (180/M_PI) );
}

void QuaternionPropertyWidgetItem::xValueChanged(double value)
{
  d->proxi->setX(value);
  PropertyWidgetItem::valueChanged(d->proxi->operator QVariant());
}

void QuaternionPropertyWidgetItem::yValueChanged(double value)
{
  d->proxi->setY(value);
  PropertyWidgetItem::valueChanged(d->proxi->operator QVariant());
}

void QuaternionPropertyWidgetItem::zValueChanged(double value)
{
  d->proxi->setZ(value);
  PropertyWidgetItem::valueChanged(d->proxi->operator QVariant());
}

void QuaternionPropertyWidgetItem::angleValueChanged(double value)
{
  d->proxi->setScalar(value * (180/M_PI) );
  PropertyWidgetItem::valueChanged(d->proxi->operator QVariant());
}

#include "quaternionpropertywidgetitem.moc"
