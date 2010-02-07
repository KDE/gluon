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

#include "propertiesdock.h"

#include <widgets/propertywidget.h>
#include <engine/game.h>
#include <engine/component.h>
#include <objectmanager.h>

using namespace GluonCreator;

class PropertiesDock::PropertiesDockPrivate
{
    public:
        PropertiesDockPrivate() { }

        PropertyWidget *widget;
};

PropertiesDock::PropertiesDock(const QString& title, QWidget* parent, Qt::WindowFlags flags): Dock(title, parent, flags)
{
    setObjectName("PropertiesDock");

    d = new PropertiesDockPrivate;

    d->widget = new PropertyWidget(this);
    setWidget(d->widget);

    connect(SelectionManager::instance(), SIGNAL(selectionChanged(SelectionManager::SelectionList)), SLOT(selectionChanged(SelectionManager::SelectionList)));
    connect(d->widget, SIGNAL(propertyChanged(QString,QVariant,QVariant)), GluonEngine::Game::instance(), SLOT(updateAll()));
    connect(ObjectManager::instance(), SIGNAL(newComponent(GluonEngine::Component*)), SLOT(newComponent(GluonEngine::Component*)));
}

PropertiesDock::~PropertiesDock()
{
    delete d;
    d = 0;
}

void PropertiesDock::setSelection(GluonCore::GluonObject* obj)
{
    d->widget->setObject(obj);
}

QAbstractItemView* PropertiesDock::view()
{
    return 0;
}

QAbstractItemModel* PropertiesDock::model()
{
    return 0;
}

void PropertiesDock::selectionChanged(SelectionManager::SelectionList selection)
{
    setSelection(selection.at(0));
}

void PropertiesDock::newComponent(GluonEngine::Component* comp)
{
    if(comp->parent() == d->widget->object())
    {
        d->widget->setObject(d->widget->object());
    }
}


