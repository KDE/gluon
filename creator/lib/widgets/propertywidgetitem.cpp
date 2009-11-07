/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <QtGui>
#include <QVariant>

#include "propertywidgetitem.h"

using namespace Gluon::Creator;

PropertyWidgetItem::PropertyWidgetItem(QObject * parent, Qt::WindowFlags f)
{
    QGridLayout * layout = new QGridLayout(this);
    layout->setSpacing(0);
    layout->setMargin(0);
    this->setLayout(layout);
}

PropertyWidgetItem::~PropertyWidgetItem()
{
}

void
PropertyWidgetItem::setEditObject(QObject * editThis)
{
    this->editedObject = editThis;
}


void
PropertyWidgetItem::setEditProperty(QString propertyName)
{
    this->propertyName = propertyName;
    setupPropertyWidget();
}

void
PropertyWidgetItem::setupPropertyWidget()
{
    if(!editedObject)
        return;
    
    QVariant value = editedObject->property(propertyName.toUtf8());
    switch(value.type())
    {
        case QVariant::String:
            editWidget = createLineEdit(value);
            break;
        case QVariant::Int:
            editWidget = createSpinBox(value);
            break;
        case QVariant::Double:
            editWidget = createDoubleSpinBox(value);
            break;
        default:
            editWidget = new QLabel(this);
            qobject_cast<QLabel*>(editWidget)->setText(tr("Unknown type (%1)").arg(value.toString()));
            break;
    }
    
    layout()->addWidget(editWidget);
}

void PropertyWidgetItem::propertyChanged(QString value) { propertyChanged(QVariant(value)); }
void PropertyWidgetItem::propertyChanged(int value) { propertyChanged(QVariant(value)); }
void PropertyWidgetItem::propertyChanged(double value) { propertyChanged(QVariant(value)); }
void PropertyWidgetItem::propertyChanged(QVariant value)
{
    if(!editedObject)
        return;
    
    editedObject->setProperty(propertyName.toUtf8(), value);
}

QWidget *
PropertyWidgetItem::createLineEdit(QVariant value)
{
    QLineEdit * widget = new QLineEdit(this);
    widget->setText(value.toString());
    connect(widget, SIGNAL(textChanged(QString)), this, SLOT(propertyChanged(QString)));
    return widget;
}

QWidget *
PropertyWidgetItem::createSpinBox(QVariant value)
{
    QSpinBox * widget = new QSpinBox(this);
    widget->setValue(value.toInt());
    connect(widget, SIGNAL(valueChanged(int)), this, SLOT(propertyChanged(int)));
    return widget;
}

QWidget *
PropertyWidgetItem::createDoubleSpinBox(QVariant value)
{
    QDoubleSpinBox * widget = new QDoubleSpinBox(this);
    widget->setValue(value.toDouble());
    connect(widget, SIGNAL(valueChanged(double)), this, SLOT(propertyChanged(double)));
    return widget;
}

#include "propertywidgetitem.moc"
