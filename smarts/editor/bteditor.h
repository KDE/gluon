/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2009 Dan Leinir Turthra Jensen <admin@leinir.dk>
 * Copyright (c) 2009 Kim Jung Nissen <jungnissen@gmail.com>
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

#ifndef GLUON_SMARTS_BTEDITOR_H
#define GLUON_SMARTS_BTEDITOR_H

#include <QtGui/QMainWindow>
#include <QMenu>
#include "ui_bteditor.h"
#include "treeselectordialog.h"
#include <kparts/mainwindow.h>

class btNode;
class btNodeTypesModel;
class btBrain;
class btTreeModel;
class btEditorNode;
class TreeSelectorDialog;
class btPropertyWidget;
class btNodeEditWidget;
class NewTreeWizard;

class bteditor : public KParts::MainWindow, private Ui::BtEditor
{
        Q_OBJECT
    public:
        bteditor( QWidget* parent = 0 );
        virtual ~bteditor();
        void setupActions();

        void showBehaviorTree( btTreeModel* showThis );
        void showPropertiesFor( btEditorNode* showFor );

    public Q_SLOTS:
        void createNewBehaviorTree();
        void newBehaviorTreeAdded( btTreeModel* newTree );
        void newBehaviorTreeCreated( QString name );
        void showBehaviorTreeListCicked();
        void setBehaviorTree( int index );
        void replaceBrain();
        void editorSelectionChanged( const QItemSelection& selected, const QItemSelection& deselected );
        void nodeTypeDeleted( int row );
        void updateView( const QModelIndex& one, const QModelIndex& two );

        void showFor( btEditorNode* node );

    private:
        btBrain* m_brain;
        btNodeTypesModel* nodeTypes;
        btTreeModel* m_currentBehaviorTree;
        TreeSelectorDialog* treeSelectDialog;
        btNodeEditWidget* editWidget;
        btPropertyWidget* propertyWidget;
        NewTreeWizard* wizard;
        QMenu*   treeContextMenu;
        QMenu*   btEditorContextMenu;
        QString fileName;

        btPropertyWidget* oldPropertyWidget;

    private slots:
        void on_actionNew_triggered();
        void on_actionNew_Tree_triggered();
        void on_btEditor_customContextMenuRequested( QPoint pos );
        void on_actionSave_triggered();
        void on_availableNodes_customContextMenuRequested( QPoint pos );
        void on_availableNodes_activated( QModelIndex index );
        void menuNewNodeTriggered();
        void menuDeleteNodeTriggered();
        void bteditDeleteNodeTriggered();
        void on_actionEdit_Node_triggered();
        void on_actionSave_As_triggered();
        void on_actionOpen_triggered();
};

#endif // GLUON_SMARTS_BTEDITOR_H
