/* This file is part of Rocs,
	 Copyright (C) 2008 by:
	 Tomaz Canabrava <tomaz.canabrava@gmail.com>
	 Ugo Sangiori <ugorox@gmail.com>

	 Rocs is free software; you can redistribute it and/or modify
	 it under the terms of the GNU General Public License as published by
	 the Free Software Foundation; either version 2 of the License, or
	 (at your option) any later version.

	 Rocs is distributed in the hope that it will be useful,
	 but WITHOUT ANY WARRANTY; without even the implied warranty of
	 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
	 GNU General Public License for more details.

	 You should have received a copy of the GNU General Public License
	 along with Step; if not, write to the Free Software
	 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA	02110-1301	USA
*/

#ifndef SUI_MAINWINDOW_H
#define SUI_MAINWINDOW_H

//#include <KXmlGuiWindow>
#include <kmessagebox.h>
#include <KToolBar>
#include <KComboBox>
#include <QtGui/QAction>
#include <QtGui/QVBoxLayout>
#include <QtGui/QUndoCommand>
#include <engine/gameobject.h>
#include <engine/game.h>
#include <engine/gameproject.h>
#include <engine/scene.h>
#include <creator/lib/historymanager.h>

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

class MainWindow : public QWidget {
    Q_OBJECT

public:
    /*! defalt constructor */
    MainWindow();

    Graph *graph() const;
    GraphScene *scene() const;
    void debug(const QString& s);
    GraphDocument *activeDocument() const;
    
    
private: // Methods
    void setupWidgets(); // Setup all the widgets.
    void setupActions(); // Setup all the actions.
    void startThreadDocument();
    void addCustomTypes(KComboBox* bigList);
    void eatChildren(GluonEngine::GameObject *trap);
  
public slots:
    void setActiveGraphDocument(GraphDocument *d);
    void setActiveGraph(Graph *g);
    void toggleWidgetTypeShown();
    void readTheScene();
    void saveStateGDL();
    void loadStateGDL();
    void updateNodesFromModel(const QUndoCommand* cmd);
    void deleteThisSceneObject(QString objectName);
    void markAsGameObject();
    void exportCode(bool checked);
      
private:
    GraphVisualEditor* _graphVisualEditor; //! Area where the graph will be editted.
    KToolBar* _actionButtons;
    KComboBox* _widgetType;
    KPushButton* _exportCode;
    QAction* _widgetTypeBar;
    QVBoxLayout* _layout;
    KActionCollection *ac;
    //KActionCollection *_paletteActions; //! the pallete actions, move, add, etc.
    GraphDocument *_tDocument;
    Graph *_graph;
    bool _idle;
    QString _lastScene;
    bool _skipNextUpdate;
    bool _isGameObject;
};

#endif
