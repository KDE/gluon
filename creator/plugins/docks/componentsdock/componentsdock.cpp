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

#include "componentsdock.h"

#include <QListWidget>
#include <gluonobjectfactory.h>
#include <gluonobject.h>
#include <component.h>
#include <KDebug>

using namespace Gluon::Creator;

class ComponentsDock::ComponentsDockPrivate
{
    public:
        ComponentsDockPrivate() { view = 0; };

        QListWidget *view;
};

ComponentsDock::ComponentsDock(const QString& title, QWidget* parent, Qt::WindowFlags flags): Dock(title, parent, flags)
{
    setObjectName("ComponentsDock");

    d = new ComponentsDockPrivate();
    d->view = new QListWidget(this);
    d->view->setDragEnabled(true);
    d->view->setDragDropMode(QAbstractItemView::DragOnly);

    QHash<QString, Gluon::GluonObject*> objectTypes = Gluon::GluonObjectFactory::instance()->objectTypes();
    foreach(Gluon::GluonObject* obj, objectTypes)
    {
        if(obj->inherits("Gluon::Component")) d->view->addItem(obj->metaObject()->className());
    }

    setWidget(d->view);
}

ComponentsDock::~ComponentsDock()
{
    delete d;
}

void ComponentsDock::setSelection(Gluon::GluonObject* obj)
{
    Q_UNUSED(obj);
}

QAbstractItemView* ComponentsDock::view()
{
    return d->view;
}

QAbstractItemModel* ComponentsDock::model()
{
    return d->view->model();
}

