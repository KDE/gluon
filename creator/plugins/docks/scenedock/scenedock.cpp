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

#include <QtGui/QTreeView>

#include <models/scenemodel.h>
#include <game.h>

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
    d->model = new SceneModel;
    d->model->setRootGameObject(Game::instance()->currentScene());
    connect(Game::instance(), SIGNAL(currentSceneChanged(GameObject*)), d->model, SLOT(setRootGameObject(GameObject*)));

    d->view = new QTreeView;
    d->view->setModel(d->model);
    d->view->setDragEnabled(true);
    d->view->setAcceptDrops(true);
    d->view->setDropIndicatorShown(true);
    d->view->setDragDropMode(QAbstractItemView::InternalMove);

    setWidget(d->view);
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

