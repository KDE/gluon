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

#include "projectdock.h"

#include "core/debughelper.h"
#include "core/gluon_global.h"
#include "engine/game.h"
#include "engine/gameobject.h"
#include "engine/scene.h"
#include "engine/asset.h"
#include "models/projectmodel.h"
#include "engine/gameproject.h"

#include <QtGui/QTreeView>
#include <QtGui/QMenu>

#include <KDebug>
#include <KInputDialog>
#include <KMessageBox>
#include <KLocalizedString>
#include <QFile>
#include <QFileInfo>
#include <KRun>
#include <historymanager.h>
#include <newobjectcommand.h>
#include <QDir>
#include <KStandardDirs>

using namespace GluonCreator;

class ProjectDock::ProjectDockPrivate
{
    public:
        ProjectDockPrivate(ProjectDock * parent)
        {
            q = parent;
            view = 0;
            GluonEngine::Asset* theItem;
            const QHash<QString, GluonCore::GluonObject*> types = GluonCore::GluonObjectFactory::instance()->objectTypes();
            QHash<QString, GluonCore::GluonObject*>::const_iterator i;
            for(i = types.constBegin(); i != types.constEnd(); ++i)
            {
                theItem = qobject_cast<GluonEngine::Asset*>(i.value());
                if(theItem)
                {
                    const QList<GluonEngine::AssetTemplate*> templates = theItem->templates();
                    for(int j = 0; j < templates.length(); ++j)
                        assetTemplates.append(templates[j]);
                }
            }
        }
        ProjectDock * q;
        ProjectModel* model;
        QTreeView* view;

        QModelIndex currentContextIndex;
        QList<QAction*> menuForObject(QModelIndex index);
        QList<QAction*> currentContextMenu;
        QList<GluonEngine::AssetTemplate*> assetTemplates;
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
                
                // Run through all the templates and add an action for each...
                foreach(const GluonEngine::AssetTemplate* item, assetTemplates)
                {
                    action = new QAction(i18n("New %1").arg(item->name), this->q);
                    action->setProperty("newAssetClassname", QString(item->parent()->metaObject()->className()));
                    action->setProperty("newAssetName", item->name);
                    action->setProperty("newAssetPluginname", item->pluginname);
                    action->setProperty("newAssetFilename", item->filename);
                    connect(action, SIGNAL(triggered()), q, SLOT(newAssetTriggered()));
                    menuItems.append(action);
                }
            }
            
            action = new QAction(this->q);
            action->setSeparator(true);
            menuItems.append(action);

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
    d->view->setHeaderHidden(true);
    d->view->setAcceptDrops(true);
    d->view->setContextMenuPolicy(Qt::CustomContextMenu);
    d->view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(d->view, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenuRequested(const QPoint&)));

    d->model->setProject(GluonEngine::Game::instance()->gameProject());
    connect(GluonEngine::Game::instance(), SIGNAL(currentProjectChanged(GluonEngine::GameProject*)), d->model, SLOT(setProject(GluonEngine::GameProject*)));
    connect(d->view, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(activated(QModelIndex)));

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
    DEBUG_FUNC_NAME
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
    GluonEngine::Asset* asset = qobject_cast<GluonEngine::Asset*>(obj);
    // Scene's a special asset, so we check for that first
    if (scene)
    {
        if (GluonEngine::Game::instance()->currentScene() != scene)
        {
            GluonEngine::Game::instance()->setCurrentScene(scene);
            GluonEngine::Game::instance()->initializeAll();
            GluonEngine::Game::instance()->drawAll();
        }
    }
    else if(asset)
    {
        DEBUG_TEXT("Asset")
        QString filename = KUrl(GluonEngine::Game::instance()->gameProject()->filename()).directory(KUrl::AppendTrailingSlash) + asset->file().toLocalFile();
	DEBUG_TEXT2("Filename: %1", filename)
        if(QFile::exists(filename))
        {
	    DEBUG_TEXT("Opening asset")
            KRun* runner = new KRun(filename, this);
            Q_UNUSED(runner);
	    //KRun::run("xdg-open %u", KUrl::List() << filename, parentWidget());
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
    if (d->currentContextIndex.isValid())
    {
        GluonCore::GluonObject * object = static_cast<GluonCore::GluonObject*>(d->currentContextIndex.internalPointer());
        QString theName(KInputDialog::getText(i18n("Enter Name"), i18n("Please enter the name of the new folder in the text box below:"), i18n("New Folder"), 0, this));
        if (!theName.isEmpty())
            new GluonCore::GluonObject(theName, object);
    }
}

void GluonCreator::ProjectDock::newAssetTriggered()
{
    DEBUG_BLOCK
    if (d->currentContextIndex.isValid())
    {
        GluonCore::GluonObject * object = static_cast<GluonCore::GluonObject*>(d->currentContextIndex.internalPointer());
        QAction* menuItem = qobject_cast< QAction* >(QObject::sender());
        if(menuItem)
        {
            GluonCore::GluonObject* newChild = GluonCore::GluonObjectFactory::instance()->instantiateObjectByName(menuItem->property("newAssetClassname").toString());
            GluonEngine::Asset* newAsset = qobject_cast< GluonEngine::Asset* >(newChild);
            if(newAsset)
            {
                newAsset->setName(menuItem->property("newAssetName").toString());
                object->addChild(newAsset);

                QString templateFilename = QString("gluon/templates/%1/%2").arg(menuItem->property("newAssetPluginname").toString()).arg(menuItem->property("newAssetFilename").toString());
                QString fileName = GluonCore::Global::dataDirectory() + '/' + templateFilename;
                if(fileName.isEmpty())
                {
                    DEBUG_TEXT("Failed at finding the template file!");
                    return;
                }

                if (!QDir::current().exists("Assets"))
                    QDir::current().mkdir("Assets");

                QFileInfo info(fileName);
                QUrl newLocation(QString("Assets/%1.%2").arg(newAsset->fullyQualifiedFileName()).arg(info.completeSuffix()));
                QFile(fileName).copy(newLocation.toLocalFile());

                newAsset->setFile(newLocation);
                newAsset->load();

                //HistoryManager::instance()->addCommand(new NewObjectCommand(newAsset));
            }
        }
    }
}
