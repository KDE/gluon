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

#ifndef MOVENODE_H
#define MOVENODE_H

#include "AbstractAction.h"
#include <QObject>
#include <QPointF>
class QGraphicsLineItem;
class QGraphicsSvgItem;
class QGraphicsItem;
class QObject;
class NodeItem;
class Node;
class Graph;
class QGraphicsView;

/*!
  \brief The 'Move Node' Action
  This action holds the 'Move Node' icon and tooltips, and when it's executed,
  it will move the selected node around the screen.
*/

class MoveNodeAction : public AbstractAction
{
        Q_OBJECT
    public:
        /*!
          Default constructor
          \param parent the Parent QOBject that will hold this action. ( remove it in the future, maybe? )
        */

        explicit MoveNodeAction( GraphScene* scene, QObject* parent = 0 );

        /*!
          Default Destructor
        */
        ~MoveNodeAction();
    public slots:
        /*!
          will be executed when the mouse press a button.
          \param pos the position onscreen of the click.
        */
        void executePress( QPointF pos );
        /*! will be executed when the mouse moves.
          \param pos the current position of the cursor.
        */
        void executeMove( QPointF pos );

        /*! will be executed when the mouse releases a click
        \param pos the position of the cursor.
        */
        void executeRelease( QPointF pos );

    signals:
        void addEdge( Node* from, Node* to, QGraphicsSvgItem* cFrom, QGraphicsSvgItem* cTo );

    protected:
        /*! the node that will be moved on screen */
        NodeItem* _movableNode;

        /*! the model of the NodeItem,
        needs it to modify it's internal value when the move is finished */
        Node* _node;

        /*! the parent graph of the node. */
        Graph* _g;

        GraphScene* _graphScene;

        /*! the QGraphicsView. */
        QGraphicsView* _view;

        /*! the point of the first click while adding a new edge */
        QPointF _startPos;

        /*! a temporary line that will connect the two Nodes. */
        QGraphicsLineItem* _tmpLine;

        /*! pointer to the node that suffered the mouse-release-click */
        NodeItem* _nodeTo;

        /*! pointer to the SVG Item that suffered the mouse-release-click */
        QGraphicsSvgItem* _svgAt;

        /*! pointer to the SVG Item that suffered the mouse-pressed-click */
        QGraphicsSvgItem* _svgFrom;

        /*! List of Graphics items at mouse position */
        QList<QGraphicsItem*> _itemsUnderCursor;
};

#endif
