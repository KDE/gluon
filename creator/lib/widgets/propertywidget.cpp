/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2009 Dan Leinir Turthra Jensen <admin@leinir.dk>
 * Copyright (c) 2010 Arjen Hiemstra <>
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

#include "propertywidget.h"

using namespace GluonCreator;

#include "propertywidget.h"
#include "propertywidgetitem.h"
#include "propertywidgetitemfactory.h"

#include <core/gluonobject.h>
#include <core/debughelper.h>

#include <QtCore/QVariant>
#include <QtCore/QMetaClassInfo>

#include <QtGui/QBoxLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>

class PropertyWidget::PropertyWidgetPrivate
{
    public:
        PropertyWidgetPrivate()
        {
            object = 0;
            layout = 0;
        }
        GluonCore::GluonObject *object;
        QVBoxLayout *layout;

        void appendMetaObject(QWidget* parent, QObject* object, QGridLayout* layout);
};


PropertyWidget::PropertyWidget(QWidget* parent): QScrollArea(parent), d(new PropertyWidgetPrivate)
{
}

PropertyWidget::~PropertyWidget()
{
    delete d;
}

GluonCore::GluonObject *PropertyWidget::object() const
{
    return d->object;
}

void PropertyWidget::setObject(GluonCore::GluonObject * object)
{
    if (object)
    {
        d->object = object;
        d->layout = new QVBoxLayout(this);
        d->layout->setSpacing(0);
        d->layout->setContentsMargins(0, 0, 0, 0);
        d->layout->setAlignment(Qt::AlignTop);

        appendObject(object, true);
        for (int i = 0; i < object->children().count(); i++)
        {
            appendObject(object->child(i));
        }
        d->layout->addStretch();

        QWidget * containerWidget = new QWidget(this);
        containerWidget->setLayout(d->layout);

        setWidget(containerWidget);
        setWidgetResizable(true);
    }
}

void PropertyWidget::clear()
{
    delete widget();
}

void PropertyWidget::appendObject(GluonCore::GluonObject *obj, bool first)
{
    if (!first && obj->metaObject()->className() == QString("GluonEngine::GameObject"))
    {
        return;
    }

    QString classname = obj->metaObject()->className();
    classname = classname.right(classname.length() - classname.lastIndexOf(':') - 1);
    #ifdef __GNUC__
    #warning We will need to replace the group box with a custom widget of some type, as we cannot collapse it. Unfortunate, but such is life ;)
    #endif
    QGroupBox* objectBox = new QGroupBox(classname, this);

    objectBox->setFlat(true);
    objectBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    if (first)
    {
        long addr = reinterpret_cast<long>(obj);
        QColor color;
        color.setHsv(addr % 255, 255, 192);
        objectBox->setPalette(QPalette(color));
    }

    d->layout->addWidget(objectBox);

    QGridLayout* boxLayout = new QGridLayout(objectBox);
    boxLayout->setSpacing(0);
    boxLayout->setContentsMargins(0, 0, 0, 0);
    objectBox->setLayout(boxLayout);

    d->appendMetaObject(this, obj, boxLayout);
}

void PropertyWidget::PropertyWidgetPrivate::appendMetaObject(QWidget *parent, QObject *object, QGridLayout* layout)
{
    QString propertyName;
    QString propertyDescription;
    QVariant propertyValue;

    const QMetaObject *metaObject = object->metaObject();
    QMetaProperty metaProperty;

    int row;
    int count = metaObject->propertyCount();
    for (int i = 0; i < count; ++i)
    {
        row = layout->rowCount();
        metaProperty = metaObject->property(i);

        if (metaProperty.name() == QString("objectName"))
            continue;

        QLabel * nameLabel = new QLabel(parent);
        nameLabel->setText(metaProperty.name());
        nameLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        layout->addWidget(nameLabel, row, 0);

        PropertyWidgetItem *editWidget = PropertyWidgetItemFactory::instance()->create(object, metaProperty.typeName(), parent);
        editWidget->setEditObject(object);
        editWidget->setEditProperty(metaProperty.name());
        connect(editWidget, SIGNAL(propertyChanged(QObject*, QString, QVariant, QVariant)), parent, SIGNAL(propertyChanged(QObject*, QString, QVariant, QVariant)));
        editWidget->setMinimumWidth(250);
        editWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        layout->addWidget(editWidget, row, 1);
    }

    foreach(const QByteArray &propName, object->dynamicPropertyNames())
    {
        QString thePropName(propName);
        row = layout->rowCount();
        QLabel * nameLabel = new QLabel(parent);
        nameLabel->setText(thePropName);
        nameLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        layout->addWidget(nameLabel, row, 0);

        PropertyWidgetItem *editWidget = PropertyWidgetItemFactory::instance()->create(object, object->property(propName).typeName(), parent);
        editWidget->setEditObject(object);
        editWidget->setEditProperty(thePropName);
        connect(editWidget, SIGNAL(propertyChanged(QObject*, QString, QVariant, QVariant)), parent, SIGNAL(propertyChanged(QObject*, QString, QVariant, QVariant)));
        editWidget->setMinimumWidth(250);
        editWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        layout->addWidget(editWidget);
    }
}

#include "propertywidget.moc"
