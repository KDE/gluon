/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2009 Dan Leinir Turthra Jensen <admin@leinir.dk>
 * Copyright (c) 2009 Kim Jung Nissen <jungnissen@gmail.com>
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

#include "btpropertywidgetitem.h"

#include "btglobal.h"

#include "btqvariantlistwidget.h"
#include "btchildlistwidget.h"
#include "bteditornode.h"
#include "bteditornodetype.h"
#include "btparallelconditionswidget.h"

#include <QtGui/QListWidgetItem>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>
#include <QtGui/QLineEdit>
#include <QtGui/QGridLayout>

btPropertyWidgetItem::btPropertyWidgetItem(QObject * parent, Qt::WindowFlags f)
{
    Q_UNUSED(parent)
    Q_UNUSED(f)

    QGridLayout * layout = new QGridLayout(this);
    layout->setSpacing(0);
    layout->setMargin(0);
    setLayout(layout);
}

btPropertyWidgetItem::~btPropertyWidgetItem()
{
    if (qobject_cast<btEditorNodeType*>(editedObject))
    {
        btEditorNodeType * nodeType = qobject_cast<btEditorNodeType*>(editedObject);

        if (nodeType->metaObject()->indexOfProperty(propertyName.toUtf8()) > -1)
        {
            QLineEdit * lineEdit = qobject_cast<QLineEdit*>(editWidget);

            if (propertyName == "className")
            {
                disconnect(nodeType, SIGNAL(classNameChanged(QString)), lineEdit, SLOT(setText(QString)));
            }
            else if (propertyName == "name")
            {
                disconnect(nodeType, SIGNAL(nameChanged(QString)), lineEdit, SLOT(setText(QString)));
            }
            else if (propertyName == "description")
            {
                disconnect(nodeType, SIGNAL(descriptionChanged(QString)), lineEdit, SLOT(setText(QString)));
            }
        }
    }
}

void btPropertyWidgetItem::setEditObject(QObject * editThis)
{
    editedObject = editThis;
}


void btPropertyWidgetItem::setEditProperty(QString propertyName, bool enabled)
{
    propertyName = propertyName;
    setupPropertyWidget(enabled);
}

void btPropertyWidgetItem::setupPropertyWidget(bool enabled)
{
    qRegisterMetaType<btChildWeights>("btChildWeights");
    qRegisterMetaType<btParallelConditions>("btParallelConditions");

    if (!editedObject)
        return;

    QVariant value = editedObject->property(propertyName.toUtf8());
    switch (value.type())
    {
    case QVariant::String:
        editWidget = createLineEdit(value, enabled);
        break;
    case QVariant::Int:
        editWidget = createSpinBox(value, enabled);
        break;
    case QVariant::Double:
        editWidget = createDoubleSpinBox(value, enabled);
        break;
    case QVariant::List:
        editWidget = createList(value, enabled);
        break;
    case QVariant::UserType:
        if (propertyName == "weights")
        {
            editWidget = createChildProbabilitiesList(propertyName, enabled);
        }
        else if (propertyName == "conditions")
        {
            editWidget = createParallelConditionsList(propertyName, enabled);
        }
        break;
    default:
        editWidget = new QLabel(this);
        qobject_cast<QLabel*>(editWidget)->setText(tr("Unknown type (%1)").arg(value.toString()));
        break;
    }

    layout()->addWidget(editWidget);
}

void btPropertyWidgetItem::propertyChanged(QString value) {
    propertyChanged(QVariant(value));
}
void btPropertyWidgetItem::propertyChanged(int value) {
    propertyChanged(QVariant(value));
}
void btPropertyWidgetItem::propertyChanged(double value) {
    propertyChanged(QVariant(value));
}
void btPropertyWidgetItem::propertyChanged(QVariant value)
{
    if (!editedObject)
        return;

    editedObject->setProperty(propertyName.toUtf8(), value);

    emit sendUpdateTreeModel();
}

void btPropertyWidgetItem::QVariantListItemRemoved(QListWidgetItem * item, int index)
{
    if (!editedObject || !item)
        return;

    QVariant value = editedObject->property(propertyName.toUtf8());
    int typeId = QMetaType::type(editedObject->property(propertyName.toUtf8()).toString().toUtf8());

    QVariantList list;

    if (!typeId)
    {
        typeId = value.type();
        list = qvariant_cast<QVariantList>(value);
    }
    else
    {
        list = qvariant_cast<QVariantList>(QVariant((QVariant::Type)typeId));
    }

    if (list.contains(item->text()))
    {
        delete item;
        list.removeAt(index);
    }

    editedObject->setProperty(propertyName.toUtf8(), list);
}

void btPropertyWidgetItem::QVariantListItemAdded(QListWidgetItem * item)
{
    if (!editedObject)
        return;

    QVariant value = editedObject->property(propertyName.toUtf8());
    int typeId = QMetaType::type(editedObject->property(propertyName.toUtf8()).toString().toUtf8());

    QVariantList list;

    if (!typeId)
    {
        typeId = value.type();
        list = qvariant_cast<QVariantList>(value);
    }
    else
    {
        list = qvariant_cast<QVariantList>(QVariant((QVariant::Type)typeId));
    }
    list.append(item->text());
    editedObject->setProperty(propertyName.toUtf8(), list);
}

void btPropertyWidgetItem::QVariantListItemChanged(QListWidgetItem * item, int index)
{
    if (!editedObject || index < 0)
        return;

    QVariant value = editedObject->property(propertyName.toUtf8());
    int typeId = QMetaType::type(editedObject->property(propertyName.toUtf8()).toString().toUtf8());

    QVariantList list;

    if (!typeId)
    {
        typeId = value.type();
        list = qvariant_cast<QVariantList>(value);
    }
    else
    {
        list = qvariant_cast<QVariantList>(QVariant((QVariant::Type)typeId));
    }

    list.replace(index, item->text());

    editedObject->setProperty(propertyName.toUtf8(), list);
}

QWidget * btPropertyWidgetItem::createLineEdit(QVariant value, bool enabled)
{
    QLineEdit * widget = new QLineEdit(this);
    widget->setText(value.toString());
    widget->setEnabled(enabled);

    if (qobject_cast<btEditorNodeType*>(editedObject))
    {
        btEditorNodeType * nodeType = qobject_cast<btEditorNodeType*>(editedObject);

        if (nodeType->metaObject()->indexOfProperty(propertyName.toUtf8()) > -1)
        {
            QLineEdit * lineEdit = qobject_cast<QLineEdit*>(widget);

            if (propertyName == "className")
            {
                connect(nodeType, SIGNAL(classNameChanged(QString)), lineEdit, SLOT(setText(QString)));
            }
            else if (propertyName == "name")
            {
                connect(nodeType, SIGNAL(nameChanged(QString)), lineEdit, SLOT(setText(QString)));
            }
            else if (propertyName == "description")
            {
                connect(nodeType, SIGNAL(descriptionChanged(QString)), lineEdit, SLOT(setText(QString)));
            }
        }
    }


    connect(widget, SIGNAL(textChanged(QString)), this, SLOT(propertyChanged(QString)));
    return widget;
}

QWidget * btPropertyWidgetItem::createSpinBox(QVariant value, bool enabled)
{
    QSpinBox * widget = new QSpinBox(this);
    widget->setRange(-32000,32000);
    widget->setValue(value.toInt());
    widget->setEnabled(enabled);
    connect(widget, SIGNAL(valueChanged(int)), this, SLOT(propertyChanged(int)));
    return widget;
}

QWidget * btPropertyWidgetItem::createDoubleSpinBox(QVariant value, bool enabled)
{
    QDoubleSpinBox * widget = new QDoubleSpinBox(this);
    widget->setValue(value.toDouble());
    widget->setEnabled(enabled);
    connect(widget, SIGNAL(valueChanged(double)), this, SLOT(propertyChanged(double)));
    return widget;
}

QWidget * btPropertyWidgetItem::createList(QVariant value, bool enabled)
{
    btQVariantListWidget * widget = new btQVariantListWidget(this);
    connect(widget, SIGNAL(itemRemoved(QListWidgetItem*,int)), this, SLOT(QVariantListItemRemoved(QListWidgetItem*,int)));
    connect(widget, SIGNAL(itemAdded(QListWidgetItem*)), this, SLOT(QVariantListItemAdded(QListWidgetItem*)));
    connect(widget, SIGNAL(itemChanged(QListWidgetItem*,int)), this, SLOT(QVariantListItemChanged(QListWidgetItem*,int)));

    QVariantList list = qvariant_cast<QVariantList>(value);

    for (int i = 0; i < list.count(); i++)
    {
        QListWidgetItem * item = new QListWidgetItem(list.at(i).toString());
        item->setFlags(widget->returnItemFlags());
        widget->addItem(item);
    }

    widget->setEnabled(enabled);
    return widget;
}

const QString btPropertyWidgetItem::getPropertyType(QString propertyName)
{
    Q_UNUSED(propertyName)
    return "";
}

QWidget * btPropertyWidgetItem::createChildProbabilitiesList(QString propertyName ,bool enabled)
{
    btChildListWidget* widget = new btChildListWidget(this);

    widget->setChildProbabilites(propertyName, editedObject, enabled);

    return widget;
}

QWidget * btPropertyWidgetItem::createParallelConditionsList(QString propertyName, bool enabled)
{
    btParallelConditionsWidget * widget = new btParallelConditionsWidget(this);

    widget->setParallelConditions(propertyName, editedObject, enabled);

    return widget;
}

 
