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
#include "models/componentmodel.h"

#include <QtGui/QListWidget>
#include <QtGui/QStringListModel>
#include <KDebug>
#include <core/gluonobjectfactory.h>
#include <core/gluonobject.h>
#include <engine/component.h>

using namespace GluonCreator;

class ComponentsDock::ComponentsDockPrivate
{
    public:
        ComponentsDockPrivate() { view = 0; };

        QListView *view;
        ComponentModel *model;
};

ComponentsDock::ComponentsDock(const QString& title, QWidget* parent, Qt::WindowFlags flags): Dock(title, parent, flags)
{
    setObjectName("ComponentsDock");

    d = new ComponentsDockPrivate();

    d->view = new QListView(this);
    d->view->setSelectionMode(QAbstractItemView::SingleSelection);
    d->view->setDragEnabled(true);
    d->view->setAcceptDrops(false);
    d->view->setDropIndicatorShown(false);

    QHash<QString, GluonCore::GluonObject*> objectTypes = GluonCore::GluonObjectFactory::instance()->objectTypes();
    QStringList list;
    foreach(GluonCore::GluonObject* obj, objectTypes)
    {
        if(obj->inherits("Gluon::Component"))
        {
            list << obj->metaObject()->className();            
        }
    }
    d->model = new ComponentModel(this);
    d->model->setStringList(list);
    d->view->setModel(d->model);

    setWidget(d->view);
}

ComponentsDock::~ComponentsDock()
{
    delete d;
}

void ComponentsDock::setSelection(GluonCore::GluonObject* obj)
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

