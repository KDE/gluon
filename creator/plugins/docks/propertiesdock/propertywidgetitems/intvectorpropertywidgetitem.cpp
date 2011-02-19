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

#include "intvectorpropertywidgetitem.h"
#include <QtGui/QGridLayout>
#include <QtGui/QPushButton>
#include <KIcon>

using namespace GluonCreator;

REGISTER_PROPERTYWIDGETITEM( GluonCreator, IntVectorPropertyWidgetItem )

IntVectorPropertyWidgetItem::IntVectorPropertyWidgetItem( QWidget* parent, Qt::WindowFlags f )
    : PropertyWidgetItem( parent, f )
{
    QWidget* centralWidget = new QWidget(this);
    
    QGridLayout* layout = new QGridLayout(centralWidget);
    
    listItems = new QWidget(centralWidget);
    layout->addWidget( listItems, 0, 0, 1, 2 );
    
    addButton = new QPushButton(centralWidget);
    addButton->setIcon( KIcon("list-add") );
    layout->addWidget( addButton, 1, 0 );
    
    removeButton = new QPushButton(centralWidget);
    removeButton->setIcon( KIcon("list-remove") );
    layout->addWidget( removeButton, 1, 1 );
    
    setEditWidget(centralWidget);
}

IntVectorPropertyWidgetItem::~IntVectorPropertyWidgetItem()
{

}


QStringList IntVectorPropertyWidgetItem::supportedDataTypes() const
{
    QStringList supportedTypes;
    supportedTypes.append( "QVector<int>" );
    supportedTypes.append( "QMatrix4x4" );
    return supportedTypes;
}

GluonCreator::PropertyWidgetItem* IntVectorPropertyWidgetItem::instantiate()
{
    return new IntVectorPropertyWidgetItem();
}

void IntVectorPropertyWidgetItem::setEditValue(const QVariant& value)
{
    GluonCreator::PropertyWidgetItem::setEditValue(value);
}
