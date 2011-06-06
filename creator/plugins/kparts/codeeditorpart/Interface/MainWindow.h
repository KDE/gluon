/* This file is part of Rocs,
     Copyright (C) 2008 by:
     Tomaz Canabrava <tomaz.canabrava@gmail.com>
     Ugo Sangiori <ugorox@gmail.com>
     Laszlo Papp <lpapp@kde.org>

     Rocs is free software; you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation; either version 2 of the License, or
     (at your option) any later version.

     Rocs is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.   See the
     GNU General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with Step; if not, write to the Free Software
     Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef SUI_MAINWINDOW_H
#define SUI_MAINWINDOW_H

#include "lib/historymanager.h"

#include <engine/gameobject.h>
#include <engine/component.h>
#include <engine/game.h>
#include <engine/gameproject.h>
#include <engine/scene.h>

#include <KDE/KMessageBox>
#include <KDE/KToolBar>
#include <KDE/KComboBox>

#include <QtGui/QAction>
#include <QtGui/QVBoxLayout>
#include <QtGui/QUndoCommand>
#include <QtCore/QTextStream>

class KPushButton;
class GraphVisualEditor;
class KActionCollection;
class GraphDocument;
class Graph;
class GraphScene;
class KAction;
class MoveNodeAction;
class TabWidget;
class CodeEditor;

#include <QtCore/QWaitCondition>

class MainWindow : public QWidget
{
        Q_OBJECT
        /**
         * \brief Main interface for code editor.
         * Creates Graph to put Nodes on and Buttons to change interaction mode.
         */
    public:
        MainWindow();

        /**
         * Gets graph currently in use.
         * @return    Graph currently in use.
         */
        Graph* graph() const;
        /**
         * Gets scene currently being displayed.
         * @return    Scene being displayed.
         */
        GraphScene* scene() const;
        void debug( const QString& s );
        GraphDocument* activeDocument() const;


    private: // Methods
        /**
         * Setup/Create widgets to window.
         */
        void setupWidgets(); // Setup all the widgets.
        /**
         * Setup/Create action buttons for window/graph.
         */
        void setupActions(); // Setup all the actions.
        /**
         * Setup/Create list of object types available to create.
         */
        void setupLists(); //Setup all them lists.
        void startThreadDocument();
        /**
         * Create list of Node type that can be used in Add Node from GDL file.
         * @param    bigList    Combo box Node types can be appended to.
         */
        void addCustomTypes( KComboBox* bigList );
        /**
         * Function to delete a tree of GameObjects.
         * @param    trap    GameObject at the top-most level of objects to be deleted.
         */
        void eatChildren( GluonEngine::GameObject* trap );

    public slots:
        /**
        * Sets graph document to be shown in graph area.
         * @param    d    Document to be set as new active document.
         */
        void setActiveGraphDocument( GraphDocument* d );
        /**
         * Connects specified Graph to Graph area.
         * @param    g    Graph to be set as new Graph.
         */
        void setActiveGraph( Graph* g );
        /**
         * Toggles if combo box with Node types is allowed to be shown.
         */
        void toggleWidgetTypeShown();
        /**
         * Change graph contents based on scene currently open. Opens GDL state if exists.
         */
        void readTheScene();
        /**
         * Save current Graph state in a GDL file.
         */
        void saveStateGDL();
        /**
         * Load previous Graph state from GDL file.
         */
        void loadStateGDL();
        /**
         * Change Graph contents and Nodes when a change has been propagated in Gluon model.(Undo/Redo)
         * @param    cmd    UndoCommand containing model change.
         */
        void updateNodesFromModel( const QUndoCommand* cmd );
        /**
         * Deletes object from scene containing a specific name and parent.
         * @param    objectName    Name of object to remove from scene.
         * @param    objectParent    Parent object name of to be deleted object.
         */
        void deleteThisSceneObject( QString objectName, QString objectParent );
        /**
         * Mark next Node, when updating, as a GameObject.
         */
        void markAsGameObject();
        /**
         * Mark next Node, when updating, as GameComponent.
         */
        void markAsGameComponent();
        /**
         * Export javascript code representation of visual Nodes. Uses scene name for filename.
         * @param    checked    currently unused file check value.
         */
        void exportCode( bool checked );
        /**
         * Translate Nodes in current Graph into a tree of GluonObjects.
         * @return    GluonObject with all Graph Nodes as children.
         */
        GluonCore::GluonObject* surfNodesIntoTree();
        /**
         * Recursively add GluonObjects as children to given object by object name.
         * @param    n    Node to start search with. (must have objectName match a Node name.)
         */
        void traceNodeGen( GluonCore::GluonObject* n );
        /**
         * Recursively write basic javascript representing Nodes starting with given object.
         * @param    o    GluonObject to start searching from.
         * @param    file    Text stream to write javascript to.
         */
        void exportFromThisNode( GluonCore::GluonObject* o, QTextStream* file );
    signals:
        void sendDisappoint();

    private:
        GraphVisualEditor* _graphVisualEditor; //! Area where the graph will be editted.
        KToolBar* _actionButtons;
        KComboBox* _widgetType;
        KPushButton* _exportCode;
        QAction* _widgetTypeBar;
        QVBoxLayout* _layout;
        KActionCollection* ac;
        //KActionCollection *_paletteActions; //! the pallete actions, move, add, etc.
        GraphDocument* _tDocument;
        Graph* _graph;
        bool _idle;
        QString _lastScene;
        bool _skipNextUpdate;
        bool _isGameObject;
        bool _isGameComponent;
        bool _skipSaving;
        QList<QString> _objectTypes;

};

#endif
