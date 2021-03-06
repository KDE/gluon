/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
 * Copyright (c) 2011 Laszlo Papp <lpapp@kde.org>
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

#include "enumpropertywidgetitem.h"

#include <core/log.h>
#include <core/gluonobjectfactory.h>

#include <KCompletion/KComboBox>

#include <QtWidgets/QLayout>
#include <QtCore/QMetaEnum>

namespace GluonCreator
{
    class EnumPWIPrivate
    {
        public:
            EnumPWIPrivate()
                : comboBox( 0 )
                , editObject( 0 )
            {
            };

            ~EnumPWIPrivate() {};

            KComboBox* comboBox;
            QObject* editObject;
            QString typeName;
            QMetaEnum metaEnum;

            void setupComboBox()
            {
                if( !editObject )
                    return;

                QString str = typeName.section( "::", 0, -2 );
                QString typeStr = typeName.section( "::", -1 );
                const QMetaObject* mo;
                if( str.compare( "Qt" ) && !str.isEmpty() )
                {
                    mo = GluonCore::GluonObjectFactory::instance()->objectTypes().value( str );
                }
                else
                {
                    mo = editObject->metaObject();
                }

                int enumIndex = mo->indexOfEnumerator( typeStr.toUtf8() );
                if( enumIndex > -1 )
                {
                    metaEnum = mo->enumerator( enumIndex );
                }
                else
                {
                    const QMetaObject* qtmo = QtMetaObject::get();
                    int qtEnumIndex = qtmo->indexOfEnumerator( typeName.toUtf8() );

                    if( qtEnumIndex > -1 )
                    {
                        metaEnum = qtmo->enumerator( qtEnumIndex );
                    }
                    else
                    {
                        WARNING() << "The enumerator " << typeName << " was not found! Maybe you forgot to declare it in the class?";
                        metaEnum = QMetaEnum();
                    }
                }

                for( int i = 0; i < metaEnum.keyCount(); ++i )
                {
                    comboBox->addItem( QString( metaEnum.key( i ) ), metaEnum.value( i ) );
                }
            }
    };
}

using namespace GluonCreator;

EnumPropertyWidgetItem::EnumPropertyWidgetItem( const QString& typeName, QWidget* parent, Qt::WindowFlags f )
    : PropertyWidgetItem( parent, f )
{
    d = new EnumPWIPrivate();
    d->typeName = typeName;

    d->comboBox = new KComboBox( this );
    layout()->addWidget( d->comboBox );
}

EnumPropertyWidgetItem::~EnumPropertyWidgetItem()
{
    delete d;
}

PropertyWidgetItem*
EnumPropertyWidgetItem::instantiate()
{
    return new EnumPropertyWidgetItem( QString() );
}

QStringList
EnumPropertyWidgetItem::supportedDataTypes() const
{
    QStringList supportedTypes;
    return supportedTypes;
}

void
EnumPropertyWidgetItem::setEditObject( QObject* editThis )
{
    GluonCreator::PropertyWidgetItem::setEditObject( editThis );
    d->editObject = editThis;
    d->setupComboBox();
    connect( d->comboBox, SIGNAL(currentIndexChanged(int)), SLOT(indexChanged(int)) );
}

void
EnumPropertyWidgetItem::setEditValue( const QVariant& value )
{
    // int key = value.toInt();
    d->comboBox->setCurrentIndex( d->comboBox->findData( value ) );
    GluonCreator::PropertyWidgetItem::setEditValue( value );
}

void
EnumPropertyWidgetItem::indexChanged( int newIndex )
{
    d->editObject->setProperty( editProperty().toUtf8(), d->comboBox->itemData( newIndex ) );
    GluonCreator::PropertyWidgetItem::valueChanged( d->comboBox->itemData( newIndex ) );
}
