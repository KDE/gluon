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

#include "gluonobjectpropertywidgetitem.h"
#include "core/debughelper.h"
#include "engine/game.h"
#include "engine/scene.h"
#include "engine/gameobject.h"
#include "engine/gameproject.h"
#include "engine/gluon_engine_metatypes.h"

#include <filemanager.h>

#include <KMessageBox>
#include <KLocalizedString>
#include <KInputDialog>

#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QToolButton>
#include <QPushButton>

namespace GluonCreator
{
    class GluonObjectPWIPrivate
    {
        public:
            GluonObjectPWIPrivate()
            {
                currentValue = 0;
                //browseButton = 0;
            };

            QPushButton* currentValue;
            QToolButton* editButton;
            QString typeName;

            static QList<const GluonCore::GluonObject*> getChildrenOfType( const QString& typeName, const GluonCore::GluonObject* lookHere )
            {
                QList<const GluonCore::GluonObject*> foundChildren;

                if( lookHere )
                {
                    foreach( const QObject * child, lookHere->children() )
                    {
                        if( child->inherits( typeName.toUtf8() ) )
                            foundChildren.append( qobject_cast<const GluonCore::GluonObject*>( child ) );

                        foundChildren.append( getChildrenOfType( typeName, qobject_cast<const GluonCore::GluonObject*>( child ) ) );
                    }
                }

                return foundChildren;
            }
    };
}

using namespace GluonCreator;

GluonObjectPropertyWidgetItem::GluonObjectPropertyWidgetItem( const QString& typeName, QWidget* parent, Qt::WindowFlags f )
    : PropertyWidgetItem( parent, f )
    , d( new GluonObjectPWIPrivate )
{
    d->typeName = typeName;

    QHBoxLayout* base = new QHBoxLayout;
    base->setSpacing( 0 );
    base->setContentsMargins( 0, 0, 0, 0 );

    d->currentValue = new QPushButton( this );
    d->currentValue->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Minimum );
    base->addWidget( d->currentValue );
    connect( d->currentValue, SIGNAL( clicked( bool ) ), SLOT( browseForItems() ) );

    d->editButton = new QToolButton( this );
    d->editButton->setIcon( KIcon( "document-edit" ) );
    d->editButton->setText( i18nc( "Edit/preview currently selected object", "Edit" ) );
    d->editButton->setToolTip( i18n( "Edit/preview currently selected object" ) );
    base->addWidget( d->editButton );
    connect( d->editButton, SIGNAL( clicked( bool ) ), SLOT( openInEditor() ) );

    QWidget* local = new QWidget( parent );
    local->setLayout( base );
    layout()->addWidget( local );
}

GluonObjectPropertyWidgetItem::~GluonObjectPropertyWidgetItem()
{
    delete d;
}

PropertyWidgetItem *
GluonObjectPropertyWidgetItem::instantiate()
{
    return new GluonObjectPropertyWidgetItem( QString() );
}

QStringList
GluonObjectPropertyWidgetItem::supportedDataTypes() const
{
    QStringList supportedTypes;
    return supportedTypes;
}

void
GluonObjectPropertyWidgetItem::setTypeName( const QString& typeName )
{
    d->typeName = typeName;
}

QString
GluonObjectPropertyWidgetItem::typeName() const
{
    return d->typeName;
}

void
GluonObjectPropertyWidgetItem::browseForItems()
{
    QList<const GluonCore::GluonObject*> items = GluonObjectPWIPrivate::getChildrenOfType( d->typeName, GluonEngine::Game::instance()->gameProject() );
    items.append( GluonObjectPWIPrivate::getChildrenOfType( d->typeName, GluonEngine::Game::instance()->currentScene()->sceneContents() ) );

    if( items.count() == 0 )
    {
        KMessageBox::information( this, i18n( "There are no items of the type %1 anywhere in this project. Please add some and try again.", d->typeName ), i18n( "No Items Found" ) );
    }
    else
    {
        QString caption( "" );
        QString label( "" );
        QStringList nameList;
        bool ok = false;

        nameList.append( i18n( "Clear object reference" ) );
        foreach( const GluonCore::GluonObject * item, items )
        nameList.append( item->fullyQualifiedName() );

        QString chosen = KInputDialog::getItem( caption, label, nameList, 0, false, &ok, this );
        if( ok )
        {
            GluonCore::GluonObject* chosenItem = 0;
            foreach( const GluonCore::GluonObject * testItem, items )
            {
                if( testItem->fullyQualifiedName() == chosen )
                {
                    chosenItem = const_cast<GluonCore::GluonObject*>( testItem );
                    break;
                }
            }
            objectValueChanged( chosenItem );
        }
    }
}

void GluonObjectPropertyWidgetItem::openInEditor()
{
    GluonEngine::Asset* theObject = qobject_cast<GluonEngine::Asset*>( GluonCore::GluonObjectFactory::instance()->wrappedObject( editObject()->property( editProperty().toUtf8() ) ) );

    if( theObject )
    {
        FileManager::instance()->openAsset( theObject );
    }
}

void
GluonObjectPropertyWidgetItem::setEditValue( const QVariant& value )
{
    PropertyWidgetItem::setEditValue( value );

    GluonCore::GluonObject* theObject = GluonCore::GluonObjectFactory::instance()->wrappedObject( value );
    if( theObject )
    {
        d->currentValue->setText( theObject->name() );
        d->currentValue->setToolTip( theObject->fullyQualifiedName() );
        //d->currentValue->setDisabled(false);
    }
    else
    {
        d->currentValue->setText( i18n( "(no object selected)" ) );
        //d->currentValue->setDisabled(true);
    }
}

void
GluonObjectPropertyWidgetItem::objectValueChanged( GluonCore::GluonObject* value )
{
    if( value )
    {
        d->currentValue->setText( value->name() );
        //d->currentValue->setDisabled(false);
    }
    else
    {
        d->currentValue->setText( i18n( "(no object selected)" ) );
        //d->currentValue->setDisabled(true);
    }

    QVariant oldValue = editObject()->property( editProperty().toUtf8() );
    QVariant newValue = GluonCore::GluonObjectFactory::instance()->wrapObject( oldValue, value );
    PropertyWidgetItem::valueChanged( newValue );
}
