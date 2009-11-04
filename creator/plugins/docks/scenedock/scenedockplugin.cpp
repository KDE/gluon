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

#include "scenedockplugin.h"
#include "scenemodel.h"

#include <QtGui/QTreeView>

#include <KLocalizedString>
#include <gluon/game.h>
#include <gluoncreator/gluoncreator_macros.h>

using namespace Gluon::Creator;

class Gluon::Creator::SceneDockPlugin::SceneDockPluginPrivate
{
  public:
    SceneDockPluginPrivate() { model = 0; view = 0; }
    SceneModel* model;
    QTreeView* view;
};

Gluon::Creator::SceneDockPlugin::SceneDockPlugin(QWidget* parent, const QList< QVariant >& params)
  : DockPlugin(i18n("Scene Dock"), parent)
{
  Q_UNUSED(params)
  
  d = new SceneDockPluginPrivate;

  d->model = new SceneModel(this);
  d->view = new QTreeView(this);
  d->view->setModel(d->model);
  d->model->setRootGameObject(Game::instance()->currentScene());
  
  setWidget(d->view);
}

Gluon::Creator::SceneDockPlugin::~SceneDockPlugin()
{
  
}

QAbstractItemModel* Gluon::Creator::SceneDockPlugin::model()
{
  return d->model;
}

QItemSelectionModel* Gluon::Creator::SceneDockPlugin::selectionModel()
{
  return d->view->selectionModel();
}

GLUON_CREATOR_DOCKPLUGIN_EXPORT(SceneDockPlugin)
