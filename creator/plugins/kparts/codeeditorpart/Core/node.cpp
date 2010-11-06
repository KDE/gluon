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

#include "node.h"
#include "edge.h"
#include "graph.h"
#include <KDebug>
#include <KGlobal>
#include <kstandarddirs.h>

#include "DynamicPropertiesList.h"


Node::Node( Graph* parent ) : QObject( parent )
{
    _graph = parent;
    _x = 0;
    _y = 0;
    _width = 0.5;
    _showName = true;
    _showValue = true;
    _showImage = false;
    _begin = false;
    _end = false;
    _color = _graph->nodeDefaultColor();
    _changing = false;
    _value = 0;
    _valueHeader = "Value";
    _image = QPixmap( 100, 100 );
    _image.fill();
    _maxInEdges = 1;
    _maxOutEdges = 1;
    _maxSelfEdges = 0;
    _icon = "rocs_method";
    _type = "";
    _nitem = 0;
    _iconpackage = KGlobal::dirs()->locate( "data", "iconpacks/default.svg" );
    kDebug() << "Node successfully created" << _iconpackage;
}

Node::~Node()
{
    emit removed();
    empty( _in_edges );
    empty( _out_edges );
    empty( _self_edges );

}

void Node::empty( EdgeList& list )
{
    foreach( Edge * e, list )
    {
        e->remove();
    }
}

bool Node::showName()
{
    return _showName;
}

bool Node::showValue()
{
    return _showValue;
}

bool Node::showImage()
{
    return _showImage;
}

void Node::hideImage( bool b )
{
    _showImage = b;
    emit changed();
}

void Node::hideName( bool b )
{
    _showName = b;
    emit changed();
}

void Node::hideValue( bool b )
{
    _showValue = b;
    emit changed();
}

void Node::setIcon( const QString& s )
{
    _icon = s;
    emit changed();
}

void Node::setIconPackage( const QString& s )
{
    _iconpackage = s;
}

void Node::setType( QString type )
{
    _type = type;
}

QString Node::type()
{
    return _type;
}

QGraphicsSvgItem* Node::nodeItem()
{
    return _nitem;
}

void Node::setNodeItem( QGraphicsSvgItem* ni )
{
    _nitem = ni;
}

const QString& Node::icon() const
{
    return _icon;
}

const QString& Node::iconPackage() const
{
    return _iconpackage;
}

QList<Node*> Node::adjacent_nodes() const
{
    QList<Node*> adjacent;

    foreach( Edge * e, _out_edges )
    {
        adjacent.append( e->to() );
    }

    if( _graph -> directed() )
    {
        foreach( Edge * e, _self_edges )
        {
            adjacent.append( e->to() );
        }
        return adjacent;
    }

    foreach( Edge * e, _in_edges )
    {
        adjacent.append( e->from() );
    }
    return adjacent;
}


EdgeList Node::adjacent_edges() const
{
    EdgeList adjacent;

    adjacent << _out_edges;

    if( _graph -> directed() )
    {
        adjacent << _self_edges;
    }
    else
    {
        adjacent << _in_edges;
    }

    return adjacent;
}

void Node::addInEdge( Edge* e )
{
    _in_edges.append( e );
}

void Node::addOutEdge( Edge* e )
{
    _out_edges.append( e );
}

void Node::addSelfEdge( Edge* e )
{
    _self_edges.append( e );
}

EdgeList Node::in_edges() const
{
    return _in_edges;
}

EdgeList Node::out_edges() const
{
    return _out_edges;
}

EdgeList Node::self_edges() const
{
    return _self_edges;
}

/*Edge* Node::addEdge(Node* to) {
    return _graph->addEdge(this, to);
}*/

void Node::removeEdge( Edge* e, int edgeList )
{
    switch( edgeList )
    {
        case In  :
            removeEdge( e, _in_edges );
            break;
        case Out :
            removeEdge( e, _out_edges );
            break;
        case Self:
            removeEdge( e, _self_edges );
            break;
    }
}

void Node::removeEdge( Edge* e, EdgeList& list )
{
    if( list.contains( e ) ) list.removeOne( e );
}

EdgeList Node::edges( Node* n )
{
    EdgeList list;
    if( n == this )
    {
        return _self_edges;
    }
    foreach( Edge * tmp, _out_edges )
    {
        if( tmp->to() == n )
        {
            list.append( tmp );
        }
    }
    foreach( Edge * tmp, _in_edges )
    {
        if( tmp->from() == n )
        {
            list.append( tmp );
        }
    }
    return list;
}

void Node::remove()
{
    _graph->remove( this );
}

//! Properties:
void Node::setX( int x )
{
    _x = x;
    if( ! _changing )
    {
        emit changed();
    }
}

qreal Node::x() const
{
    return _x;
}

void Node::setY( int y )
{
    _y  = y;
    if( ! _changing )
    {
        emit changed();
    }
}

bool Node::inEdgesCapacityReached() const
{
    if( maxInEdges() == -1 ) return false;
    if( maxInEdges() <  in_edges().count() + 1 ) return true;
    return false;
}

bool Node::outEdgesCapacityReached() const
{
    if( maxOutEdges() == -1 ) return false;
    if( maxOutEdges() <  out_edges().count() + 1 ) return true;
    return false;
}

bool Node::selfEdgesCapacityReached() const
{
    if( maxSelfEdges() == -1 ) return false;
    if( maxSelfEdges() <  self_edges().count() + 1 ) return true;
    return false;
}


void Node::setWidth( qreal w )
{
    _width = w;
    if( ! _changing )
    {
        emit changed();
        kDebug() << "Updating node drawing";
    }
}

void Node::setPos( qreal x, qreal y )
{
    _x = x;
    _y = y;
    if( ! _changing )
    {
        emit changed();
    }

}

qreal Node::y() const
{
    return _y;
}

qreal Node::width() const
{
    return _width;
}

void Node::setColor( const QString& s )
{
    _color = s;
    if( ! _changing )
    {
        emit changed();
    }
}

const QString& Node::color() const
{
    return _color;
}

void Node::setMaxInEdges( const int& m )
{
    _maxInEdges = m;
    if( ! _changing )
    {
        emit changed();
    }
}

const int& Node::maxInEdges() const
{
    return _maxInEdges;
}

void Node::setMaxOutEdges( const int& m )
{
    _maxOutEdges = m;
    if( ! _changing )
    {
        emit changed();
    }
}

const int& Node::maxSelfEdges() const
{
    return _maxSelfEdges;
}

void Node::setMaxSelfEdges( const int& m )
{
    _maxSelfEdges = m;
    if( ! _changing )
    {
        emit changed();
    }
}

const int& Node::maxOutEdges() const
{
    return _maxOutEdges;
}

void Node::setImage( const QPixmap& p )
{
    _image = p;
    if( ! _changing )
    {
        emit changed();
    }
}

const QPixmap& Node::image() const
{
    return _image;
}

void Node::setName( const QString& s )
{
    _name = s;
    if( ! _changing )
    {
        emit changed();
    }
}

const QString& Node::name() const
{
    return _name;
}

void Node::setBegin( bool begin )
{
    if( !begin )
    {
        _begin = false;
        if( _graph->begin() == this )
        {
            _graph->setBegin( 0 );
        }
    }
    else if( _graph->begin() == this )
    {
        return;
    }
    else if( _graph->setBegin( this ) )
    {
        _begin = true;
    }
    else
    {
        return;
    }

    if( ! _changing )
    {
        emit changed();
    }
}

void Node::setEnd( bool end )
{
    _end = end;

    if( end )
    {
        _graph->addEnd( this );
    }
    else
    {
        _graph->removeEnd( this );
    }
    if( ! _changing )
    {
        emit changed();
    }
}

bool Node::begin() const
{
    return _begin;
}

bool Node::end() const
{
    return _end;
}

const QVariant Node::value() const
{
    return _value;
}
void  Node::setValue( QVariant s )
{
    _value = s;
    if( ! _changing )
    {
        emit changed();
    }
}

void Node::setValue( const QString& c )
{
    _value = c;
    if( _changing )
    {
        emit changed();
    }
}
void Node::startChange()
{
    _changing = true;
}

void Node::endChange()
{
    _changing = false;
    emit changed();
}

void Node::addDynamicProperty( QString property, QVariant value )
{
    this->setProperty( property.toUtf8(), value );
    if( value.isValid() )
    {
        DynamicPropertiesList::New()->addProperty( this, property );
    }
}

void Node::removeDynamicProperty( QString property )
{
    this->addDynamicProperty( property.toUtf8(), QVariant::Invalid );
    DynamicPropertiesList::New()->removeProperty( this, property );
}
