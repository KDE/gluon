/***************************************************************************
 * main.cpp
 * This file is part of the KDE project
 * copyright (C)2004-2007 by Tomaz Canabrava (tomaz.canabrava@gmail.com)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 * You should have received a copy of the GNU Library General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 ***************************************************************************/

#ifndef NODE_H
#define NODE_H

#include <QObject>
#include <QList>
#include <QString>
#include <QPixmap>

#include "rocslib_export.h"
#include "edge.h"
#include <QGraphicsSvgItem>

class Node;


typedef QList<Node*> NodeList;

class Node : public QObject
{
        Q_OBJECT
        Q_PROPERTY( qreal x READ x WRITE setX )
        Q_PROPERTY( qreal y READ y WRITE setY )
        Q_PROPERTY( qreal width READ width WRITE setWidth )
        Q_PROPERTY( QString name READ name WRITE setName )
        Q_PROPERTY( QString color READ color WRITE setColor )
        Q_PROPERTY( bool begin READ begin WRITE setBegin )
        Q_PROPERTY( bool end READ end WRITE setEnd )
        Q_PROPERTY( QVariant value READ value WRITE setValue )
        Q_PROPERTY( QPixmap image READ image WRITE setImage )
        Q_PROPERTY( int maxInEdges READ maxInEdges WRITE setMaxInEdges )
        Q_PROPERTY( int maxOutEdges READ maxOutEdges WRITE setMaxOutEdges )
        Q_PROPERTY( int maxSelfEdges READ maxSelfEdges WRITE setMaxSelfEdges )
        Q_PROPERTY( QString iconPackage READ iconPackage WRITE setIconPackage )
        Q_PROPERTY( QString icon READ icon WRITE setIcon )

    public:
        Node( Graph* parent );
        ~Node();
        void addInEdge( Edge* e );
        void addOutEdge( Edge* e );
        void addSelfEdge( Edge* e );
        void removeEdge( Edge* e, int edgeList );
        void removeEdge( Edge* e, EdgeList& list );
        void remove();
        enum EdgeLists {In, Out, Self};
        /**
         * Marks Node as having changed. Used for updating Graph.
         */
        void startChange();
        void endChange();
        bool showName();
        bool showImage();
        bool showValue();
        bool inEdgesCapacityReached() const;
        bool outEdgesCapacityReached() const;
        bool selfEdgesCapacityReached() const;

        Graph* graph()
        {
            return _graph;
        }

    public  slots:
        NodeList adjacent_nodes() const;
        EdgeList adjacent_edges() const;
        /**
         * List of Edges connected to Node.
         * @param    n    Node to look for connected edges.
         * @return    Edges connected to Node.
         */
        EdgeList edges( Node* n );
        /**
         * List of Edges going into this Node.
         * @return    Edges going into this Node.
         */
        EdgeList in_edges() const;
        /**
         * List of Edges going out of this Node.
         * @return    Edges going out of this Node.
         */
        EdgeList out_edges() const;
        /**
         * List of Edges connected to and from this Node.
         * @return    Edges to and from this Node.
         */
        EdgeList self_edges() const;

        void setX( int x );
        void setY( int y );
        void setWidth( double w );
        void setPos( qreal x, qreal y );
        qreal x() const;
        qreal y() const;
        qreal width() const;
        void setColor( const QString& s );
        const QString& color() const;
        void setName( const QString& s );
        const QString& name() const;
        bool begin() const;
        bool end() const;
        void setBegin( bool begin = true );
        void setEnd( bool end = true );
        void setValue( const QVariant v );
        void setValue( const QString& s );
        void setValueHeader( const QString& s )
        {
            _valueHeader = s;
        }
        const QString valueHeader()
        {
            return _valueHeader;
        }
        const QVariant value() const;
        const QPixmap& image() const;
        /**
         * Sets Node image to be displayed.
         * @param    p    Pixmap to be used as Node image.
         */
        void setImage( const QPixmap& p );
        /**
         * Set max number of Edges allowed flowing into this Node.
         * @param    m    Number of Edges allowed.
         */
        void setMaxInEdges( const int& m );
        const int& maxInEdges() const;
        /**
         * Set max number of Edges allowed flowing out of this Node.
         * @param    m    Number of Edges allowed.
         */
        void setMaxOutEdges( const int& m );
        const int& maxOutEdges() const;
        /**
         * Set max number of Edges allowed wit both to and from points as this Node.
         * @param    m    Number of Edges allowed.
         */
        void setMaxSelfEdges( const int& m );
        const int& maxSelfEdges() const;
        /**
         * Sets icon from current iconpack based on SVG name.
         * @param    s    String containing name of icon for node.
         */
        void setIcon( const QString& s );
        const QString& icon() const;
        const QString& iconPackage() const;
        /**
         * Sets icon package from SVG file.
         * @param    s    String containing name of iconpack.
         */
        void setIconPackage( const QString& s );
        void hideName( bool b );
        void hideImage( bool b );
        void hideValue( bool b );
        /**
         * Sets type of the node.
         * @param    type    String containing type for node.(must be valid type)
         */
        void setType( QString type );
        QString type();
        /**
         * Qt graphics scene item representation of Node on graph.
         * @return    SVGitem of this node.
         */
        QGraphicsSvgItem* nodeItem();
        /**
         * Assigns SVGitem to Node.
         * @param    ni    SVGitem to be associated with Node.
         */
        void setNodeItem( QGraphicsSvgItem* ni );
        /** Add a property to this node
        * @param property Name of property
        * @param value Value of the property. arg2 should be different of QVariant::Invalid.
        */
        void addDynamicProperty( QString property, QVariant value );

        /** Remove property arg1 from this node. If property arg1 don't exist in this node, nothing is made.
        * @param property name os property to remove
        */
        void removeDynamicProperty( QString property );

        //Edge* addEdge(Node* to);

    private:
        EdgeList _in_edges;
        EdgeList _out_edges;
        EdgeList _self_edges;
        void empty( EdgeList& list );

        //! fixed properties
        qreal _x;
        qreal _y;
        qreal _width;

        bool _begin;
        bool _end;
        bool _changing;
        bool _showName;
        bool _showValue;
        bool _showImage;

        Graph* _graph;

        QString _name;
        QString _color;
        QString _iconpackage;
        QString _icon;

        QVariant _value;
        QPixmap _image;
        int _maxInEdges;
        int _maxOutEdges;
        int _maxSelfEdges;
        QString _type;
        QGraphicsSvgItem* _nitem;
        QString _valueHeader;

    signals:
        void removed();
        void changed();
};


#endif
