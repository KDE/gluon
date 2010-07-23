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
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.   See the
     GNU General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with Step; if not, write to the Free Software
     Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "MainWindow.h"
//Qt related includes

// KDE Related Includes
#include <KActionCollection>
#include <KIcon>
#include <KDebug>
//#include <KApplication>
#include <klocalizedstring.h>

// UI RELATED INCLUDES

#include "GraphVisualEditor.h"
#include "GraphScene.h"

// MODEL Related Includes
#include "model_GraphDocument.h"

// Graph Related Includes
#include "graphDocument.h"
#include "graph.h"

// Action Related Includes
#include "AbstractAction.h"
#include "AddNode.h"
#include "AddTypedNode.h"
#include "AddEdge.h"
#include "MoveNode.h"
#include "Select.h"
#include "DeleteAction.h"
#include "AlignAction.h"

// backends
#include <kstandarddirs.h>
#include <QActionGroup>
#include <QAction>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <KPushButton>
#include <core/gluonobject.h>
#include <core/gdlhandler.h>

MainWindow::MainWindow() :  QWidget()
{
    _tDocument = new    GraphDocument("Untitled");
    
    setupWidgets();
    setupActions();
    //setupGUI();

   setActiveGraphDocument ( _tDocument );
   _graph = _tDocument->addGraph();
   setActiveGraph(_graph);
   _graph->setKCB(_widgetType);
}

GraphDocument *MainWindow::activeDocument() const{
    return _tDocument;
}

void MainWindow::setupWidgets()
{
    _layout = new QVBoxLayout(this);
    _graphVisualEditor = new GraphVisualEditor ( this );
    _actionButtons = new KToolBar(_graphVisualEditor,false);
    _widgetType = new KComboBox(_actionButtons);
    addCustomTypes(_widgetType);
    _layout->addWidget(_actionButtons);
    _layout->addWidget(_graphVisualEditor);
}

void MainWindow::addCustomTypes(KComboBox* bigList)
{
    QFile nodefile(KGlobal::dirs()->locate("data", "nodetypes.gdl"));
    if (!nodefile.open(QIODevice::ReadOnly)) return;
    QTextStream noderead(&nodefile);
    QString nodetext = noderead.readAll();
    if (nodetext.isEmpty()) return;
    QList<GluonCore::GluonObject*> noderootlist = GluonCore::GDLHandler::instance()->parseGDL(nodetext,this->parent());
    QMap<QString,QVariant> propertlist;
    foreach(QObject* n, noderootlist.first()->children()){
      propertlist.clear();
      foreach(QByteArray ba, n->dynamicPropertyNames()){
	propertlist.insert(QString(ba.data()),n->property(ba.data()));
      }
      bigList->addItem(qobject_cast<GluonCore::GluonObject*>(n)->name(),propertlist);
    }
    nodefile.close();
}

void MainWindow::setupActions()
{
    GraphScene *gc = _graphVisualEditor->scene();
    ac=new KActionCollection(this);
    QActionGroup *g = new QActionGroup ( this );
    _actionButtons->addAction(g->addAction(ac->addAction("add_typed_node",new AddTypedNodeAction(gc,this))));
    _actionButtons->addAction(g->addAction(ac->addAction("move_node",new MoveNodeAction(gc,this))));
    _actionButtons->addAction(g->addAction ( ac->addAction ( "delete_action", new DeleteAction ( gc, this ))));
    _widgetTypeBar=_actionButtons->addWidget(_widgetType);
    _widgetTypeBar->setVisible(false);
    qobject_cast<AddTypedNodeAction*>(ac->action("add_typed_node"))->widgetTypeChanged(_widgetType->currentText());
    connect(ac->action("add_typed_node"),SIGNAL(changed()),this,SLOT(toggleWidgetTypeShown()));
    connect(_widgetType,SIGNAL(currentIndexChanged(QString)),ac->action("add_typed_node"),SLOT(widgetTypeChanged(QString)));
    ac->action("move_node")->trigger();
    
/*
    g->addAction ( ac->addAction ( "select", new SelectAction ( gc, this )));
    g->addAction ( ac->addAction ( "delete", new DeleteAction ( gc, this )));
    actionCollection()->action ( "move_node" )->toggle();
   
    ac->addAction ( "align-hbottom",new AlignAction ( i18n ( "Align on the base" ),  AlignAction::Bottom, _graphVisualEditor ) );
    ac->addAction ( "align-hcenter",new AlignAction ( i18n ( "Align on the center" ),AlignAction::HCenter,_graphVisualEditor ) );
    ac->addAction ( "align-htop",   new AlignAction ( i18n ( "Align on the top" ),   AlignAction::Top,    _graphVisualEditor ) );
    ac->addAction ( "align-vleft",  new AlignAction ( i18n ( "Align on the left" ),  AlignAction::Left,   _graphVisualEditor ) );
    ac->addAction ( "align-vcenter",new AlignAction ( i18n ( "Align on the center" ),AlignAction::VCenter,_graphVisualEditor ) );
    ac->addAction ( "align-vright", new AlignAction ( i18n ( "Align on the right" ), AlignAction::Right,  _graphVisualEditor ) );
    */
}

void MainWindow::toggleWidgetTypeShown(){
  if(_widgetTypeBar->isVisible()){
    _widgetTypeBar->setVisible(false);
  }else{
    _widgetTypeBar->setVisible(true);
  }
}

void MainWindow::setActiveGraphDocument ( GraphDocument* d )
{
    foreach ( QAction *action, ac->actions() ){
        if ( AbstractAction *absAction = qobject_cast<AbstractAction*> ( action ) ){
            absAction->setActiveGraphDocument ( d );
        }
    }

    _graphVisualEditor->setActiveGraphDocument ( d );
}

void MainWindow::setActiveGraph ( Graph *g )
{
    foreach ( QAction *action, ac->actions() )
    {
        if ( AbstractAction *absAction = qobject_cast<AbstractAction*> ( action ) )
            absAction->setActiveGraph ( g );
    }
    _graphVisualEditor->setActiveGraph ( g );
}

Graph* MainWindow::graph() const
{
    return _graph;
}

GraphScene* MainWindow::scene() const
{
    return _graphVisualEditor->scene();
}
