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

#include "graph.h"
#include "edge.h"
#include "node.h"
#include "NodeItem.h"
#include "graphDocument.h"
#include "DynamicPropertiesList.h"

#include <KDE/KInputDialog>
#include <KDE/KDebug>

#include <QtCore/QListIterator>
#include <QtCore/QHashIterator>
#include <QtCore/QMapIterator>
#include <QtCore/QByteArray>
#include <QtCore/QStringList>
#include <QtGui/QColor>

Graph::Graph( GraphDocument* parent ) : QObject( parent )
{
    _directed = true;
    _automate = false;
    _readOnly = false;
    _document = parent;
    _listbox = 0;
    _begin = 0;
    calcRelativeCenter();
    _nodeDefaultColor = "blue";
    _edgeDefaultColor = "gray";
    _nodeNamesVisible = true;
    _nodeValuesVisible = true;
    _edgeNamesVisible = false;
    _edgeValuesVisible = true;
}

Graph::~Graph()
{
    foreach( Edge * e,  _edges )
    {
        remove( e );
    }

    foreach( Node * n, _nodes )
    {
        remove( n );
    }
}

GraphDocument* Graph::document() const
{
    return _document;
}

void Graph::remove()
{
    _document->removeOne( this );
    delete this;
}

QList<Node*> Graph::nodes() const
{
    return _nodes;
}

QList<Edge*> Graph::edges() const
{
    return _edges;
}

void Graph::setNodesColor( QString c )
{
    kDebug() << "Entrou no setNodesColor, com a cor " << c;
    foreach( Node * n, _nodes )
    {
        n->setColor( c );
    }
}

void Graph::setEdgesColor( QString c )
{
    kDebug() << "Entrou no setEdgesColor, com a cor " << c;
    foreach( Edge * e, _edges )
    {
        e->setColor( c );
    }
}

void Graph::setKCB( KComboBox* list )
{
    _listbox = list;
}

Node* Graph::addNode( QString name )
{
    if( _readOnly ) return 0;

    Node*  n = new Node( this );
    n->setName( name );
    _nodes.append( n );
    emit nodeCreated( n );
    connect( n, SIGNAL( changed() ), this, SIGNAL( changed() ) );
    return n;
}

void Graph::addNode( QString name, QPointF pos )
{
    Node* node = addNode( name );
    node->setPos( pos.x(), pos.y() );
}

void Graph::addNode( QString name, QString type )
{
    Node* node = addNode( name );
    QString key;
    node->setName( name );
    node->hideValue( false );
    node->setWidth( 0.5 );
    node->setType( type );
    if( _listbox == 0 )
    {
        emit iAmDisappoint();
        return;
    }
    if( type == "if" )
    {
        node->setValue( QVariant( "true" ) );
        node->hideValue( true );
        node->setValueHeader( "Test" );
        node->setMaxOutEdges( 2 );
    }
    QMap<QString, QVariant> nodelist;
    if( _listbox->isVisible() )
    {
        nodelist = _listbox->itemData( _listbox->currentIndex() ).toMap();
    }
    else
    {
        nodelist = _listbox->itemData( _listbox->findText( type ) ).toMap();
    }
    node->setIcon( nodelist["nodetypesvg"].toString() );
    QMapIterator<QString, QVariant> i( nodelist );
    while( i.hasNext() )
    {
        key = i.next().key();
        if( key != "nodetypesvg" )
        {
            node->addDynamicProperty( key, nodelist[key] );
        }
    }
    connect( this, SIGNAL( forceUpdate() ), node, SIGNAL( changed() ) );
    emit forceUpdate();
}

void Graph::addNode( QString name, QPointF pos, QString type )
{
    Node* node = addNode( name );
    QString key;
    node->setPos( pos.x(), pos.y() );
    node->setName( name );
    node->hideValue( false );
    node->setWidth( 0.5 );
    node->setType( type );
    if( _listbox == 0 )
    {
        emit iAmDisappoint();
        return;
    }
    if( type == "if" )
    {
        node->setValue( QVariant( "true" ) );
        node->hideValue( true );
        node->setValueHeader( "Test" );
        node->setMaxOutEdges( 2 );
    }
    QMap<QString, QVariant> nodelist;
    if( _listbox->isVisible() )
    {
        nodelist = _listbox->itemData( _listbox->currentIndex() ).toMap();
    }
    else
    {
        nodelist = _listbox->itemData( _listbox->findText( type ) ).toMap();
    }
    node->setIcon( nodelist["nodetypesvg"].toString() );
    QMapIterator<QString, QVariant> i( nodelist );
    while( i.hasNext() )
    {
        key = i.next().key();
        if( key != "nodetypesvg" )
        {
            node->addDynamicProperty( key, nodelist[key] );
        }
    }
    connect( this, SIGNAL( forceUpdate() ), node, SIGNAL( changed() ) );
    emit forceUpdate();
}

Edge* Graph::addEdge( Node* from, Node* to, QGraphicsSvgItem* cFrom, QGraphicsSvgItem* cTo )
{
    if( _readOnly ) return 0;

    if( from == 0 || to == 0 )
    {
        return 0;
    }


    if( ( from == to ) && ( !_directed ) )
    {
        return 0;
    }
    else if( ( from->edges( to ).size() >= 1 ) && ( !_directed ) )
    {
        return 0;
    }
    else if( ( _nodes.indexOf( from ) == -1 ) || ( _nodes.indexOf( to ) == -1 ) )
    {
        return 0;
    }
    else if( from->outEdgesCapacityReached() || to->inEdgesCapacityReached() )
    {
        emit iAmDisappoint();
        return 0;
    }
    else if( !connectionIsValid( true, cFrom ) || !connectionIsValid( false, cTo ) )
    {
        emit iAmDisappoint();
        return 0;
    }
    else if( ( from == to ) && ( from->selfEdgesCapacityReached() ) )
    {
        emit iAmDisappoint();
        return 0;
    }

    Edge* e  = new Edge( this, from, to, cFrom, cTo );
    /*if(!assignEdgeAction(from, e)){
      delete e;
      return 0;
    }*/
    _edges.append( e );
    emit edgeCreated( e );
    connect( e, SIGNAL( changed() ), this, SIGNAL( changed() ) );
    emit forceUpdate();
    return e;
}

bool Graph::connectionIsValid( bool direction, QGraphicsSvgItem* svg )
{
    QHashIterator<QString, QGraphicsSvgItem*> iterator( qgraphicsitem_cast<NodeItem*>( svg->parentItem() )->connectors() );
    QString key;
    QListIterator<QByteArray> plist = qgraphicsitem_cast<NodeItem*>( svg->parentItem() )->node()->dynamicPropertyNames();
    //direction: true=check from this node, false=check to this node
    foreach( Edge * e, _edges )
    {
        if( direction == true )
        {
            if( e->connectorFrom() == svg )
            {
                return false;
            }
        }
        else
        {
            if( e->connectorTo() == svg )
            {
                return false;
            }
        }
    }
    if( direction == true )
    {
        while( iterator.hasNext() )
        {
            if( iterator.next().value() == svg )
            {
                key = iterator.key();
                while( plist.hasNext() )
                {
                    if( plist.next() == key )
                    {
                        if( qgraphicsitem_cast<NodeItem*>( svg->parentItem() )->node()->property( key.toUtf8().data() ) == "in" ) return false;
                    }
                }
            }
        }
    }
    else
    {
        while( iterator.hasNext() )
        {
            if( iterator.next().value() == svg )
            {
                key = iterator.key();
                while( plist.hasNext() )
                {
                    if( plist.next() == key )
                    {
                        if( qgraphicsitem_cast<NodeItem*>( svg->parentItem() )->node()->property( key.toUtf8().data() ) == "out" ) return false;
                    }
                }
            }
        }
    }
    return true;
}

bool Graph::assignEdgeAction( Node* from, Edge* edge )
{
    QListIterator<QByteArray> plist = from->dynamicPropertyNames();
    QListIterator<Edge*> elist = from->out_edges();
    QStringList middleman;
    QString temp;
    bool safe;
    bool okPressed;
    QString selectedProperty;
    if( !plist.hasNext() )
    {
        iAmDisappoint();
        return false;
    }
    else
    {
        while( plist.hasNext() )
        {
            safe = true;
            temp = QString( plist.next().data() );
            while( elist.hasNext() )
            {
                if( elist.next()->value() == temp )
                {
                    safe = false;
                }
            }
            elist.toFront();
            if( safe )
            {
                middleman << temp;
            }
        }

        selectedProperty = KInputDialog::getItem( "Select Action to Associate to:", "Select Action:" , middleman, false, &okPressed);
    }
    if( !okPressed )
    {
        return false;
    }
    else
    {
        edge->setValue( selectedProperty );
        return true;
    }
}


/*Edge* Graph::addEdge(const QString& name_from, const QString& name_to) {
    if (_readOnly) return 0;
    Node *from = 0;
    Node *to   = 0;

    QString tmpName;

    foreach( Node* n,  _nodes) {
        tmpName = n->name();

        if (tmpName == name_from) {
            from = n;
        }
        if (tmpName == name_to) {
            to = n;
        }
        if ((to != 0) && (from != 0)) {
            break;
        }
    }

    return addEdge(from, to);
}*/

bool Graph::directed() const
{
    return _directed;
}

Node* Graph::node( const QString& name )
{
    QString tmpName;
    foreach( Node * n,  _nodes )
    {
        tmpName = n->name();
        if( tmpName == name )
        {
            return n;
        }
    }
    return 0;
}

void Graph::remove( Node* n )
{
    _nodes.removeOne( n );
    n->deleteLater();
    emit forceUpdate();
}

void Graph::remove( Edge* e )
{
    _edges.removeOne( e );
    delete e;
    emit forceUpdate();
}

void Graph::setDirected( bool directed )
{

    foreach( Node * n1, _nodes )
    {
        foreach( Node * n2, n1->adjacent_nodes() )
        {
            // do not permit loop nodes while changing graph's state.
            if( ( n1->edges( n2 ).size() == 1 ) && ( n1 != n2 ) )
            {
                continue;
            }

            QList<Edge*> listEdges = n1->edges( n2 );
            if( n1 != n2 )
            {
                listEdges.removeFirst();
            }

            foreach( Edge * e, listEdges )
            {
                remove( e );
            }
        }
    }
    emit forceUpdate();
    _directed = directed;
    emit complexityChanged( directed );
    return;
}

void Graph::calcRelativeCenter()
{
    /*
      _top = _nodes[0]->y();   _bottom = _nodes[0]->y();
      _left = _nodes[0]->x(); _right = _nodes[0]->x();
      kDebug() << "INIT:";
      kDebug() << "TOP : " << _top << " BOTTOM " << _bottom << "LEFT" << _left << "RIGHT" << _right;
      for (int counter = 0; counter < _nodes.size(); counter++) {
       if(_nodes[counter]->x() > _right)  _right = _nodes[counter]->x();
       if(_nodes[counter]->y() > _top)  _top = _nodes[counter]->y();
       if(_nodes[counter]->x() < _left)  _left = _nodes[counter]->x();
       if(_nodes[counter]->y() < _bottom)  _bottom = _nodes[counter]->y();
           kDebug() << "TOP : " << _top << " BOTTOM " << _bottom << "LEFT" << _left << "RIGHT" << _right;
      }
      */
    /// this will be here till I find a better way to calculate a *relative* center of the graph, and not the center of the document.
    if( parent() != 0 )
    {
        GraphDocument* gd = qobject_cast<GraphDocument*>( parent() );
        _relativeCenter.setY( gd->height() / 2 );
        _relativeCenter.setX( gd->width() / 2 );
    }
    else
    {
        _relativeCenter.setY( 0 );
        _relativeCenter.setX( 0 );
    }
}

QPointF Graph::relativeCenter() const
{
    return _relativeCenter;
}

const QString& Graph::name() const
{
    return _name;
}
void Graph::setName( const QString& s )
{
    _name = s;
}

bool Graph::setBegin( Node* n )
{
    if( !n )
    {
        _begin = 0;
        return false;
    }

    if( !_begin )
    {
        _begin = n;
        return true;
    }
    else if( _begin == n )
    {
        return false;
    }

    _begin->setBegin( false );
    _begin = n;
    return true;
}

Node* Graph::begin() const
{
    return _begin;
}

Node* Graph::addEnd( Node* n )
{
    _ends.append( n );
    return n;
}

void Graph::removeEnd( Node* n )
{
    _ends.removeAll( n );
}

void Graph::setNodeDefaultColor( const QString& color )
{
    kDebug() << "Entrou com cor aqui painho." << color;
    _nodeDefaultColor = color;
}

const QString& Graph::nodeDefaultColor() const
{
    return _nodeDefaultColor;
}

void Graph::setEdgeDefaultColor( const QString& color )
{
    _edgeDefaultColor = color;
}
const QString& Graph::edgeDefaultColor() const
{
    return _edgeDefaultColor;
}

void Graph::setAutomate( bool b )
{
    _automate = b;
    emit automateChanged( b );
}
bool Graph::automate()
{
    return _automate;
}

void Graph::addDynamicProperty( QString property, QVariant value )
{
    this->setProperty( property.toUtf8(), value );
    if( value.isValid() )
    {
        DynamicPropertiesList::New()->addProperty( this, property );
    }
}

void Graph::removeDynamicProperty( QString property )
{
    this->addDynamicProperty( property, QVariant::Invalid );
    DynamicPropertiesList::New()->removeProperty( this, property );
}

void Graph::addNodesDynamicProperty( QString property, QVariant value )
{
    foreach( Node * n, _nodes )
    {
        n->addDynamicProperty( property, value );
    }
}

void Graph::addEdgesDynamicProperty( QString property, QVariant value )
{
    foreach( Edge * e, _edges )
    {
        e->addDynamicProperty( property, value );
    }
}

void Graph::removeNodesDynamicProperty( QString property )
{
    foreach( Node * n, _nodes )
    {
        n->removeDynamicProperty( property );
    }
}
void Graph::removeEdgesDynamicProperty( QString property )
{
    foreach( Edge * e, _edges )
    {
        e->removeDynamicProperty( property );
    }
}

void Graph::setNodeNameVisibility( bool b )
{
    _nodeNamesVisible = b;
    foreach( Node * n, _nodes )
    {
        n->hideName( b );
    }
}

bool Graph::nodeNameVisibility()
{
    return _nodeNamesVisible;
}

void Graph::setEdgeNameVisibility( bool b )
{
    _edgeNamesVisible = b;
    foreach( Edge * n, _edges )
    {
        n->hideName( b );
    }
}

bool Graph::edgeNameVisibility()
{
    return _edgeNamesVisible;
}

void Graph::setNodeValueVisibility( bool b )
{
    _nodeValuesVisible = b;
    foreach( Node * n, _nodes )
    {
        n->hideValue( b );
    }
}
bool Graph::nodeValueVisibility()
{
    return _nodeValuesVisible;
}

void Graph::setEdgeValueVisibility( bool b )
{
    _edgeValuesVisible = b;
    foreach( Edge * n, _edges )
    {
        n->hideValue( b );
    }
}

bool Graph::edgeValueVisibility()
{
    return _edgeValuesVisible;
}
