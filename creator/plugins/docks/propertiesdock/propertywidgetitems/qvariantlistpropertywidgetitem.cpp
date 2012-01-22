/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  Dan Leinir Turthra Jensen <admin@leinir.dk>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/


#include "qvariantlistpropertywidgetitem.h"
#include "core/debughelper.h"

#include <KIcon>
#include <KLocalizedString>

#include <QtGui/QGridLayout>
#include <QtGui/QToolButton>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>
#include <QtGui/QLineEdit>
#include <QtGui/QMenu>

using namespace GluonCreator;

REGISTER_PROPERTYWIDGETITEM( GluonCreator, QVariantListPropertyWidgetItem )

Q_DECLARE_METATYPE( QVariantList )

QVariantListPropertyWidgetItem::QVariantListPropertyWidgetItem(QWidget* parent, Qt::WindowFlags f)
    : PropertyWidgetItem(parent, f)
{
    additionMenu = new QMenu(this);
    QAction* addInt = new QAction(i18n("Integer"), additionMenu);
    addInt->setData(QVariant(0));
    connect(addInt, SIGNAL(triggered(bool)), SLOT(addItem()));
    additionMenu->addAction(addInt);
    QAction* addDouble = new QAction(i18n("Floating point number"), additionMenu);
    addDouble->setData(QVariant(1));
    connect(addDouble, SIGNAL(triggered(bool)), SLOT(addItem()));
    additionMenu->addAction(addDouble);
    QAction* addString = new QAction(i18n("String"), additionMenu);
    addString->setData(QVariant(2));
    connect(addString, SIGNAL(triggered(bool)), SLOT(addItem()));
    additionMenu->addAction(addString);

    QWidget* centralWidget = new QWidget( this );
    centralWidget->setContentsMargins( 0, 0, 0, 0 );

    QGridLayout* layout = new QGridLayout( centralWidget );
    layout->setSpacing( 0 );

    addButton = new QToolButton( centralWidget );
    addButton->setIcon( KIcon( "list-add" ) );
    connect( addButton, SIGNAL(clicked(bool)), SLOT(showAdditionMenu()) );
    layout->addWidget( addButton, 0, 0 );

    countLabel = new QLabel( centralWidget );
    countLabel->setText( i18n( "Item count: %1" ).arg(0) );
    layout->addWidget( countLabel, 0, 1 );

    listItems = new QWidget( centralWidget );
    listItems->setLayout( new QVBoxLayout() );
    listItems->layout()->setMargin( 0 );
    listItems->layout()->setSpacing( 0 );
    listItems->setContentsMargins( 0, 0, 0, 0 );
    layout->addWidget( listItems, 1, 0, 1, 2 );

    setEditWidget( centralWidget );
}

QVariantListPropertyWidgetItem::~QVariantListPropertyWidgetItem()
{
}

QStringList QVariantListPropertyWidgetItem::supportedDataTypes() const
{
    QStringList supportedTypes;
    supportedTypes.append( "QVariantList" );
    return supportedTypes;
}

GluonCreator::PropertyWidgetItem* QVariantListPropertyWidgetItem::instantiate()
{
    return new QVariantListPropertyWidgetItem();
}

void QVariantListPropertyWidgetItem::showAdditionMenu()
{
    additionMenu->popup( addButton->mapToGlobal( QPoint( 0, addButton->height() ) ) );
}

void QVariantListPropertyWidgetItem::addItem()
{
    DEBUG_FUNC_NAME
    QAction* theAction = qobject_cast< QAction* >( sender() );
    if( theAction )
    {
        if( theAction->data().isValid() )
        {
            int addWhat = theAction->data().toInt();
            DEBUG_TEXT2("Attempting to add an item of type %1", addWhat);
            switch(addWhat)
            {
                case Integer:
                    addItem(QVariant(0));
                    break;
                case Float:
                    addItem(QVariant(0.0));
                    break;
                case String:
                    addItem(QVariant(QLatin1String("")));
                    break;
                default:
                    addItem(QVariant());
                    break;
            }
        }
        else
        {
            DEBUG_TEXT("The caller had no int data!");
            addItem(QVariant());
        }
    }
    else
    {
        DEBUG_TEXT("The caller was not an action");
        addItem(QVariant());
    }
}

void QVariantListPropertyWidgetItem::addItem(QVariant value)
{
    DEBUG_BLOCK
    QWidget* editorWidget = 0;
    QSpinBox* editorSpin = 0;
    QDoubleSpinBox* editorDSpin = 0;
    QLineEdit* editorLE = 0;

    ValueTypes valueType = UnknownType;
    switch(value.type())
    {
        case QVariant::Int:
            valueType = Integer;
            break;
        case QVariant::Double:
            valueType = Float;
            break;
        case QVariant::String:
            valueType = String;
            break;
        default:
            break;
    }

    DEBUG_TEXT2("Adding an item with value type %1", valueType);
    switch(valueType)
    {
        case Integer:
            editorSpin = new QSpinBox(listItems);
            editorSpin->setValue( value.toInt() );
            connect( editorSpin, SIGNAL(valueChanged(int)), SLOT(spinValueChanged(int)) );
            editorWidget = editorSpin;
            break;
        case Float:
            editorDSpin = new QDoubleSpinBox(listItems);
            editorDSpin->setValue( value.toDouble() );
            connect( editorDSpin, SIGNAL(valueChanged(double)), SLOT(dspinValueChanged(double)) );
            editorWidget = editorDSpin;
            break;
        case String:
            editorLE = new QLineEdit(listItems);
            editorLE->setText( value.toString() );
            connect( editorLE, SIGNAL(textChanged(QString)), SLOT(textValueChanged(QString)) );
            editorWidget = editorLE;
            break;
        default:
            break;
    }

    QWidget* container = new QWidget( listItems );
    container->setContentsMargins( 0, 0, 0, 0 );
    QHBoxLayout* containerLayout = new QHBoxLayout( container );
    containerLayout->setMargin( 0 );
    containerLayout->setSpacing( 0 );

    QToolButton* removeButton = new QToolButton( listItems );
    removeButton->setIcon( KIcon( "list-remove" ) );
    connect( removeButton, SIGNAL(clicked(bool)), SLOT(removeClicked()) );
    containerLayout->addWidget( removeButton );

    containerLayout->addWidget( editorWidget );

    listItems->layout()->addWidget( container );
    editorItems.insert( removeButton, editorWidget );
    values.insert( editorWidget, value );
    itemOrder.append( editorWidget );
    countLabel->setText( i18n( "Item count: %1", values.count() ) );
}

void QVariantListPropertyWidgetItem::removeClicked()
{
    QToolButton* from = qobject_cast<QToolButton*>( sender() );
    if( from )
    {
        listItems->layout()->removeWidget( from->parentWidget() );
        from->parentWidget()->deleteLater();
        QWidget* editWidget = editorItems[from];
        editorItems.remove( from );
        values.remove( editWidget );
        itemOrder.removeOne( editWidget );
        countLabel->setText( i18n( "Item count: %1" ).arg(0) );
        valueHasChanged();
    }
}

void QVariantListPropertyWidgetItem::spinValueChanged( int newValue )
{
    QSpinBox* from = qobject_cast< QSpinBox* >( sender() );
    if( from )
    {
        values[from] = newValue;
        valueHasChanged();
    }
}

void QVariantListPropertyWidgetItem::dspinValueChanged( double newValue )
{
    QDoubleSpinBox* from = qobject_cast< QDoubleSpinBox* >( sender() );
    if( from )
    {
        values[from] = newValue;
        valueHasChanged();
    }
}

void QVariantListPropertyWidgetItem::textValueChanged(QString newValue)
{
    QLineEdit* from = qobject_cast< QLineEdit* >( sender() );
    if( from )
    {
        values[from] = newValue;
        valueHasChanged();
    }
}

void QVariantListPropertyWidgetItem::setEditValue(const QVariant& value)
{
    QGridLayout* layout = qobject_cast<QGridLayout*>( editWidget()->layout() );

    // Clear out any old data...
    editorItems.clear();
    values.clear();
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
    QVariantList items = value.toList();

    if( items.count() > 0 )
    {
        for( int i = 0; i < items.count(); ++i )
        {
            addItem( items[i] );
        }
    }

    GluonCreator::PropertyWidgetItem::setEditValue(value);
}

void QVariantListPropertyWidgetItem::valueHasChanged()
{
    QVariantList theValues;
    foreach( QWidget * item, itemOrder )
    {
        theValues.append( values[item] );
    }
    PropertyWidgetItem::valueChanged( theValues );
}
