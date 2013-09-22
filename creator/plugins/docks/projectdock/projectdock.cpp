/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2011 Laszlo Papp <lpapp@kde.org>
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

#include <creator/lib/filemanager.h>
#include <creator/lib/historymanager.h>
#include <creator/lib/newobjectcommand.h>
#include <creator/lib/objectmanager.h>
#include <creator/lib/models/projectmodel.h>
#include <creator/lib/models/models.h>
#include <creator/lib/models/modeltest.h>
#include <creator/lib/selectionmanager.h>

#include <engine/game.h>
#include <engine/gameobject.h>
#include <engine/gameproject.h>
#include <engine/scene.h>
#include <engine/asset.h>

#include <core/debughelper.h>
#include <core/directoryprovider.h>

#include <KDE/KIcon>
#include <KDE/KLocalizedString>
#include <KDE/KMessageBox>
#include <KDE/KToolBar>
#include <KDE/KFileItemListProperties>
#include <KDE/KFileItemActions>
#include <KDE/KFileDialog>

#include <QtCore/QMetaClassInfo>
#include <QtGui/QMenu>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QToolButton>
#include <QtGui/QItemSelection>

using namespace GluonCreator;

class ProjectDock::ProjectDockPrivate
{
    public:
        ProjectDockPrivate( ProjectDock* parent )
        {
            DEBUG_BLOCK
            q = parent;
            view = 0;
            GluonEngine::Asset* theItem;
            const QHash<QString, const QMetaObject*> types = GluonCore::GluonObjectFactory::instance()->objectTypes();
            QHash<QString, const QMetaObject*>::const_iterator i;
            for( i = types.constBegin(); i != types.constEnd(); ++i )
            {
                theItem = qobject_cast<GluonEngine::Asset*>( i.value()->newInstance() );
                if( theItem )
                {
                    QString category = theItem->metaObject()->classInfo( theItem->metaObject()->indexOfClassInfo( "org.gluon.category" ) ).value();
                    if( category.isEmpty() )
                        category = i18nc( "Asset without a category", "Uncategorised" );

                    const QList<GluonEngine::AssetTemplate*> templates = theItem->templates();
                    for( int j = 0; j < templates.length(); ++j )
                    {
                        assetTemplates.insert( category, templates[j] );
                        assetIcons.insert( templates[j], theItem->metaObject()->classInfo( theItem->metaObject()->indexOfClassInfo( "org.gluon.icon" ) ).value() );
                    }
                }
                else
                {
                    QObject* obj = i.value()->newInstance();
                    if( obj )
                    {
                        if( obj->inherits( "GluonEngine::Asset" ) )
                        {
                            DEBUG_TEXT2( "The Asset class %1 is lacking the Q_INTERFACES(GluonEngine::Asset) macro", i.value()->className() )
                        }
                    }
                }
            }
        }
        ProjectDock* q;
        ProjectModel* model;
        QTreeView* view;
        KToolBar* toolBar;
        QMenu* newMenu;

        QModelIndex currentContextIndex;
        void menuForObject( QModelIndex index, QMenu* menu );
        QList< QAction* > currentContextMenu;
        QMultiHash< QString, GluonEngine::AssetTemplate* > assetTemplates;
        QHash< GluonEngine::AssetTemplate*, QString > assetIcons;
};

void ProjectDock::ProjectDockPrivate::menuForObject( QModelIndex index, QMenu* menu )
{
    GluonCore::GluonObject* object = static_cast<GluonCore::GluonObject*>( index.internalPointer() );
    if( object )
    {
        const QMetaObject* mobj = object->metaObject();
        if( mobj )
        {
            currentContextIndex = index;
            QAction* action;
            if( object->inherits( "GluonEngine::Asset" ) )
            {
                GluonEngine::Asset* asset = qobject_cast< GluonEngine::Asset* >( object );
                if( asset )
                {
                    if( !asset->inherits( "GluonEngine::Scene" ) )
                    {
                        KFileItem item( KFileItem::Unknown, KFileItem::Unknown, KUrl( asset->absolutePath() ) );
                        KFileItemListProperties properties( KFileItemList() << item );
                        KFileItemActions* openWithActions = new KFileItemActions( menu );
                        openWithActions->setItemListProperties( properties );

                        openWithActions->addOpenWithActionsTo( menu, QString() );
                    }

                    menu->addSeparator();

                    QList<QAction*> actions = asset->actions();
                    foreach( QAction * action, actions )
                    {
                        connect( action, SIGNAL(triggered(bool)), model, SIGNAL(layoutChanged()) );
                        menu->addAction( action );
                    }
                }
            }
            else
            {
                menu->addActions( newMenu->actions() );
            }

            if( !object->inherits( "GluonEngine::GameProject" ) )
            {
                menu->addSeparator();

                action = new QAction( KIcon( "edit-delete" ), i18n( "Delete \"%1\"...", object->name() ), q );
                connect( action, SIGNAL(triggered()), q, SLOT(deleteActionTriggered()) );
                menu->addAction( action );
            }
        }
    }
}



ProjectDock::ProjectDock( const QString& title, QWidget* parent, Qt::WindowFlags flags )
    : QDockWidget( title, parent, flags ), d( new ProjectDockPrivate( this ) )
{
    setObjectName( "ProjectDock" );

    d->model = Models::instance()->projectModel();
    new ModelTest( d->model, this );

    d->view = new QTreeView( this );
    d->view->setModel( d->model );
    d->view->setHeaderHidden( true );
    d->view->setDragEnabled( true );
    d->view->setAcceptDrops( true );
    d->view->setContextMenuPolicy( Qt::CustomContextMenu );
    d->view->setEditTriggers( QAbstractItemView::NoEditTriggers );
    connect( d->view, SIGNAL(customContextMenuRequested(QPoint)), SLOT(showContextMenuRequested(QPoint)) );
    connect( d->view->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), SLOT(selectionChanged(QItemSelection,QItemSelection)) );

    d->model->setProject( GluonEngine::Game::instance()->gameProject() );
    connect( GluonEngine::Game::instance(), SIGNAL(currentProjectChanged(GluonEngine::GameProject*)), SLOT(currentProjectChanged(GluonEngine::GameProject*)) );
    connect( d->view, SIGNAL(doubleClicked(QModelIndex)), SLOT(activated(QModelIndex)) );

    QWidget* widget = new QWidget( this );
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setContentsMargins( 0, 0, 0, 0 );
    layout->setSpacing( 0 );
    widget->setLayout( layout );

    d->toolBar = new KToolBar( widget );
    d->toolBar->setIconDimensions( 16 );

    d->newMenu = new QMenu( i18nc( "Add asset menu", "Add" ), d->toolBar );

    QToolButton* menuButton = new QToolButton( d->toolBar );
    menuButton->setIcon( KIcon( "document-new" ) );
    menuButton->setText( i18nc( "Add asset menu", "Add" ) );
    menuButton->setPopupMode( QToolButton::InstantPopup );
    menuButton->setToolButtonStyle( Qt::ToolButtonTextBesideIcon );
    menuButton->setMenu( d->newMenu );

    d->toolBar->insertWidget( 0, menuButton );

    d->newMenu->addAction( KIcon( "folder" ), i18n( "New Folder" ), this, SLOT(createNewFolder()) );
    d->newMenu->addAction( KIcon( "document-new" ), i18n( "New Scene" ), this, SLOT(createNewScene()) );
    d->newMenu->addSeparator();

    QHash< QString, QMenu* > menus;
    // Run through all the templates and add an action for each...
    QMultiHash< QString, GluonEngine::AssetTemplate* >::const_iterator itr;
    for( itr = d->assetTemplates.begin(); itr != d->assetTemplates.end(); ++itr )
    {
        QMenu* menu;
        if( menus.contains( itr.key() ) )
        {
            menu = menus.value( itr.key() );
        }
        else
        {
            menu = new QMenu( itr.key(), d->newMenu );
            menus.insert( itr.key(), menu );
            d->newMenu->addMenu( menu );
        }

        GluonEngine::AssetTemplate* item = itr.value();
        QAction* action = menu->addAction( i18nc( "Add a new asset", "New %1", item->name ), this, SLOT(createNewAsset()) );
        action->setIcon( KIcon( d->assetIcons.value( item ) ) );
        action->setProperty( "newAssetClassname", item->parent()->metaObject()->className() );
        action->setProperty( "newAssetName", item->name );
        action->setProperty( "newAssetPluginname", item->pluginname );
        action->setProperty( "newAssetFilename", item->filename );
    }

    d->newMenu->addSeparator();
    d->newMenu->addAction( KIcon( "document-import" ), i18n( "Import Assets..." ), this, SLOT(importAssetsTriggered()) );

    d->toolBar->addAction( KIcon( "edit-delete" ), i18nc( "Delete selected object from project", "Delete" ), this, SLOT(deleteActionTriggered()) );

    layout->addWidget( d->toolBar );
    layout->addWidget( d->view );

    setWidget( widget );
}

ProjectDock::~ProjectDock()
{
    delete d;
}

void ProjectDock::activated( QModelIndex index )
{
    if( !index.isValid() )
    {
        return;
    }

    QObject* obj = static_cast<QObject*>( index.internalPointer() );
    if( !obj )
    {
        return;
    }

    GluonEngine::Scene* scene = qobject_cast<GluonEngine::Scene*>( obj );
    GluonEngine::Asset* asset = qobject_cast<GluonEngine::Asset*>( obj );
    // Scene's a special asset, so we check for that first
    if( scene )
    {
        if( GluonEngine::Game::instance()->currentScene() != scene )
        {
            GluonEngine::Game::instance()->setCurrentScene( scene );
            GluonEngine::Game::instance()->initializeAll();
            GluonEngine::Game::instance()->drawAll();
        }
    }
    else if( asset )
    {
        FileManager::instance()->openAsset( asset );
    }
}

void ProjectDock::selectionChanged( const QItemSelection& selected, const QItemSelection& /* deselected */ )
{
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

void ProjectDock::currentProjectChanged( GluonEngine::GameProject* project )
{
    d->model->setProject( project );

    if( !d->toolBar->isEnabled() )
        d->toolBar->setEnabled( true );

    d->view->expandAll();
}

void ProjectDock::showContextMenuRequested( const QPoint& pos )
{
    QModelIndex index = d->view->indexAt( pos );
    if( !index.isValid() )
        index = d->model->index( 0, 0 );

    QMenu menu( static_cast<GluonCore::GluonObject*>( index.internalPointer() )->name(), this );
    d->menuForObject( index, &menu );
    menu.exec( d->view->mapToGlobal( pos ) );
    connect( &menu, SIGNAL(aboutToHide()), SLOT(contextMenuHiding()) );
}

void ProjectDock::contextMenuHiding()
{
    d->currentContextIndex = QModelIndex();
}

void ProjectDock::deleteActionTriggered()
{
    DEBUG_BLOCK
    if( !d->currentContextIndex.isValid() )
        d->currentContextIndex = d->view->selectionModel()->currentIndex();

    if( !d->currentContextIndex.isValid() )
        return;

    GluonCore::GluonObject* object = static_cast<GluonCore::GluonObject*>( d->currentContextIndex.internalPointer() );

    GluonCore::ReferenceCounter* counter = dynamic_cast<GluonCore::ReferenceCounter*>( object );
    if( counter && counter->count() > 0 )
    {
        QString objs = i18ncp( "Appended to the object reference error dialog text", "%1 other object", "%1 other objects", counter->count() );
        KMessageBox::error( this, i18n( "The object %1 is currently referenced by %2. Please remove these references before deleting the object.", object->name(), objs ), i18n( "Object in use" ) );
        return;
    }

    ObjectManager::instance()->deleteObject( object );

    d->view->selectionModel()->select( d->currentContextIndex.parent(), QItemSelectionModel::ClearAndSelect );
    d->model->removeRows( d->currentContextIndex.row(), 1, d->currentContextIndex.parent() );

    d->currentContextIndex = QModelIndex();
}

void ProjectDock::createNewFolder()
{
    if( !d->currentContextIndex.isValid() )
        d->currentContextIndex = d->model->index( 0, 0 );

    GluonCore::GluonObject *newFolder = new GluonCore::GluonObject( i18n( "New Folder" ) );
    QModelIndex newFolderIndex = d->model->addChild( newFolder, d->currentContextIndex );
    d->view->edit( newFolderIndex );

    NewObjectCommand *newObjectCommand = new NewObjectCommand( newFolder );
    HistoryManager::instance()->addCommand( newObjectCommand );
}

void ProjectDock::createNewScene()
{
    if( !d->currentContextIndex.isValid() )
        d->currentContextIndex = d->model->index( 0, 0 );

    GluonEngine::Scene* newScene = new GluonEngine::Scene();
    newScene->setName( i18n( "NewScene" ) );
    newScene->setGameProject( GluonEngine::Game::instance()->gameProject() );
    QModelIndex newSceneIndex = d->model->addChild( newScene, d->currentContextIndex );
    d->view->edit( newSceneIndex );

    NewObjectCommand *newObjectCommand = new NewObjectCommand( newScene );
    HistoryManager::instance()->addCommand( newObjectCommand );
}

void ProjectDock::createNewAsset()
{
    if( !d->currentContextIndex.isValid() )
        d->currentContextIndex = d->model->index( 0, 0 );

    QAction* menuItem = qobject_cast< QAction* >( QObject::sender() );
    if( menuItem )
    {
        QString templateFilename = QString( "gluon/templates/%1/%2" ).arg( menuItem->property( "newAssetPluginname" ).toString() ).arg( menuItem->property( "newAssetFilename" ).toString() );
        QString fileName = GluonCore::DirectoryProvider::instance()->dataDirectory() + '/' + templateFilename;
        if( fileName.isEmpty() )
        {
            DEBUG_BLOCK
            DEBUG_TEXT( "Failed at finding the template file!" )
            return;
        }

        GluonEngine::Asset* newAsset = ObjectManager::instance()->createNewAsset( fileName,
                                                                    static_cast<GluonCore::GluonObject*>( d->currentContextIndex.internalPointer() ),
                                                                    menuItem->property( "newAssetClassname" ).toString(),
                                                                    menuItem->property( "newAssetName" ).toString() );

        if( newAsset )
        {
            d->model->addChild( newAsset, d->currentContextIndex );
            NewObjectCommand *newObjectCommand = new NewObjectCommand( newAsset );
            HistoryManager::instance()->addCommand( newObjectCommand );
        }
    }
}

void ProjectDock::importAssetsTriggered()
{
    ObjectManager::instance()->createAssets( KFileDialog::getOpenFileNames(), static_cast<GluonCore::GluonObject*>( d->currentContextIndex.internalPointer() ) );
}
