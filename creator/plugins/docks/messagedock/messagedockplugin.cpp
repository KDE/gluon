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

#include "messagedockplugin.h"

#include <QtGui/QTreeView>

#include <KLocalizedString>
#include <gluon/game.h>
#include <gluon/creator/gluoncreator_macros.h>
#include <KDebug>

using namespace Gluon::Creator;

class Gluon::Creator::MessageDockPlugin::MessageDockPluginPrivate
{
  public:
    MessageDockPluginPrivate() { view = 0; }
    //MessageModel* model;
    QTreeView* view;
};

Gluon::Creator::MessageDockPlugin::MessageDockPlugin(QWidget* parent, const QList< QVariant >& params)
  : DockPlugin(i18n("Message Dock"), parent)
{
  Q_UNUSED(params)

  setObjectName("MessageDock");
  
  d = new MessageDockPluginPrivate;

  //d->model = new MessageModel(this);
  d->view = new QTreeView(this);
  //d->view->setModel(d->model);
  //d->model->setRootGameObject(Game::instance()->currentMessage());
  
  setWidget(d->view);
}

Gluon::Creator::MessageDockPlugin::~MessageDockPlugin()
{
  
}

QAbstractItemModel* Gluon::Creator::MessageDockPlugin::model()
{
  //return d->model;
}

QItemSelectionModel* Gluon::Creator::MessageDockPlugin::selectionModel()
{
  //return d->view->selectionModel();
}

GLUON_CREATOR_DOCKPLUGIN_EXPORT(MessageDockPlugin)
