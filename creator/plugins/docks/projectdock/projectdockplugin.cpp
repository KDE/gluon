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

#include "projectdockplugin.h"

#include <QtGui/QTreeView>

#include <KLocalizedString>
#include <gluon/game.h>
#include <gluon/creator/gluoncreator_macros.h>
#include <KDebug>

using namespace Gluon::Creator;

class Gluon::Creator::ProjectDockPlugin::ProjectDockPluginPrivate
{
  public:
    ProjectDockPluginPrivate() { view = 0; }
    //ProjectModel* model;
    QTreeView* view;
};

Gluon::Creator::ProjectDockPlugin::ProjectDockPlugin(QWidget* parent, const QList< QVariant >& params)
  : DockPlugin(i18n("Project Dock"), parent)
{
  Q_UNUSED(params)

  setObjectName("ProjectDock");
  
  d = new ProjectDockPluginPrivate;

  //d->model = new ProjectModel(this);
  d->view = new QTreeView(this);
  //d->view->setModel(d->model);
  //d->model->setRootGameObject(Game::instance()->currentProject());
  
  setWidget(d->view);
}

Gluon::Creator::ProjectDockPlugin::~ProjectDockPlugin()
{
  
}

QAbstractItemModel* Gluon::Creator::ProjectDockPlugin::model()
{
  //return d->model;
}

QItemSelectionModel* Gluon::Creator::ProjectDockPlugin::selectionModel()
{
  //return d->view->selectionModel();
}

GLUON_CREATOR_DOCKPLUGIN_EXPORT(ProjectDockPlugin)
