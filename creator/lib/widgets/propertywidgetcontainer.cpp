/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "propertywidgetcontainer.h"
#include "propertywidgetitem.h"
#include "propertywidgetitemnewcustomproperty.h"
#include "core/gluonobject.h"

#include "selectionmanager.h"
#include "objectmanager.h"
#include "engine/gameobject.h"
#include "engine/component.h"
#include "models/models.h"
#include "models/scenemodel.h"

#include <KIcon>
#include <KLocalizedString>
#include <KMessageBox>
#include <ksqueezedtextlabel.h>

#include <QtGui/QGridLayout>
#include <QtGui/QBoxLayout>
#include <QtGui/QToolButton>
#include <QtGui/QCheckBox>
#include <QtGui/QMenu>
#include <QtCore/QHash>
#include <QtCore/QMetaProperty>
#include <QtCore/QStringBuilder>
#include <QtCore/QTimer>
#include <QtCore/QDebug>

namespace GluonCreator
{
    class PropertyWidgetContainer::PropertyWidgetContainerPrivate
    {
        public:
            PropertyWidgetContainerPrivate( PropertyWidgetContainer* parent )
                : expanded( true )
                , enabled( true )
                , containerWidget( 0 )
                , containerLayout( 0 )
                , expander( 0 )
                , enabler( 0 )
                , menuButton( 0 )
                , newCustomProp( 0 )
            {
                this->parent = parent;
                menu = new QMenu( parent );

                // The widget used for the heading
                QFrame* titleWidget = new QFrame( parent );
                titleWidget->setFrameShape( QFrame::StyledPanel );
                titleWidget->setFrameShadow( QFrame::Raised );
                parent->layout()->addWidget( titleWidget );

                QHBoxLayout* titleLayout = new QHBoxLayout();
                titleLayout->setSpacing( 0 );
                titleLayout->setContentsMargins( 0, 0, 0, 0 );
                titleWidget->setLayout( titleLayout );

                expander = new QToolButton( titleWidget );
                expander->setAutoRaise( true );
                expander->setArrowType( Qt::DownArrow );
                connect( expander, SIGNAL( clicked( bool ) ), parent, SLOT( toggleExpanded() ) );
                titleLayout->addWidget( expander );

                enabler = new QCheckBox( titleWidget );
                enabler->setText( title );
                enabler->setChecked( enabled );
                connect( enabler, SIGNAL( toggled( bool ) ), parent, SLOT( setEnabled( bool ) ) );
                titleLayout->addWidget( enabler );

                menuButton = new QToolButton( titleWidget );
                menuButton->setIcon( KIcon( "preferences-other" ) );
                menuButton->setAutoRaise( true );
                menuButton->setPopupMode( QToolButton::InstantPopup );
                menuButton->setMenu( menu );
                titleLayout->addWidget( menuButton );

                // The widget used for containing the children
                containerWidget = new QWidget( parent );
                containerLayout = new QGridLayout();
                containerLayout->setSpacing( 0 );
                containerLayout->setContentsMargins( 2, 0, 0, 0 );
                containerWidget->setLayout( containerLayout );
                containerLayout->setColumnStretch( 0, 1 );
                containerLayout->setColumnStretch( 1, 3 );
                parent->layout()->addWidget( containerWidget );
            }
            ~PropertyWidgetContainerPrivate()
            {
            }

            /**
             * Sanitize the name according to the camelCasing
             * - Make first letter upper case
             * - Split at upper-case letters
             * - Add space between those indicated words
             * @par fixThis A string which needs fixing
             * @return The fixified string
             */
            QString humanifyString( QString fixThis );

            PropertyWidgetContainer* parent;
            GluonCore::GluonObject* object;
            void appendMetaObject( QObject* object );
            void addPropertyItem( QString name, PropertyWidgetItem* item );

            bool expanded;
            bool enabled;
            QString title;

            QWidget* containerWidget;
            QGridLayout* containerLayout;
            QHash<QString, QWidget*> items;

            QToolButton* expander;
            QCheckBox* enabler;
            QToolButton* menuButton;

            QMenu* menu;

            GluonCreator::PropertyWidgetItemNewCustomProperty* newCustomProp;
    };
}

using namespace GluonCreator;

PropertyWidgetContainer::PropertyWidgetContainer( GluonCore::GluonObject* theObject, QWidget* parent, Qt::WindowFlags f )
    : QWidget( parent, f )
{
    // Create a base layout to add our two children to...
    QVBoxLayout* layout = new QVBoxLayout( this );
    layout->setSpacing( 0 );
    layout->setContentsMargins( 0, 0, 0, 0 );
    setLayout( layout );

    d = new PropertyWidgetContainerPrivate( this );
    setObject( theObject );
}

PropertyWidgetContainer::~PropertyWidgetContainer()
{
    delete d;
}

void PropertyWidgetContainer::setObject( GluonCore::GluonObject* theObject )
{
    d->object = theObject;

    QString classname( theObject->metaObject()->className() );
    classname = classname.right( classname.length() - classname.lastIndexOf( ':' ) - 1 );
    setTitle( d->humanifyString( classname ) );

    if( !theObject->property( "enabled" ).isNull() )
        setEnabled( theObject->property( "enabled" ).value<bool>() );
    if( !theObject->property( "expanded" ).isNull() )
        setExpanded( theObject->property( "expanded" ).value<bool>() );
    connect( this, SIGNAL( propertyChanged( QObject*, QString, QVariant, QVariant ) ), parentWidget(), SIGNAL( propertyChanged( QObject*, QString, QVariant, QVariant ) ) );

    // Manually add the name and description widgets, as we wish to handle those a little differently
    PropertyWidgetItem* nameWidget = PropertyWidgetItemFactory::instance()->create( theObject, "QString", parentWidget() );
    nameWidget->setEditObject( theObject );
    nameWidget->setEditProperty( "name" );
    d->addPropertyItem( "name", nameWidget );

    PropertyWidgetItem* descriptionWidget = PropertyWidgetItemFactory::instance()->create( theObject, "QString", parentWidget() );
    descriptionWidget->setEditObject( theObject );
    descriptionWidget->setEditProperty( "description" );
    d->addPropertyItem( "description", descriptionWidget );

    QFrame* separator = new QFrame( this );
    separator->setFrameShape( QFrame::HLine );
    d->containerLayout->addWidget( separator, d->containerLayout->rowCount(), 0, 1, 2 );

    // Set up us the menu...
    QAction* customPropAction = new QAction( this );
    customPropAction->setText( i18n( "Add Custom Property..." ) );
    connect( customPropAction, SIGNAL( triggered( bool ) ), this, SLOT( addPropertyTriggered() ) );
    d->menu->addAction( customPropAction );
    d->menu->addSeparator();
    if( classname != QString( "GameObject" ) )
    {
        // Don't show moving up and down stuff for the GameObject
        QAction* upAction = new QAction( this );
        upAction->setText( i18n( "Move Up" ) );
        connect( upAction, SIGNAL( triggered( bool ) ), this, SLOT( upTriggered() ) );
        d->menu->addAction( upAction );
        QAction* downAction = new QAction( this );
        downAction->setText( i18n( "Move Down" ) );
        connect( downAction, SIGNAL( triggered( bool ) ), this, SLOT( downTriggered() ) );
        d->menu->addAction( downAction );
        d->menu->addSeparator();
    }
    if( classname != QString( "GameProject" ) )
    {
        QAction* delAction = new QAction( this );
        delAction->setText( i18n( "Delete" ) );
        connect( delAction, SIGNAL( triggered( bool ) ), this, SLOT( delTriggered() ) );
        d->menu->addAction( delAction );
    }

    d->appendMetaObject( theObject );
}

void
PropertyWidgetContainer::upTriggered()
{

}

void
PropertyWidgetContainer::downTriggered()
{

}

void
PropertyWidgetContainer::delTriggered()
{
    if( KMessageBox::questionYesNo( this, i18n( "Are you sure you wish to delete the item %1?" ).arg( d->object->fullyQualifiedName() ), i18n( "Delete Item?" ) ) == KMessageBox::Yes )
    {
        GluonCore::GluonObject* theParent = qobject_cast<GluonCore::GluonObject*>( d->object->parent() );
        if( theParent )
            theParent->removeChild( d->object );

        SelectionManager::instance()->clearSelection();
        GluonEngine::GameObject* gobj = qobject_cast<GluonEngine::GameObject*>(d->object);
        GluonEngine::Component* comp = qobject_cast<GluonEngine::Component*>(d->object);
        if(gobj && gobj->parentGameObject())
        {
            Models::instance()->sceneModel()->deleteGameObject(gobj);
        }
        else if(comp)
        {
            Models::instance()->sceneModel()->deleteComponent(comp);
            this->deleteLater();
            // Cause the property dock to update its view
//            SelectionManager::SelectionList list;
//            list.append( theParent );
//            SelectionManager::instance()->setSelection( list );
        }
    }
}

void PropertyWidgetContainer::addPropertyTriggered()
{
    d->newCustomProp = new PropertyWidgetItemNewCustomProperty( this );
    connect( d->newCustomProp, SIGNAL( propertyCreated(GluonCore::GluonObject*,QString) ), this, SLOT( propertyCreated(GluonCore::GluonObject*,QString) ) );
    d->newCustomProp->createProperty( d->object );
}

void PropertyWidgetContainer::propertyCreated(GluonCore::GluonObject* propertyCreatedOn, QString createdPropertyName)
{
    QVariant propVal = propertyCreatedOn->property(createdPropertyName.toUtf8());
    PropertyWidgetItem* pwi = PropertyWidgetItemFactory::instance()->create( propertyCreatedOn, propVal.typeName(), parentWidget() );
    pwi->setEditObject( propertyCreatedOn );
    pwi->setEditProperty( createdPropertyName );
    d->addPropertyItem( createdPropertyName, pwi );
    d->newCustomProp->deleteLater();
    emit propertyChanged( propertyCreatedOn, createdPropertyName, propVal, propVal );
}

bool
PropertyWidgetContainer::expanded() const
{
    return d->expanded;
}

void
PropertyWidgetContainer::setExpanded( const bool& newExpanded )
{
    bool oldExpanded = d->expanded;
    d->expanded = newExpanded;

    // This is done to avoid polluting the GDL with unneeded data - the invalid QVariant removes the expanded property, because true is the default value
    if( !newExpanded )
        d->object->setProperty( "expanded", false );
    else
        d->object->setProperty( "expanded", QVariant() );

    if( newExpanded )
    {
        d->expander->setArrowType( Qt::DownArrow );
    }
    else
    {
        d->expander->setArrowType( Qt::RightArrow );
    }
    // This should be animated - need to experiment with the animation framework for that to be pretty ;)
    d->containerWidget->setVisible( newExpanded );

    emit propertyChanged( d->object, "expanded", oldExpanded, newExpanded );
}

void
PropertyWidgetContainer::toggleExpanded()
{
    setExpanded( !expanded() );
}

bool
PropertyWidgetContainer::enabled() const
{
    return d->enabled;
}

void
PropertyWidgetContainer::setEnabled( const bool& newEnabled )
{
    bool oldEnabled = d->enabled;
    d->enabled = newEnabled;
    if( d->enabled != d->object->property( "enabled" ).value<bool>() )
        d->object->setProperty( "enabled", newEnabled );
    if( d->enabler->isChecked() != newEnabled )
        d->enabler->setChecked( newEnabled );
    emit propertyChanged( d->object, "expanded", oldEnabled, newEnabled );
}

QString
PropertyWidgetContainer::title() const
{
    return d->title;
}

void
PropertyWidgetContainer::setTitle( const QString& newTitle )
{
    d->title = newTitle;
    d->enabler->setText( newTitle );
}

void
PropertyWidgetContainer::addDefaultMenuItems()
{
}

void
PropertyWidgetContainer::addMenuItem( QAction* menuItem )
{
    d->menu->addAction( menuItem );
}

void
PropertyWidgetContainer::removeMenuItem( QAction* menuItem )
{
    if( d->menu->actions().contains( menuItem ) )
        d->menu->removeAction( menuItem );
}

void
PropertyWidgetContainer::PropertyWidgetContainerPrivate::appendMetaObject( QObject* object )
{
    QString propertyName, propertyDescription;
    QVariant propertyValue;

    const QMetaObject* metaObject = object->metaObject();
    QMetaProperty metaProperty;

    int count = metaObject->propertyCount();
    for( int i = 0; i < count; ++i )
    {
        metaProperty = metaObject->property( i );

        // Guard against adding these, as we manually add them above, to ensure that they
        // are right at the top and have a little line under them and such... all pretty ;)
        // Also disregard enabled, as that is done by the checkbox above...
        propertyName = QString( metaProperty.name() );
        if( propertyName == QString( "objectName" ) || propertyName == QString( "name" ) || propertyName == QString( "description" ) || propertyName == QString( "expanded" ) || propertyName == QString( "enabled" ) )
            continue;

        PropertyWidgetItem* editWidget;
        if(!metaProperty.isEnumType())
        {
            editWidget = PropertyWidgetItemFactory::instance()->create( object, metaProperty.typeName(), parent->parentWidget() );
        }
        else
        {
            QMetaEnum enumerator = metaProperty.enumerator();
            if( strcmp(enumerator.scope(), "Qt") )
                editWidget = PropertyWidgetItemFactory::instance()->create( object, metaProperty.typeName(), parent->parentWidget() );
            else
                editWidget = PropertyWidgetItemFactory::instance()->create( object, enumerator.name(), parent->parentWidget() );
        }

        editWidget->setEditObject( object );
        editWidget->setEditProperty( metaProperty.name() );

        addPropertyItem( metaProperty.name(), editWidget );
    }

    foreach( const QByteArray & propName, object->dynamicPropertyNames() )
    {
        QString thePropName( propName );
        // Don't show the expanded dynamic property - we make this one dynamic because
        // we don't want to pollute the API with this arguably very meta information
        if( thePropName == QString( "description" ) || thePropName == QString( "expanded" ) || thePropName == QString( "enabled" ) )
            continue;

        PropertyWidgetItem* editWidget = PropertyWidgetItemFactory::instance()->create( object, object->property( propName ).typeName(), parent->parentWidget() );
        editWidget->setEditObject( object );
        editWidget->setEditProperty( thePropName );

        addPropertyItem( thePropName, editWidget );
    }
}

void
PropertyWidgetContainer::PropertyWidgetContainerPrivate::addPropertyItem( QString name, PropertyWidgetItem* item )
{

    KSqueezedTextLabel* nameLabel = new KSqueezedTextLabel( parent );
    nameLabel->setAlignment( Qt::AlignLeft | Qt::AlignTop );
    nameLabel->setTextElideMode( Qt::ElideRight );
    nameLabel->setText( humanifyString( name ) );
    nameLabel->setToolTip( nameLabel->fullText() );

    item->setMinimumWidth( 150 );
    item->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Fixed );
    // Yeah, looks a bit funny, but this makes it possible to connect to either the pwi container... or the pwi view ;)
    connect( item, SIGNAL( propertyChanged( QObject*, QString, QVariant, QVariant ) ), parent, SIGNAL( propertyChanged( QObject*, QString, QVariant, QVariant ) ) );

    int row = containerLayout->rowCount();
    containerLayout->addWidget( nameLabel, row, 0 );
    containerLayout->addWidget( item, row, 1 );

    items.insert( name, item );
}

QString
PropertyWidgetContainer::PropertyWidgetContainerPrivate::humanifyString( QString fixThis )
{
    QString fixedString;
    const int length = fixThis.size();
    for( int i = 0; i < length; ++i )
    {
        const QChar current = fixThis.at( i );
        if( i == 0 )
        {
            // Always upper-case the first word, whether it is or not...
            fixedString = current.toUpper();
        }
        else
        {
            if( current.isUpper() )
            {
                fixedString = fixedString % ' ' % current;
            }
            else
            {
                fixedString = fixedString % current;
            }
        }
    }
    return fixedString;
}
