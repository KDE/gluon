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

#include "btpropertywidget.h"

#include "btpropertywidgetitem.h"
#include "bteditornode.h"
#include "bteditornodetype.h"
#include "colorgen.h"

#include <QBoxLayout>
#include <QVariant>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QtCore/QMetaClassInfo>
#include <QToolButton>
#include <QDebug>
#include <QMenu>
#include <QAction>

btPropertyWidget::btPropertyWidget(QObject * parent)
{
    Q_UNUSED(parent)
    colorgen = NULL;
    m_node = NULL;
}

btPropertyWidget::~btPropertyWidget()
{
    qDeleteAll(this->children());
    delete colorgen;
}

void btPropertyWidget::appendToPropertyView (QGridLayout * layout, qint32 &row, QObject * object, QString name, QString description, bool enabled, QVariant options)
{
    Q_UNUSED(options)
    ++row;

    QLabel * nameLabel = new QLabel(this);
    nameLabel->setText(name);
    nameLabel->setToolTip(description);
    layout->addWidget(nameLabel, row, 0);
    nameLabel->setAlignment(Qt::AlignTop);

    btPropertyWidgetItem * editWidget = new btPropertyWidgetItem(this);
    connect(editWidget,SIGNAL(sendUpdateTreeModel()), this, SLOT(updateTreeModel()));
    editWidget->setEditObject(object);
    editWidget->setEditProperty(name, enabled);
    layout->addWidget(editWidget, row, 1);
}

void btPropertyWidget::appendMetaObjectToPropertyView (QGridLayout * layout, qint32 &row, QObject * object, bool enabled)
{
    QString propertyName, propertyDescription;
    QVariant propertyValue;

    const QMetaObject *metaobject = object->metaObject();

    int count = metaobject->propertyCount();
    for (int i=0; i<count; ++i)
    {
        QMetaProperty metaproperty = metaobject->property(i);
        propertyName = metaproperty.name();
        if (propertyName == "objectName")
            continue;

        propertyValue = object->property(propertyName.toUtf8());
        propertyDescription = getPropertyDescription(object, propertyName);
        appendToPropertyView(layout, row, object, propertyName, propertyDescription, enabled);
    }

    foreach(const QByteArray& name, object->dynamicPropertyNames())
    {
        propertyName = QString(name);
        propertyValue = object->property(name);
        propertyDescription = getPropertyDescription(object, propertyName);;
        appendToPropertyView(layout, row, object, propertyName, propertyDescription, true);
    }
}

void btPropertyWidget::appendObjectToPropertyView (QGridLayout * layout, qint32 &row, btEditorNode * node, bool enabled)
{
    ++row;
    QLabel * titleLabel = new QLabel(this);
    titleLabel->setText(node->name());
    titleLabel->setToolTip(node->description());
    titleLabel->setStyleSheet("background-color: " + colorgen->nextColor().name());
    layout->addWidget(titleLabel, row, 0, 1, 2);

    // Add a new property line for each property in the object's metaobject...
    QObject *object = node;
    appendMetaObjectToPropertyView(layout, row, object, enabled);

}

void btPropertyWidget::appendComponentToPropertyView (QGridLayout * layout, qint32 &row, btEditorNodeType * node, bool enabled)
{
    ++row;
    QLabel * titleLabel = new QLabel(this);

    titleLabel->setStyleSheet("background-color: " + colorgen->nextColor().name());
    if (QString(node->metaObject()->className()) == "btDecoratorNode")
    {
        titleLabel->setText(node->name());
        titleLabel->setToolTip(node->description());

        QHBoxLayout * hLayout = new QHBoxLayout();
        hLayout->addWidget(titleLabel);

        QToolButton * showMenuButton = new QToolButton(this);

        QMenu * buttonMenu = new QMenu(showMenuButton);

        btEditorNode* parent = qobject_cast<btEditorNode*>(node->parentNode());

        if (parent->decorators().indexOf(node) > 0)
        {
            QAction* upAction = new QAction(buttonMenu);
            upAction->setText("Move up");
            connect(upAction, SIGNAL(triggered()), node, SLOT(moveUpAction()));
            buttonMenu->addAction(upAction);
        }

        if (parent->decorators().indexOf(node) < parent->decoratorCount()-1)
        {
            QAction* downAction = new QAction(buttonMenu);
            downAction->setText("Move down");
            connect(downAction, SIGNAL(triggered()), node, SLOT(moveDownAction()));
            buttonMenu->addAction(downAction);
        }

        QAction * removeAction = new QAction(buttonMenu);
        removeAction->setText("Remove");
        connect(removeAction, SIGNAL(triggered()), node, SLOT(removeActionTriggered()));

        QAction * sep = buttonMenu->addSeparator();
        sep->setParent(this);
        buttonMenu->addAction(removeAction);

        showMenuButton->setText("Menu");
        showMenuButton->setMenu(buttonMenu);
        showMenuButton->setPopupMode(QToolButton::InstantPopup);

        hLayout->addWidget(showMenuButton);

        layout->addLayout(hLayout, row, 0,1,2);
    }
    else
    {
        titleLabel->setText(node->name());
        layout->addWidget(titleLabel, row, 0, 1, 2);
    }

    // Add a new property line for each property in the object's metaobject...
    QObject *object = node;
    appendMetaObjectToPropertyView(layout, row, object, enabled);
}

void btPropertyWidget::setupPropertyView()
{
    qDeleteAll(this->children());
    delete colorgen;

    colorgen = new ColorGen(0,70,30);

    QGridLayout * propertyLayout = new QGridLayout(this);
    propertyLayout->setMargin(0);
    propertyLayout->setSpacing(0);

    qint32 row = 0;

    // First add yourself...
    appendObjectToPropertyView(propertyLayout, row, this->node(), true);

    // Then add all the decorators...
    for (int i = 0; i < this->node()->decoratorCount(); i++)
    {
        appendComponentToPropertyView(propertyLayout, row, qobject_cast<btEditorNodeType*>(this->node()->decorators()[i]), false);
    }

    // Finally, add the node's nodeType
    appendComponentToPropertyView(propertyLayout, row, qobject_cast<btEditorNodeType*>(node()->type()), false);

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

btEditorNode * btPropertyWidget::node() const
{
    return m_node;
}

void btPropertyWidget::setNode(btEditorNode * node)
{
    /*if(m_node)
    {
        disconnect(m_node, SIGNAL(updatePropertyWidget()), this, SLOT(dragDropUpdate()));
    }*/

    m_node = node;
    //connect(m_node, SIGNAL(updatePropertyWidget()), this, SLOT(dragDropUpdate()));
    setupPropertyView();
}

QString btPropertyWidget::getPropertyDescription(QObject *object, QString propertyName)
{
    btEditorNodeType * node = qobject_cast<btEditorNodeType*>(object);

    if (node == NULL)
        return "";

    return node->getPropertyDescription(propertyName);
}

void btPropertyWidget::dragDropUpdate()
{
    if (m_node != NULL)
    {
        setupPropertyView();
    }
}

void btPropertyWidget::updateTreeModel()
{
    emit treeModelUpdate();
}

#include "btpropertywidget.moc"
