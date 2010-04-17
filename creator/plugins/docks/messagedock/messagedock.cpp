/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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
#include <engine/game.h>

// Yup, this should be a view... but for now...
#include <QtGui/QListWidget>
#include <QDebug>

using namespace GluonCreator;

class MessageDock::MessageDockPrivate
{
    public:
        MessageDockPrivate()
        {
            view = 0;
        }
        QListWidget* view;
};

MessageDock::MessageDock(const QString& title, QWidget* parent, Qt::WindowFlags flags) 
    : Dock(title, parent, flags),
    d(new MessageDockPrivate)
{
    setObjectName("MessageDock");
    d->view = new QListWidget(this);
    
    connect(GluonEngine::Game::instance(), SIGNAL(showDebug(const QString&)), this, SLOT(showDebug(const QString&)));
    
    setWidget(d->view);
}

void MessageDock::showDebug(const QString& debugText)
{
    QListWidgetItem* item = new QListWidgetItem(debugText, d->view);
    d->view->addItem(item);
    d->view->scrollToItem(item);
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

#include "messagedock.moc"
