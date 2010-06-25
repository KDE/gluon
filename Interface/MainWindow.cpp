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
#include "AddEdge.h"
#include "MoveNode.h"
#include "Select.h"
#include "DeleteAction.h"
#include "AlignAction.h"

// backends
#include <kstandarddirs.h>
//#include <QActionGroup>
#include <QAction>
#include <KPushButton>

MainWindow::MainWindow() :  QWidget()
{
    _tDocument = new    GraphDocument("Untitled");
    
    setupWidgets();
    setupActions();
    //setupGUI();

   setActiveGraphDocument ( _tDocument );
   _graph = _tDocument->addGraph();
   setActiveGraph(_graph);
}

GraphDocument *MainWindow::activeDocument() const{
    return _tDocument;
}

void MainWindow::setupWidgets()
{
    _graphVisualEditor = new GraphVisualEditor ( this );
    _actionButtons = new KToolBar(_graphVisualEditor,false);
}

void MainWindow::setupActions()
{
    GraphScene *gc = _graphVisualEditor->scene();
    ac=new KActionCollection(this);
    //QActionGroup *g = new QActionGroup ( this );
    _actionButtons->addAction(ac->addAction("add_node",new AddNodeAction(gc,this)));
    _actionButtons->addAction(ac->addAction("move_node",new MoveNodeAction(gc,this)));
     
     
    
    //g->addAction ( ac->addAction ( "move_node", new MoveNodeAction(gc, this )));
    //g->addAction ( ac->addAction ( "add_node", new AddNodeAction ( gc, this )));
   /* g->addAction ( ac->addAction ( "add_edge", new AddEdgeAction ( gc, this )));
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
