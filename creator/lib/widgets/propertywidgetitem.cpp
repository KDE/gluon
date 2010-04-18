/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
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
#include "propertywidgetitem.h"

#include <QtCore/QVariant>
#include <QtGui/QVBoxLayout>
#include <QtGui/QLayout>

using namespace GluonCreator;

class PropertyWidgetItem::PropertyWidgetItemPrivate
{
    public:
        PropertyWidgetItemPrivate()
        {
            editedObject = 0;
            editWidget = 0;
        }

        QObject *editedObject;
        QString propertyName;
        QWidget *editWidget;
};

PropertyWidgetItem::PropertyWidgetItem(QWidget* parent, Qt::WindowFlags f)
        : QWidget(parent, f)
{
    d = new PropertyWidgetItemPrivate;

    setLayout(new QVBoxLayout());
    layout()->setSpacing(0);
    layout()->setContentsMargins(0, 0, 0, 0);
}

PropertyWidgetItem::~PropertyWidgetItem()
{
    delete d;
}


QWidget*
PropertyWidgetItem::editWidget() const
{
    return d->editWidget;
}

QObject*
PropertyWidgetItem::editObject() const
{
    return d->editedObject;
}

QString
PropertyWidgetItem::editProperty() const
{
    return d->propertyName;
}

const QString
PropertyWidgetItem::typeName() const
{
    return QString(d->editedObject->property(d->propertyName.toUtf8()).typeName());
}

void
PropertyWidgetItem::setEditObject(QObject * editThis)
{
    d->editedObject = editThis;
}

void
PropertyWidgetItem::setEditProperty(const QString& propertyName)
{
    d->propertyName = propertyName;
    if (d->editedObject)
        setEditValue(d->editedObject->property(propertyName.toUtf8()));
}

void
PropertyWidgetItem::setEditWidget(QWidget* widget)
{
    d->editWidget = widget;
    layout()->addWidget(widget);
}

void
PropertyWidgetItem::setEditValue(const QVariant& value)
{
    if (d->editWidget)
        d->editWidget->setProperty("value", value);
}

void
PropertyWidgetItem::valueChanged(QVariant value)
{
    QVariant oldValue = d->editedObject->property(d->propertyName.toUtf8());
    d->editedObject->setProperty(d->propertyName.toUtf8(), value);
    emit propertyChanged(d->editedObject, d->propertyName, oldValue, value);
}

#include "propertywidgetitem.moc"
