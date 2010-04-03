/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "messagedock.h"

#include <QtGui/QTreeView>

using namespace GluonCreator;

class MessageDock::MessageDockPrivate
{
    public:
        MessageDockPrivate()
        {
            view = 0;
        }
        //MessageModel* model;
        QTreeView* view;
};

MessageDock::MessageDock(const QString& title, QWidget* parent, Qt::WindowFlags flags) 
    : Dock(title, parent, flags),
    d(new MessageDockPrivate)
{
    setObjectName("MessageDock");

    //d->model = new MessageModel(this);
    d->view = new QTreeView(this);
    //d->view->setModel(d->model);
    //d->model->setRootGameObject(Game::instance()->currentMessage());

    setWidget(d->view);
}

MessageDock::~MessageDock()
{
    delete d;
}

QAbstractItemModel* MessageDock::model()
{
    //return d->model;
    return 0;
}

QAbstractItemView* MessageDock::view()
{
    return d->view;
}

void MessageDock::setSelection(GluonCore::GluonObject* obj)
{
    Q_UNUSED(obj)
}

