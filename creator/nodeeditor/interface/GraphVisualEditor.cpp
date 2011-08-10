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

#include "GraphVisualEditor.h"
#include "GraphScene.h"
#include "NodeEditor.h"
#include "NodeItem.h"
#include "OrientedEdgeItem.h"

#include "graphDocument.h"
#include "graph.h"
#include "node.h"
#include "edge.h"

#include "AlignAction.h"
//#include "settings.h"

#include <QVBoxLayout>
#include <QGraphicsItem>
#include <KDebug>
#include <QGraphicsView>
#include <QPainter>

GraphVisualEditor::GraphVisualEditor( NodeEditor* parent )
    : QWidget( parent ),
      _topNode( 0 ),
      _bottomNode( 0 ),
      _leftNode( 0 ),
      _rightNode( 0 )
{
    _scene = 0;
    _graphDocument = 0;
    _graph = 0;
    _mainWindow = parent;
    setupWidgets();
}

void GraphVisualEditor::setupWidgets()
{
    QVBoxLayout* vLayout = new QVBoxLayout();
    vLayout->setContentsMargins( 0, 0, 0, 0 );
    _scene = new GraphScene( this );
    _graphicsView = new QGraphicsView();
    _graphicsView->setRenderHints( QPainter::Antialiasing );
    _graphicsView->setScene( _scene );
    vLayout -> addWidget( _graphicsView );
    setLayout( vLayout );
}

QGraphicsView* GraphVisualEditor::view() const
{
    return _graphicsView;
}

void GraphVisualEditor::setActiveGraphDocument( GraphDocument* gd )
{

    if( _graphDocument != 0 )
    {
        releaseGraphDocument();
    }

    _graphDocument = gd;
    kDebug() << "Graph Document Set: " << gd->name();
    _scene->setActiveGraphDocument( gd );

}

void GraphVisualEditor::releaseGraphDocument()
{
    _scene->clear();
    //int size = _graphDocument->size();
    //for (int i = 0; i < size; i++) {
    //    _graphDocument->at(i)->disconnect(this);
    //}
    if( _graphDocument->size() != 0 )
        _scene->setActiveGraphDocument( 0 );

}

void GraphVisualEditor::drawGraphOnScene( Graph* /*g*/ ) {}

void GraphVisualEditor::setActiveGraph( Graph* g )
{
    _graph = g;
    _scene->setActiveGraph( g );
    connect( _graph, SIGNAL( iAmDisappoint() ), this, SLOT( displaySadnessSlot() ) );
}

GraphScene* GraphVisualEditor::scene() const
{
    return _scene;
}

void GraphVisualEditor::displaySadnessSlot()
{
    _graphicsView->setCursor( QCursor( KIcon( "face-sad" ).pixmap( 32, 32 ) ) );
    _time = QTime::currentTime().addSecs( 1 );
    while( _time > QTime::currentTime() )
    {
        //do nothing
    }
    _graphicsView->setCursor( Qt::ArrowCursor );
}

QList<NodeItem*> GraphVisualEditor::selectedNodes() const
{
    QList<NodeItem*> tmpList;
    QList<QGraphicsItem*> l = _scene->selectedItems();
    foreach( QGraphicsItem * i, l )
    {
        if( qgraphicsitem_cast<NodeItem*>( i ) )
        {
            tmpList.append( qgraphicsitem_cast<NodeItem*>( i ) );
        }
    }
    return tmpList;
}
