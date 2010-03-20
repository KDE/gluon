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

#include <QVariant>

#include "propertywidgetitem.h"
#include <QVBoxLayout>
#include <QLayout>

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
