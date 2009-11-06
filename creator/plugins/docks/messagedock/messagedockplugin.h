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

#ifndef GLUON_CREATOR_SCENEDOCKPLUGIN_H
#define GLUON_CREATOR_SCENEDOCKPLUGIN_H

#include <gluon/creator/dockplugin.h>

namespace Gluon {

namespace Creator {

class MessageDockPlugin : public Gluon::Creator::DockPlugin
{
  public:
    MessageDockPlugin(QWidget* parent, const QList<QVariant>& params);
    ~MessageDockPlugin();

    QAbstractItemModel* model();
    QItemSelectionModel* selectionModel();

  private:
    class MessageDockPluginPrivate;
    MessageDockPluginPrivate* d;
};

}

}

#endif // GLUON_CREATOR_SCENEDOCKPLUGIN_H
