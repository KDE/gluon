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

#include "propertywidget.h"

using namespace GluonCreator;

#include <QtCore/QVariant>
#include <QtCore/QMetaClassInfo>

#include <QtGui/QBoxLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>

#include <core/gluonobject.h>
#include <core/debughelper.h>

#include "propertywidget.h"
#include "propertywidgetitems/propertywidgetitem.h"
#include "propertywidgetitems/propertywidgetitemfactory.h"

class PropertyWidget::PropertyWidgetPrivate
{
    public:
        PropertyWidgetPrivate() { object = 0; layout = 0; }
        GluonCore::GluonObject *object;
        QVBoxLayout *layout;
};


PropertyWidget::PropertyWidget(QWidget* parent): QScrollArea(parent)
{
    d = new PropertyWidgetPrivate;
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
    if(object)
    {
        d->object = object;
        d->layout = new QVBoxLayout(this);

        appendObject(object, true);
        for(int i = 0; i < object->children().count(); i++)
        {
            appendObject(object->child(i));
        }

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

void PropertyWidget::appendObject(GluonCore::GluonObject *obj, bool useColor)
{
    QGroupBox* objectBox = new QGroupBox(obj->name(), this);
    objectBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    if(useColor)
    {
        long addr = reinterpret_cast<long>(obj);
        QColor color;
        color.setHsv(addr % 255, 255, 192);
        objectBox->setPalette(QPalette(color));
    }

    d->layout->addWidget(objectBox);

    QGridLayout* boxLayout = new QGridLayout(objectBox);
    objectBox->setLayout(boxLayout);

    appendMetaObject(obj, boxLayout);
}

void PropertyWidget::appendMetaObject(QObject * object, QGridLayout* layout)
{
    QString propertyName;
    QString propertyDescription;
    QVariant propertyValue;

    const QMetaObject *metaObject = object->metaObject();
    QMetaProperty metaProperty;

    int row;
    int count = metaObject->propertyCount();
    for (int i=0; i<count; ++i)
    {
        row = layout->rowCount();
        metaProperty = metaObject->property(i);

        if(metaProperty.name() == QString("objectName"))
            continue;

        QLabel * nameLabel = new QLabel(this);
        nameLabel->setText(metaProperty.name());
        nameLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        layout->addWidget(nameLabel, row, 0);

        PropertyWidgetItem *editWidget = PropertyWidgetItemFactory::instance()->create(metaProperty.typeName(), this);
        editWidget->setEditObject(object);
        editWidget->setEditProperty(metaProperty.name());
        editWidget->setMinimumWidth(250);
        editWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        layout->addWidget(editWidget, row, 1);
    }
}

#include "propertywidget.moc"
