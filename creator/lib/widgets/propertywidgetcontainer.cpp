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
#include "core/gluonobject.h"

#include <QtGui/QGridLayout>
#include <QtGui/QBoxLayout>
#include <QtGui/QPushButton>
#include <QtGui/QCheckBox>
#include <QtGui/QLabel>
#include <QtGui/QMenu>
#include <QtCore/QHash>
#include <QtCore/QMetaProperty>

namespace GluonCreator {
class PropertyWidgetContainer::PropertyWidgetContainerPrivate
{
    public:
        PropertyWidgetContainerPrivate(PropertyWidgetContainer* parent)
            : expanded(true)
            , enabled(true)
            , containerWidget(0)
            , containerLayout(0)
            , expander(0)
            , enabler(0)
            , titleLabel(0)
            , menuButton(0)
        {
            this->parent = parent;
            menu = new QMenu(parent);
            
            // The widget used for the heading
            QWidget* titleWidget = new QWidget(parent);
            parent->layout()->addWidget(titleWidget);
            
            QHBoxLayout* titleLayout = new QHBoxLayout();
            titleLayout->setSpacing(0);
            titleLayout->setContentsMargins(0, 0, 0, 0);
            titleWidget->setLayout(titleLayout);
            
            expander = new QPushButton(parent);
            expander->setFlat(true);
            titleLayout->addWidget(expander);
            
            enabler = new QCheckBox(parent);
            titleLayout->addWidget(enabler);
            
            titleLabel = new QLabel(parent);
            titleLabel->setText(title);
            titleLayout->addWidget(titleLabel);
            
            menuButton = new QPushButton(parent);
            menuButton->setFlat(true);
            parent->connect(menuButton, SIGNAL(clicked(bool)), menuButton, SLOT(showMenu()));
            titleLayout->addWidget(menuButton);
            
            // The widget used for containing the children
            containerWidget = new QWidget(parent);
            containerLayout = new QGridLayout();
            containerLayout->setSpacing(0);
            containerLayout->setContentsMargins(0, 0, 0, 0);
            containerWidget->setLayout(containerLayout);
            parent->layout()->addWidget(containerWidget);
        }
        ~PropertyWidgetContainerPrivate()
        {
        };
        
        PropertyWidgetContainer* parent;
        void appendMetaObject(QObject* object);
        void addPropertyItem(QString name, PropertyWidgetItem* item);
        
        bool expanded;
        bool enabled;
        QString title;
        
        QWidget* containerWidget;
        QGridLayout* containerLayout;
        QHash<QString, QWidget*> items;
        
        QPushButton* expander;
        QCheckBox* enabler;
        QLabel* titleLabel;
        QPushButton* menuButton;
        
        QMenu* menu;
}; }

using namespace GluonCreator;

PropertyWidgetContainer::PropertyWidgetContainer(GluonCore::GluonObject* theObject, QWidget* parent, Qt::WindowFlags f)
    : QWidget(parent, f)
{
    // Create a base layout to add our two children to...
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
    
    d = new PropertyWidgetContainerPrivate(this);
    setObject(theObject);
}

PropertyWidgetContainer::~PropertyWidgetContainer()
{
    delete(d);
}

void PropertyWidgetContainer::setObject(GluonCore::GluonObject* theObject)
{
    QString classname(theObject->metaObject()->className());
    classname = classname.right(classname.length() - classname.lastIndexOf(':') - 1);
    setTitle(classname);
    d->appendMetaObject(theObject);
}

bool
PropertyWidgetContainer::expanded() const
{
    return d->expanded;
}

void
PropertyWidgetContainer::setExpanded(const bool& newExpanded)
{
    d->expanded = newExpanded;
    
    // This should be animated - need to experiment with the animation framework for that to be pretty ;)
    d->containerWidget->setVisible(newExpanded);
}

bool
PropertyWidgetContainer::enabled() const
{
    return d->enabled;
}

void
PropertyWidgetContainer::setEnabled(const bool& newEnabled)
{
    d->enabled = newEnabled;
}

QString
PropertyWidgetContainer::title() const
{
    return d->title;
}

void
PropertyWidgetContainer::setTitle(const QString& newTitle)
{
    d->title = newTitle;
    d->titleLabel->setText(newTitle);
}

void
PropertyWidgetContainer::addDefaultMenuItems(QObject* referenceObject)
{
}

void
PropertyWidgetContainer::addMenuItem(QAction* menuItem)
{
    d->menu->addAction(menuItem);
}

void
PropertyWidgetContainer::removeMenuItem(QAction* menuItem)
{
    if(d->menu->actions().contains(menuItem))
        d->menu->removeAction(menuItem);
}

void
PropertyWidgetContainer::PropertyWidgetContainerPrivate::appendMetaObject(QObject* object)
{
    QString propertyName, propertyDescription;
    QVariant propertyValue;
    
    const QMetaObject *metaObject = object->metaObject();
    QMetaProperty metaProperty;
    
    int count = metaObject->propertyCount();
    for (int i = 0; i < count; ++i)
    {
        metaProperty = metaObject->property(i);
        
        // Guard against adding these, as we manually add them above, to ensure that they
        // are right at the top and have a little line under them and such... all pretty ;)
        // Also disregard enabled, as that is done by the checkbox above...
        propertyName = QString(metaProperty.name());
        if (propertyName == QString("objectName"))// || propertyName == QString("name") || propertyName == QString("description") || propertyName == QString("enabled"))
            continue;
        
        PropertyWidgetItem *editWidget = PropertyWidgetItemFactory::instance()->create(object, metaProperty.typeName(), parent->parentWidget());
        editWidget->setEditObject(object);
        editWidget->setEditProperty(metaProperty.name());
        
        addPropertyItem(metaProperty.name(), editWidget);
    }
    
    foreach(const QByteArray &propName, object->dynamicPropertyNames())
    {
        QString thePropName(propName);
        
        PropertyWidgetItem *editWidget = PropertyWidgetItemFactory::instance()->create(object, object->property(propName).typeName(), parent->parentWidget());
        editWidget->setEditObject(object);
        editWidget->setEditProperty(thePropName);
        
        addPropertyItem(metaProperty.name(), editWidget);
    }
}

void
PropertyWidgetContainer::PropertyWidgetContainerPrivate::addPropertyItem(QString name, PropertyWidgetItem* item)
{
    
    QLabel* nameLabel = new QLabel(parent);
    nameLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    // Sanitize the name according to the camelCasing
    // - Make first letter upper case
    // - Split at upper-case letters
    // - Add space between those indicated words
    nameLabel->setText(name);
    
    item->setMinimumWidth(250);
    item->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    connect(item, SIGNAL(propertyChanged(QObject*, QString, QVariant, QVariant)), parent->parent(), SIGNAL(propertyChanged(QObject*, QString, QVariant, QVariant)));
    
    int row = containerLayout->rowCount();
    containerLayout->addWidget(nameLabel, row, 0);
    containerLayout->addWidget(item, row, 1);
    
    items.insert(name, item);
}

#include "propertywidgetcontainer.moc"
