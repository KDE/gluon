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

using namespace Gluon::Creator;

#include <QBoxLayout>
#include <QVariant>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QtCore/QMetaClassInfo>

#include "propertywidget.h"
#include "propertywidgetitem.h"
#include "gluon/component.h"
#include "gluon/gluonobject.h"

PropertyWidget::PropertyWidget(QObject * parent)
{
}

PropertyWidget::~PropertyWidget()
{
}

void
PropertyWidget::appendToPropertyView (QGridLayout * layout, qint32 &row, QObject * object, QString name, QString description)
{
    appendToPropertyView(layout, row, object, name, description, QVariant());
}

void
PropertyWidget::appendToPropertyView (QGridLayout * layout, qint32 &row, QObject * object, QString name, QString description, QVariant options)
{
    ++row;
    
    QLabel * nameLabel = new QLabel(this);
    nameLabel->setText(name);
    nameLabel->setToolTip(description);
    layout->addWidget(nameLabel, row, 0);
    
    PropertyWidgetItem * editWidget = new PropertyWidgetItem(this);
    editWidget->setEditObject(object);
    editWidget->setEditProperty(name);
    layout->addWidget(editWidget, row, 1);
}

void
PropertyWidget::appendMetaObjectToPropertyView (QGridLayout * layout, qint32 &row, QObject * object)
{
    QString propertyName, propertyDescription;
    QVariant propertyValue;
    
    const QMetaObject *metaobject = object->metaObject();
    
    int count = metaobject->propertyCount();
    for (int i=0; i<count; ++i)
    {
        QMetaProperty metaproperty = metaobject->property(i);
        propertyName = metaproperty.name();
        if(propertyName == "objectName")
            continue;
        propertyValue = object->property(propertyName.toUtf8());
        appendToPropertyView(layout, row, object, propertyName, propertyDescription);
    }
    
    foreach(QByteArray name, object->dynamicPropertyNames())
    {
        propertyName = QString(name);
        propertyValue = object->property(name);
        appendToPropertyView(layout, row, object, propertyName, propertyDescription);
    }
}

void
PropertyWidget::appendObjectToPropertyView (QGridLayout * layout, qint32 &row, Gluon::GluonObject * node)
{
    ++row;
    QLabel * titleLabel = new QLabel(this);
    titleLabel->setText(node->name());
    // Just grab this one in this manner - you can't guarantee it exists, but it's likely to be there. Yes, this is slower, but it always works.
    titleLabel->setToolTip(node->property("description").toString());
    layout->addWidget(titleLabel, row, 0, 1, 2);
 
    // Add a new property line for each property in the object's metaobject...
    QObject *object = node;
    appendMetaObjectToPropertyView(layout, row, object);
}

void
PropertyWidget::appendSubobjectToPropertyView (QGridLayout * layout, qint32 &row, Gluon::GluonObject * node)
{
    // TODO We're doing this for now... i am thinking it might be interesting to allow the subobject titles to be styled differently, so... :)
    appendObjectToPropertyView(layout, row, node);
    /*++row;
    QLabel * titleLabel = new QLabel(this);
    titleLabel->setText(node->name());
    // Just grab this one in this manner - you can't guarantee it exists, but it's likely to be there. Yes, this is slower, but it always works.
    titleLabel->setToolTip(QString(node->property("description")));
    layout->addWidget(titleLabel, row, 0, 1, 2);
    
    // Add a new property line for each property in the object's metaobject...
    QObject *object = node;
    appendMetaObjectToPropertyView(layout, row, object);*/
}

void
PropertyWidget::setupPropertyView()
{
    QGridLayout * propertyLayout = new QGridLayout(this);
    propertyLayout->setMargin(0);
    propertyLayout->setSpacing(0);
    
    qint32 row = 0;

    // First add yourself...
    appendObjectToPropertyView(propertyLayout, row, this->object());
    
    // Then add all the decorators...
    for(int i = 0; i < this->object()->children().count(); i++)
    {
        appendSubobjectToPropertyView(propertyLayout, row, qobject_cast<Gluon::GluonObject*>(this->object()->children()[i]));
    }
    
    // Add spacery type stuffs...
    QWidget * containerWidget = new QWidget(this);
    containerWidget->setLayout(propertyLayout);
    
    QVBoxLayout * containerLayout = new QVBoxLayout(this);
    containerLayout->addWidget(containerWidget);
    containerLayout->addStretch();
    containerLayout->setSpacing(0);
    containerLayout->setMargin(0);
    
    this->setLayout(containerLayout);
}

Gluon::GluonObject *
PropertyWidget::object() const
{
    return m_object;
}

void
PropertyWidget::setObject(Gluon::GluonObject * node)
{
    m_object = node;
    setupPropertyView();
}
