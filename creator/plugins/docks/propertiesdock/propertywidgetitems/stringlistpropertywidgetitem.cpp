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

#include "stringlistpropertywidgetitem.h"

#include <KDE/KIcon>
#include <KDE/KLocalizedString>
#include <KDE/KLineEdit>

#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QToolButton>

using namespace GluonCreator;

REGISTER_PROPERTYWIDGETITEM( GluonCreator, StringListPropertyWidgetItem )

Q_DECLARE_METATYPE( QVector<QString> )
Q_DECLARE_METATYPE( QList<QString> )
Q_DECLARE_METATYPE( QStringList )

StringListPropertyWidgetItem::StringListPropertyWidgetItem( QWidget* parent, Qt::WindowFlags f )
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
    countLabel->setText( i18n( "Item count: %1" ).arg( 0 ) );
    layout->addWidget( countLabel, 0, 1 );

    listItems = new QWidget( centralWidget );
    listItems->setLayout( new QVBoxLayout() );
    listItems->layout()->setMargin( 0 );
    listItems->layout()->setSpacing( 0 );
    listItems->setContentsMargins( 0, 0, 0, 0 );
    layout->addWidget( listItems, 1, 0, 1, 2 );

    setEditWidget( centralWidget );
}

StringListPropertyWidgetItem::~StringListPropertyWidgetItem()
{
}


QStringList StringListPropertyWidgetItem::supportedDataTypes() const
{
    QStringList supportedTypes;
    supportedTypes.append( "QVector<QString>" );
    supportedTypes.append( "QList<QString>" );
    supportedTypes.append( "QStringList" );
    return supportedTypes;
}

GluonCreator::PropertyWidgetItem* StringListPropertyWidgetItem::instantiate()
{
    return new StringListPropertyWidgetItem();
}

void StringListPropertyWidgetItem::leValueChanged( QString newValue )
{
    KLineEdit* from = qobject_cast< KLineEdit* >( sender() );
    if( from )
    {
        stringValues.insert( from, newValue );
        valueHasChanged();
    }
}


void StringListPropertyWidgetItem::setEditValue( const QVariant& value )
{
    QGridLayout* layout = qobject_cast<QGridLayout*>( editWidget()->layout() );

    // Clear out any old data...
    textEditorItems.clear();
    stringValues.clear();
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
    QList<QString> items;
    isList = value.canConvert< QList<QString> >();
    isStringList = value.canConvert<QStringList>();
    if( isList )
        items = value.value< QList<QString> >();
    else if( isStringList )
        items = value.toStringList();
    else
        items = value.value< QVector<QString> >().toList();
    if( items.count() > 0 )
    {
        for( int i = 0; i < items.count(); ++i )
        {
            addItem( items[i] );
        }
    }
}

void StringListPropertyWidgetItem::addItem()
{
    addItem( QString() );
    valueHasChanged();
}

void StringListPropertyWidgetItem::addItem( QString value )
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

    KLineEdit* editorLE = new KLineEdit( listItems );
    editorLE->setText( value );
    connect( editorLE, SIGNAL( valueChanged( int ) ), SLOT( leValueHasChanged( QString ) ) );
    containerLayout->addWidget( editorLE );

    listItems->layout()->addWidget( container );
    textEditorItems.insert( removeButton, editorLE );
    stringValues.insert( editorLE, value );
    itemOrder.append( editorLE );
    countLabel->setText( i18n( "Item count: %1" ).arg( stringValues.count() ) );
}

void StringListPropertyWidgetItem::removeClicked()
{
    QToolButton* from = qobject_cast<QToolButton*>( sender() );
    if( from )
    {
        listItems->layout()->removeWidget( from->parentWidget() );
        from->parentWidget()->deleteLater();
        KLineEdit* editorLE = textEditorItems[from];
        textEditorItems.remove( from );
        stringValues.remove( editorLE );
        itemOrder.append( editorLE );
        countLabel->setText( i18n( "Item count: %1" ).arg( 0 ) );
        valueHasChanged();
    }
}

void StringListPropertyWidgetItem::valueHasChanged()
{
    QList<QString> theValues;
    foreach( KLineEdit * item, itemOrder )
    {
        theValues.append( stringValues[item] );
    }
    if( isList )
        PropertyWidgetItem::valueChanged( QVariant::fromValue< QList<QString> >( theValues ) );
    if( isStringList )
        PropertyWidgetItem::valueChanged( QVariant::fromValue< QStringList >( theValues ) );
    else
        PropertyWidgetItem::valueChanged( QVariant::fromValue< QVector<QString> >( QVector<QString>::fromList( theValues ) ) );
}
