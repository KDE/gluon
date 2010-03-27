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

#include "scenedock.h"

#include <QtGui/QTreeView>

#include <core/debughelper.h>
#include <engine/game.h>
#include <engine/gameobject.h>
#include <engine/scene.h>

#include <selectionmanager.h>
#include <models/scenemodel.h>

#include <KAction>
#include <KLocalizedString>
#include <QMenu>

using namespace GluonCreator;

class SceneDock::SceneDockPrivate
{
    public:
        SceneDockPrivate()
        {
            model = 0;
            view = 0;
        }
        SceneModel* model;
        QTreeView* view;
};


SceneDock::SceneDock(const QString& title, QWidget* parent, Qt::WindowFlags flags): Dock(title, parent, flags)
{
    setObjectName("SceneDock");

    d = new SceneDockPrivate;
    d->view = new QTreeView(this);
    d->model = new SceneModel(d->view);
    setWidget(d->view);

    d->model->setRootGameObject(GluonEngine::Game::instance()->currentScene()->sceneContents());
    connect(GluonEngine::Game::instance(), SIGNAL(currentSceneChanged(GluonEngine::Scene*)), SLOT(sceneChanged(GluonEngine::Scene*)));

    d->view->setModel(d->model);
    d->view->setDragEnabled(true);
    d->view->setAcceptDrops(true);
    d->view->setDropIndicatorShown(true);
    d->view->setDragDropMode(QAbstractItemView::DragDrop);
    d->view->setSelectionMode(QAbstractItemView::ExtendedSelection);
    d->view->setContextMenuPolicy(Qt::ActionsContextMenu);
    connect(d->view->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)), SLOT(selectionChanged(QItemSelection, QItemSelection)));

    setupActions();
}

SceneDock::~SceneDock()
{
    delete d;
}

void SceneDock::setupActions()
{
    KAction* deleteAction = new KAction(KIcon("edit-delete"), i18n("Delete Object(s)"), d->view);
    d->view->addAction(deleteAction);
    deleteAction->setShortcut(KShortcut(Qt::Key_Delete), KAction::DefaultShortcut);
    connect(deleteAction, SIGNAL(triggered(bool)), SLOT(deleteSelection()));

    KAction* separator = new KAction(d->view);
    d->view->addAction(separator);
    separator->setSeparator(true);

    KAction* newGameObject = new KAction(KIcon("file-new"), i18n("New GameObject"), d->view);
    d->view->addAction(newGameObject);
    connect(newGameObject, SIGNAL(triggered(bool)), SLOT(newGameObjectAction()));
}

void SceneDock::setSelection(GluonCore::GluonObject* obj)
{
    Q_UNUSED(obj)
}

QAbstractItemView* SceneDock::view()
{
    return d->view;
}

QAbstractItemModel* SceneDock::model()
{
    return d->model;
}


void SceneDock::selectionChanged(QItemSelection selected, QItemSelection deselected)
{
    Q_UNUSED(deselected)
    DEBUG_FUNC_NAME

    SelectionManager::SelectionList selection;
    foreach(const QItemSelectionRange &range, selected)
    {
        foreach(const QModelIndex &index, range.indexes())
        {
            GluonCore::GluonObject* obj = static_cast<GluonCore::GluonObject*>(index.internalPointer());
            selection.append(obj);
        }
    }
    SelectionManager::instance()->setSelection(selection);
}

void SceneDock::sceneChanged(GluonEngine::Scene* obj)
{
    if (obj)
    {
        d->model->setRootGameObject(obj->sceneContents());
        SelectionManager::SelectionList selection;
        selection.append(obj->sceneContents());
        SelectionManager::instance()->setSelection(selection);
    }
}

void SceneDock::deleteSelection()
{
    DEBUG_FUNC_NAME;

    if (d->view->selectionModel()->hasSelection())
    {
        QItemSelection currentSelection = d->view->selectionModel()->selection();
        foreach(const QItemSelectionRange &range, currentSelection)
        {
            DEBUG_TEXT(QString("Removing rows %1 to %2").arg(range.top()).arg(range.bottom() - range.top()));
            d->model->removeRows(range.top(), (range.bottom() - range.top()) + 1, range.parent());
        }
    }
}

void GluonCreator::SceneDock::newGameObjectAction()
{
    DEBUG_FUNC_NAME

    GluonEngine::GameObject * obj = NULL;
    if (d->view->selectionModel()->hasSelection())
    {
        QItemSelection currentSelection = d->view->selectionModel()->selection();
        foreach(const QItemSelectionRange &range, currentSelection)
        {
            DEBUG_TEXT(QString("Adding new child to first GluonObject in selection"));
            obj = qobject_cast<GluonEngine::GameObject*>(static_cast<QObject*>(range.parent().child(range.top(), 0).internalPointer()));
            break;
        }
    }

    // Find the root item and add a new child to that if we've not got something by now
    if (!obj)
    {
        DEBUG_TEXT(QString("No selection with a gameobject in it, so add the new GameObject to the root of the scene"));
        obj = d->model->rootGameObject();
    }

    if (obj)
    {
        GluonEngine::GameObject * newChild = new GluonEngine::GameObject();
        obj->addChild(newChild);
        d->view->reset();
        DEBUG_TEXT(QString("Created the new GameObject: %1").arg(newChild->fullyQualifiedName()));
    }
}
