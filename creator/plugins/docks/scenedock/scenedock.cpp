/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2011 Laszlo Papp <djszapi@archlinux.us>
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

#include "scenedock.h"

#include <historymanager.h>
#include <objectmanager.h>
#include <models/models.h>

#include <core/debughelper.h>
#include <engine/game.h>
#include <engine/gameobject.h>
#include <engine/scene.h>

#include <selectionmanager.h>
#include <models/scenemodel.h>

#include <KAction>
#include <KLocalizedString>

#include <QtGui/QMenu>
#include <QtGui/QTreeView>
#include <KToolBar>
#include <QVBoxLayout>

using namespace GluonCreator;

class SceneDock::SceneDockPrivate
{
    public:
        SceneDockPrivate()
            : model( 0 )
            , view( 0 )
        {
        }

        SceneModel* model;
        QTreeView* view;
};


SceneDock::SceneDock( const QString& title, QWidget* parent, Qt::WindowFlags flags )
    : QDockWidget( title, parent, flags )
    , d( new SceneDockPrivate )
{
    setObjectName( "SceneDock" );

    d->view = new QTreeView( this );
    d->model = Models::instance()->sceneModel();

    if( GluonEngine::Game::instance()->currentScene() )
        d->model->setRootGameObject( GluonEngine::Game::instance()->currentScene()->sceneContents() );

    connect( GluonEngine::Game::instance(), SIGNAL( currentSceneChanged( GluonEngine::Scene* ) ), SLOT( sceneChanged( GluonEngine::Scene* ) ) );
    connect( GluonEngine::Game::instance(), SIGNAL( updated( int ) ), d->model, SIGNAL( layoutChanged() ) );

    d->view->setModel( d->model );
    d->view->setHeaderHidden( true );
    d->view->setDragEnabled( true );
    d->view->setAcceptDrops( true );
    d->view->setDropIndicatorShown( true );
    d->view->setDragDropMode( QAbstractItemView::DragDrop );
    d->view->setSelectionMode( QAbstractItemView::ExtendedSelection );
    d->view->setContextMenuPolicy( Qt::ActionsContextMenu );
    connect( d->view->selectionModel(), SIGNAL( selectionChanged( QItemSelection, QItemSelection ) ), SLOT( selectionChanged( QItemSelection, QItemSelection ) ) );

    QWidget* widget = new QWidget( this );
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setContentsMargins( 0, 0, 0, 0 );
    layout->setSpacing( 0 );
    widget->setLayout( layout );

    KToolBar* toolBar = new KToolBar(this);
    toolBar->setIconDimensions(16);

    QAction* newGameObject = toolBar->addAction(KIcon("document-new"), i18n("New Game Object"), this, SLOT( newGameObjectAction() ) );
    d->view->addAction( newGameObject );

    KAction* separator = new KAction( d->view );
    separator->setSeparator( true );
    d->view->addAction( separator );

    QAction* deleteAction = toolBar->addAction( KIcon( "edit-delete" ), i18n( "Delete" ), this, SLOT( deleteSelection() ) );
    d->view->addAction( deleteAction );

    layout->addWidget(toolBar);
    layout->addWidget(d->view);
    setWidget(widget);
}

SceneDock::~SceneDock()
{
    delete d;
}

void SceneDock::selectionChanged( QItemSelection selected, QItemSelection deselected )
{
    Q_UNUSED( deselected )
    DEBUG_FUNC_NAME

    SelectionManager::SelectionList selection;
    foreach( const QItemSelectionRange & range, selected )
    {
        foreach( const QModelIndex & index, range.indexes() )
        {
            GluonCore::GluonObject* obj = static_cast<GluonCore::GluonObject*>( index.internalPointer() );
            selection.append( obj );
        }
    }
    SelectionManager::instance()->setSelection( selection );
}

void SceneDock::sceneChanged( GluonEngine::Scene* obj )
{
    if( obj )
    {
        d->model->setRootGameObject( obj->sceneContents() );
        SelectionManager::instance()->clearSelection();
        d->view->expandAll();
    }
}

void SceneDock::deleteSelection()
{
    if( d->view->selectionModel()->hasSelection() )
    {
        foreach( const QItemSelectionRange & range, d->view->selectionModel()->selection() )
        {
            foreach( const QModelIndex & index, range.indexes() )
            {
                GluonEngine::GameObject* obj = static_cast<GluonEngine::GameObject*>( index.internalPointer() );
                if( obj && obj->parentGameObject() )
                {
                    ObjectManager::instance()->deleteGameObject( obj );
                }
            }

            d->view->reset();
            SelectionManager::instance()->setSelection( SelectionManager::SelectionList() );
        }
    }
}

void GluonCreator::SceneDock::newGameObjectAction()
{
    GluonEngine::GameObject* newChild = ObjectManager::instance()->createNewGameObject();
    if( newChild )
        d->view->reset();
}
