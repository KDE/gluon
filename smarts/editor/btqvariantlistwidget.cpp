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

#include "btqvariantlistwidget.h"

btQVariantListWidget::btQVariantListWidget(bool enabled, QWidget * parent) : QWidget(parent)
{
    // layout
    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(0);
    listWidget = new QListWidget();
    
    listWidget->setSelectionMode(QListView::SingleSelection);
    
    removeButton = new QPushButton(tr("-"));
    addButton = new QPushButton(tr("+"));
    
    if(!enabled)
    {
        removeButton->setEnabled(false);
        addButton->setEnabled(false);
    }
    
    buttonLayout->addStretch();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(removeButton);
    buttonLayout->addSpacing(1);
    mainLayout->addWidget(listWidget);
    mainLayout->addLayout(buttonLayout);
    this->setLayout(mainLayout);
    
    setupActions();
}

btQVariantListWidget::~btQVariantListWidget()
{
}

void btQVariantListWidget::setupActions()
{
    connect(addButton, SIGNAL(clicked(bool)), this, SLOT(insertItem()));
    connect(removeButton, SIGNAL(clicked(bool)), this, SLOT(removeItem()));
    connect(listWidget, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(changeItem(QListWidgetItem*)));
}

void btQVariantListWidget::insertItem()
{
    QListWidgetItem * item = new QListWidgetItem("New Item");
    item->setFlags(returnItemFlags());
    listWidget->addItem(item);
    emit itemAdded(item);
}

void btQVariantListWidget::removeItem()
{
    int currentRow = listWidget->currentRow();
    QListWidgetItem * item = listWidget->takeItem(currentRow);
    emit itemRemoved(item, currentRow);
}

Qt::ItemFlags btQVariantListWidget::returnItemFlags()
{
    Qt::ItemFlags flags = (Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    return flags;
}

void btQVariantListWidget::changeItem(QListWidgetItem * item)
{
    emit itemChanged(item, listWidget->currentRow());
}

void btQVariantListWidget::addItem(QListWidgetItem * item)
{
    listWidget->addItem(item);
}

#include "btqvariantlistwidget.moc"
