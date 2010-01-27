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

#include "scenedock.h"
#include "models/scenemodel.h"
#include "selectionmanager.h"
#include "debughelper.h"

#include <QtGui/QTreeView>

#include <game.h>
#include <gameobject.h>
#include <scene.h>

using namespace Gluon;
using namespace Gluon::Creator;

class SceneDock::SceneDockPrivate
{
    public:
        SceneDockPrivate() { model = 0; view = 0; }
        SceneModel* model;
        QTreeView* view;
};


SceneDock::SceneDock(const QString& title, QWidget* parent, Qt::WindowFlags flags): Dock(title, parent, flags)
{
    setObjectName("SceneDock");

    d = new SceneDockPrivate;
    d->view = new QTreeView(this);
    d->model = new SceneModel(d->view);
    setWidget(d->view);
    
    d->model->setRootGameObject(Game::instance()->currentScene()->sceneContents());
    connect(Game::instance(), SIGNAL(currentSceneChanged(Scene*)), SLOT(sceneChanged(Scene*)));

    d->view->setModel(d->model);
    d->view->setDragEnabled(true);
    d->view->setAcceptDrops(true);
    d->view->setDropIndicatorShown(true);
    d->view->setDragDropMode(QAbstractItemView::DragDrop);
    d->view->setSelectionMode(QAbstractItemView::ExtendedSelection);
    connect(d->view, SIGNAL(activated(QModelIndex)), SLOT(selectionChanged(QModelIndex)));
}

SceneDock::~SceneDock()
{
    delete d;
}

void SceneDock::setSelection(GluonObject* obj)
{
    Q_UNUSED(obj)
}

QAbstractItemView* SceneDock::view()
{
    return d->view;
}

QAbstractItemModel* SceneDock::model()
{
    return d->model;
}

void SceneDock::selectionChanged(QModelIndex index)
{
    GluonObject* obj = static_cast<GluonObject*>(index.internalPointer());
    if(obj)
    {
        SelectionManager::SelectionList selection;
        selection.append(obj);
        SelectionManager::instance()->setSelection(selection);
    }
}

void Gluon::Creator::SceneDock::sceneChanged(Scene* obj)
{
    if(obj)
    {
        d->model->setRootGameObject(obj->sceneContents());
        SelectionManager::SelectionList selection;
        selection.append(obj->sceneContents());
        SelectionManager::instance()->setSelection(selection);
    }
}
