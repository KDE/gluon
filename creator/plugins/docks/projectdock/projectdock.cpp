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

#include "core/debughelper.h"
#include "engine/game.h"
#include "engine/gameobject.h"
#include "engine/scene.h"
#include "models/projectmodel.h"

#include <QtGui/QTreeView>
#include <QtGui/QMenu>

#include <KDebug>

using namespace GluonCreator;

class ProjectDock::ProjectDockPrivate
{
  public:
    ProjectDockPrivate(ProjectDock * parent) { q = parent; view = 0; }
    ProjectDock * q;
    ProjectModel* model;
    QTreeView* view;
    
    QList<QAction*> menuForObject(GluonCore::GluonObject * object) const;
};

QList< QAction* > ProjectDock::ProjectDockPrivate::menuForObject(GluonCore::GluonObject* object) const
{
    QList<QAction*> menuItems;
    
    if(object)
    {
        const QMetaObject * mobj = object->metaObject();
        if(mobj)
        {
            QAction * action;
            if(object->inherits("GluonEngine::Asset"))
            {
                action = new QAction("Asset actions go here", object);
                action->setEnabled(false);
                menuItems.append(action);
            }
            else
            {
                action = new QAction("New Folder...", object);
                connect(action, SIGNAL(triggered()), q, SLOT(newSubMenuTriggered()));
                menuItems.append(action);
            }
            action = new QAction(QString("Delete \"%1\"...").arg(object->name()), object);
            connect(action, SIGNAL(triggered()), q, SLOT(deleteActionTriggered()));
            menuItems.append(action);
        }
    }
    
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

void ProjectDock::showContextMenuRequested(const QPoint& pos)
{
    QModelIndex index = d->view->indexAt(pos);
    if(index.isValid())
    {
        GluonCore::GluonObject * object = static_cast<GluonCore::GluonObject*>(index.internalPointer());
        if(object)
        {
            QMenu menu(object->name(), this);
            menu.addActions(d->menuForObject(object));
            menu.exec(d->view->mapToGlobal(pos));
        }
    }
}

void ProjectDock::deleteActionTriggered()
{
    DEBUG_FUNC_NAME
    GluonCore::GluonObject * sender = qobject_cast<GluonCore::GluonObject*>(QObject::sender()->parent());
    if(sender)
    {
        DEBUG_TEXT(QString("Requested deletion of %1").arg(sender->fullyQualifiedName()));
    }
}

void ProjectDock::newSubMenuTriggered()
{
    DEBUG_FUNC_NAME
    GluonCore::GluonObject * sender = qobject_cast<GluonCore::GluonObject*>(QObject::sender()->parent());
    if(sender)
    {
        DEBUG_TEXT(QString("Requested a new submenu under %1").arg(sender->fullyQualifiedName()));
    }
}

