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

#include "projectdock.h"

#include "core/debughelper.h"
#include "engine/game.h"
#include "engine/gameobject.h"
#include "engine/scene.h"
#include "models/projectmodel.h"

#include <QtGui/QTreeView>
#include <QtGui/QMenu>

#include <KDebug>
#include <KInputDialog>
#include <KMessageBox>
#include <KLocalizedString>

using namespace GluonCreator;

class ProjectDock::ProjectDockPrivate
{
    public:
        ProjectDockPrivate(ProjectDock * parent)
        {
            q = parent;
            view = 0;
        }
        ProjectDock * q;
        ProjectModel* model;
        QTreeView* view;

        QModelIndex currentContextIndex;
        QList<QAction*> menuForObject(QModelIndex index);
        QList<QAction*> currentContextMenu;
};

QList< QAction* > ProjectDock::ProjectDockPrivate::menuForObject(QModelIndex index)
{
    QList<QAction*> menuItems;

    GluonCore::GluonObject * object = static_cast<GluonCore::GluonObject*>(index.internalPointer());
    if (object)
    {
        const QMetaObject * mobj = object->metaObject();
        if (mobj)
        {
            currentContextIndex = index;
            QAction * action;
            if (object->inherits("GluonEngine::Asset"))
            {
                action = new QAction("Asset actions go here", this->q);
                action->setEnabled(false);
                menuItems.append(action);
            }
            else
            {
                action = new QAction("New Folder...", this->q);
                connect(action, SIGNAL(triggered()), q, SLOT(newSubMenuTriggered()));
                menuItems.append(action);
            }
            action = new QAction(QString("Delete \"%1\"...").arg(object->name()), this->q);
            connect(action, SIGNAL(triggered()), q, SLOT(deleteActionTriggered()));
            menuItems.append(action);
        }
    }
    currentContextMenu = QList<QAction*>(menuItems);

    return menuItems;
}



ProjectDock::ProjectDock(const QString& title, QWidget* parent, Qt::WindowFlags flags): Dock(title, parent, flags)
{
    setObjectName("ProjectDock");

    d = new ProjectDockPrivate(this);

    d->model = new ProjectModel(this);
    d->view = new QTreeView(this);
    d->view->setModel(d->model);
    d->view->setAcceptDrops(true);
    d->view->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(d->view, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenuRequested(const QPoint&)));

    d->model->setProject(GluonEngine::Game::instance()->gameProject());
    connect(GluonEngine::Game::instance(), SIGNAL(currentProjectChanged(GluonEngine::GameProject*)), d->model, SLOT(setProject(GluonEngine::GameProject*)));
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
    if (!index.isValid())
    {
        return;
    }

    QObject* obj = static_cast<QObject*>(index.internalPointer());
    if (!obj)
    {
        return;
    }

    GluonEngine::Scene* scene = qobject_cast<GluonEngine::Scene*>(obj);
    if (scene)
    {
        if (GluonEngine::Game::instance()->currentScene() != scene)
        {
            GluonEngine::Game::instance()->setCurrentScene(scene);
            GluonEngine::Game::instance()->startAll();
            GluonEngine::Game::instance()->drawAll();
        }
    }
}

void ProjectDock::showContextMenuRequested(const QPoint& pos)
{
    QModelIndex index = d->view->indexAt(pos);
    if (index.isValid())
    {
        QMenu menu(static_cast<GluonCore::GluonObject*>(index.internalPointer())->name(), this);
        menu.addActions(d->menuForObject(index));
        menu.exec(d->view->mapToGlobal(pos));
        connect(&menu, SIGNAL(aboutToHide()), this, SLOT(contextMenuHiding()));
    }
}

void ProjectDock::contextMenuHiding()
{
    d->currentContextIndex = QModelIndex();
    qDeleteAll(d->currentContextMenu);
}

void ProjectDock::deleteActionTriggered()
{
    DEBUG_FUNC_NAME
    if (d->currentContextIndex.isValid())
    {
        GluonCore::GluonObject * object = static_cast<GluonCore::GluonObject*>(d->currentContextIndex.internalPointer());
        DEBUG_TEXT(QString("Requested deletion of %1").arg(object->fullyQualifiedName()));
        if (KMessageBox::questionYesNo(this, tr("Please confirm that you wish to delete the object %1. This will delete both this item and all its children!").arg(object->name()), tr("Really Delete?")) == KMessageBox::Yes)
        {
            d->view->selectionModel()->select(d->currentContextIndex.parent(), QItemSelectionModel::ClearAndSelect);
            d->view->collapse(d->currentContextIndex.parent());
            d->model->removeRows(d->currentContextIndex.row(), 1, d->currentContextIndex.parent());
        }
    }
}

void ProjectDock::newSubMenuTriggered()
{
    DEBUG_FUNC_NAME
    if (d->currentContextIndex.isValid())
    {
        GluonCore::GluonObject * object = static_cast<GluonCore::GluonObject*>(d->currentContextIndex.internalPointer());
        DEBUG_TEXT(QString("Requested a new submenu under %1").arg(object->fullyQualifiedName()));
        QString theName(KInputDialog::getText(i18n("Enter Name"), i18n("Please enter the name of the new folder in the text box below:"), i18n("New Folder"), 0, this));
        if (!theName.isEmpty())
            new GluonCore::GluonObject(theName, object);
    }
}

