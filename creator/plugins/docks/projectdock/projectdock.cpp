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

#include "projectdock.h"

#include <QtGui/QTreeView>

#include <core/debughelper.h>
#include <engine/game.h>
#include <engine/gameobject.h>
#include <engine/scene.h>

#include <models/projectmodel.h>
#include <KDebug>

using namespace GluonCreator;

class ProjectDock::ProjectDockPrivate
{
  public:
    ProjectDockPrivate() { view = 0; }
    ProjectModel* model;
    QTreeView* view;
};


ProjectDock::ProjectDock(const QString& title, QWidget* parent, Qt::WindowFlags flags): Dock(title, parent, flags)
{
    setObjectName("ProjectDock");

    d = new ProjectDockPrivate;

    d->model = new ProjectModel(this);
    d->view = new QTreeView(this);
    d->view->setModel(d->model);
    d->view->setAcceptDrops(true);

    d->model->setProject(GluonEngine::Game::instance()->gameProject());
    connect(GluonEngine::Game::instance(), SIGNAL(currentProjectChanged(GluonCore::GameProject*)), d->model, SLOT(setProject(GluonCore::GameProject*)));
    connect(d->view, SIGNAL(activated(QModelIndex)), this, SLOT(activated(QModelIndex)));

    setWidget(d->view);
}

ProjectDock::~ProjectDock()
{
    delete d;
}

QAbstractItemModel* ProjectDock::model()
{
    return d->model;
}

QAbstractItemView* ProjectDock::view()
{
    return d->view;
}

void ProjectDock::setSelection(GluonCore::GluonObject* obj)
{
    Q_UNUSED(obj)
}

void ProjectDock::activated(QModelIndex index)
{
    if(!index.isValid())
    {
        return;
    }

    QObject* obj = static_cast<QObject*>(index.internalPointer());
    if(!obj)
    {
        return;
    }

    GluonEngine::Scene* scene = qobject_cast<GluonEngine::Scene*>(obj);
    if(scene)
    {
        if(GluonEngine::Game::instance()->currentScene() != scene)
            GluonEngine::Game::instance()->setCurrentScene(scene);
    }
}
