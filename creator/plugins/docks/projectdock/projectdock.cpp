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

#include <gluon/game.h>

#include <models/projectmodel.h>

using namespace Gluon;
using namespace Gluon::Creator;

class ProjectDock::ProjectDockPrivate
{
  public:
    ProjectDockPrivate() { view = 0; }
    ProjectModel* model;
    QTreeView* view;
};


Gluon::Creator::ProjectDock::ProjectDock(const QString& title, QWidget* parent, Qt::WindowFlags flags): Dock(title, parent, flags)
{
  setObjectName("ProjectDock");
  
  d = new ProjectDockPrivate;

  d->model = new ProjectModel(this);
  d->view = new QTreeView(this);
  d->view->setModel(d->model);

  d->model->setProject(Game::instance()->gameProject());
  connect(Game::instance(), SIGNAL(currentProjectChanged(GameProject*)), d->model, SLOT(setProject(GameProject*)));

  setWidget(d->view);
}

Gluon::Creator::ProjectDock::~ProjectDock()
{
  delete d;
}

QAbstractItemModel* Gluon::Creator::ProjectDock::model()
{
  //return d->model;
  return 0;
}

QAbstractItemView* Gluon::Creator::ProjectDock::view()
{
    return d->view;
}

void Gluon::Creator::ProjectDock::setSelection(GluonObject* obj)
{
    Q_UNUSED(obj)
}
