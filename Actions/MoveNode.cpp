
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
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Step; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "MoveNode.h"
#include "GraphScene.h"
#include "graph.h"
#include "node.h"
#include "graphDocument.h"
#include "NodeItem.h"
#include <KLocale>
#include <QGraphicsView>

#include <KDebug>
//#include "settings.h"

MoveNodeAction::MoveNodeAction(GraphScene *scene, QObject *parent)
        : AbstractAction(scene, parent) {
    setText(i18n ( "Move Node" ));
    setToolTip ( i18n ( "Moves a node around the drawing area." ) );
    setIcon ( KIcon ( "arrow" ) );
    _movableNode = 0;
    _name = "move";
    _graphScene=scene;
}

MoveNodeAction::~MoveNodeAction() {
    kDebug() << "Destroyed";
}

void MoveNodeAction::executePress(QPointF pos) {
    if (_graph == 0) {
        return;
    }
    if (_graph->readOnly()) return;
    _movableNode = qgraphicsitem_cast<NodeItem*>(_graphScene->itemAt(pos));
    if (!_movableNode) return;
    _svgFrom = _movableNode->getCurrentConnector();
    _node = _movableNode->node();
    if(_svgFrom != 0){
      _startPos = QPointF(_movableNode->node()->x(), _movableNode->node()->y());
    }
    connect(this, SIGNAL(addEdge(Node*,Node*)), _graph, SLOT(addEdge(Node*,Node*)));
}

void MoveNodeAction::executeMove(QPointF pos) {
    if ( ! _movableNode ) {
        return;
    }
    if(_svgFrom != 0){
      if ( !_tmpLine ) {
        _tmpLine = new QGraphicsLineItem( _startPos.x(), _startPos.y(), pos.x(), pos.y());
        _graphScene->addItem(_tmpLine);
    }
    else {
        _tmpLine->setLine(_startPos.x(), _startPos.y(), pos.x(), pos.y());
    }
    }else{
    if ((pos.x() < 0) || (pos.x() > _graphDocument->width())) {
        if (( pos.y() > 0) && (pos.y() < _graphDocument->height())) {
            _node -> setY(pos.y());
        }
    }
    else if ((pos.y() < 0) || (pos.y() > _graphDocument->height())) {
        if (( pos.x() > 0) && (pos.x() < _graphDocument->width())) {
            _node -> setX(pos.x());
        }
    }
    else {
        _node -> setPos(pos.x(), pos.y());
    }
    }
}

void MoveNodeAction::executeRelease(QPointF pos) {
    if ( !_movableNode ) {
        return;
    }
    if(_svgFrom != 0){
    if ( _tmpLine ) {
        delete _tmpLine;
        _tmpLine = 0;
    }
    _nodeTo = qgraphicsitem_cast<NodeItem*>(_graphScene->itemAt(pos));
    _svgAt = _nodeTo->getCurrentConnector();
    if (  _nodeTo ) {
      if(_svgAt != 0 && _svgFrom != 0){
      emit addEdge( _movableNode->node(),  _nodeTo->node() );
      }
    }}else{
    if (!((pos.x() < 0) || (pos.y() < 0) || (pos.x() > _graphDocument->width())|| (pos.y() > _graphDocument->height()))) {
        _node -> setY(pos.y());
        _node -> setX(pos.x());
    }}
    _movableNode = 0;
    disconnect(this, 0, _graph, 0);
}
