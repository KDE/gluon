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
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>
#include <QtGui/QToolButton>

#include <KIcon>
#include <KLocalizedString>

using namespace GluonCreator;

REGISTER_PROPERTYWIDGETITEM( GluonCreator, IntVectorPropertyWidgetItem )

Q_DECLARE_METATYPE( QVector<int> )
Q_DECLARE_METATYPE( QList<int> )

IntVectorPropertyWidgetItem::IntVectorPropertyWidgetItem( QWidget* parent, Qt::WindowFlags f )
    : PropertyWidgetItem( parent, f )
{
    QWidget* centralWidget = new QWidget( this );
    centralWidget->setContentsMargins( 0, 0, 0, 0 );

    QGridLayout* layout = new QGridLayout( centralWidget );
    layout->setSpacing( 0 );

    addButton = new QToolButton( centralWidget );
    addButton->setIcon( KIcon( "list-add" ) );
    connect( addButton, SIGNAL( clicked( bool ) ), SLOT( addItem() ) );
    layout->addWidget( addButton, 0, 0 );

    countLabel = new QLabel( centralWidget );
    countLabel->setText( i18n( "Item count: 0" ) );
    layout->addWidget( countLabel, 0, 1 );

    listItems = new QWidget( centralWidget );
    listItems->setLayout( new QVBoxLayout() );
    listItems->layout()->setMargin( 0 );
    listItems->layout()->setSpacing( 0 );
    listItems->setContentsMargins( 0, 0, 0, 0 );
    layout->addWidget( listItems, 1, 0, 1, 2 );

    setEditWidget( centralWidget );
}

IntVectorPropertyWidgetItem::~IntVectorPropertyWidgetItem()
{
}


QStringList IntVectorPropertyWidgetItem::supportedDataTypes() const
{
    QStringList supportedTypes;
    supportedTypes.append( "QVector<int>" );
    supportedTypes.append( "QList<int>" );
    return supportedTypes;
}

GluonCreator::PropertyWidgetItem* IntVectorPropertyWidgetItem::instantiate()
{
    return new IntVectorPropertyWidgetItem();
}

void IntVectorPropertyWidgetItem::spinValueChanged( int newValue )
{
    QSpinBox* from = qobject_cast< QSpinBox* >( sender() );
    if( from )
    {
        intValues[from] = newValue;
        valueHasChanged();
    }
}


void IntVectorPropertyWidgetItem::setEditValue( const QVariant& value )
{
    QGridLayout* layout = qobject_cast<QGridLayout*>( editWidget()->layout() );

    // Clear out any old data...
    intEditorItems.clear();
    intValues.clear();
    layout->removeItem( layout->itemAt( layout->indexOf( listItems ) ) );
    listItems->deleteLater();

    // Set new value
    listItems = new QWidget( editWidget() );
    listItems->setContentsMargins( 0, 0, 0, 0 );
    listItems->setLayout( new QVBoxLayout() );
    listItems->layout()->setMargin( 0 );
    listItems->layout()->setSpacing( 0 );

    layout->addWidget( listItems, 1, 0, 1, 2 );

    // Rebuild list from this
    QList<int> items;
    isList = value.canConvert< QList<int> >();
    if( isList )
        items = value.value< QList<int> >();
    else
        items = value.value< QVector<int> >().toList();
    if( items.count() > 0 )
    {
        for( int i = 0; i < items.count(); ++i )
        {
            addItem( items[i] );
        }
    }
}

void IntVectorPropertyWidgetItem::addItem()
{
    addItem( 0 );
    valueHasChanged();
}

void IntVectorPropertyWidgetItem::addItem( int value )
{
    QWidget* container = new QWidget( listItems );
    container->setContentsMargins( 0, 0, 0, 0 );
    QHBoxLayout* containerLayout = new QHBoxLayout( container );
    containerLayout->setMargin( 0 );
    containerLayout->setSpacing( 0 );

    QToolButton* removeButton = new QToolButton( listItems );
    removeButton->setIcon( KIcon( "list-remove" ) );
    connect( removeButton, SIGNAL( clicked( bool ) ), SLOT( removeClicked() ) );
    containerLayout->addWidget( removeButton );

    QSpinBox* editorSpin = new QSpinBox( listItems );
    editorSpin->setValue( value );
    connect( editorSpin, SIGNAL( valueChanged( int ) ), SLOT( spinValueChanged( int ) ) );
    containerLayout->addWidget( editorSpin );

    listItems->layout()->addWidget( container );
    intEditorItems.insert( removeButton, editorSpin );
    intValues.insert( editorSpin, value );
    itemOrder.append( editorSpin );
    countLabel->setText( i18n( "Item count: %1", intValues.count() ) );
}

void IntVectorPropertyWidgetItem::removeClicked()
{
    QToolButton* from = qobject_cast<QToolButton*>( sender() );
    if( from )
    {
        listItems->layout()->removeWidget( from->parentWidget() );
        from->parentWidget()->deleteLater();
        QSpinBox* editSpin = intEditorItems[from];
        intEditorItems.remove( from );
        intValues.remove( editSpin );
        itemOrder.removeOne( editSpin );
        countLabel->setText( i18n( "Item count: 0" ) );
        valueHasChanged();
    }
}

void IntVectorPropertyWidgetItem::valueHasChanged()
{
    QList<int> theValues;
    foreach( QSpinBox * item, itemOrder )
    {
        theValues.append( intValues[item] );
    }
    if( isList )
        PropertyWidgetItem::valueChanged( qVariantFromValue< QList<int> >( theValues ) );
    else
        PropertyWidgetItem::valueChanged( qVariantFromValue< QVector<int> >( QVector<int>::fromList( theValues ) ) );
}
