
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

#include "edge.h"
#include "node.h"
#include "NodeItem.h"
#include "graph.h"
#include "DynamicPropertiesList.h"
#include <KDebug>

Edge::Edge( Graph* parent, Node* from, Node* to, QGraphicsSvgItem* cFrom, QGraphicsSvgItem* cTo ) :
    QObject( parent ),
    _from( from ),
    _to( to )

{
    _graph = parent;
    _color = _graph->edgeDefaultColor();

    if( from == to )
    {
        connect( from, SIGNAL( changed() ), this, SIGNAL( changed() ) );
        from -> addSelfEdge( this );
    }
    else
    {
        connect( from, SIGNAL( changed() ), this, SIGNAL( changed() ) );
        from -> addOutEdge( this );
        connect( to, SIGNAL( changed() ), this, SIGNAL( changed() ) );
        to -> addInEdge( this );
    }
    connect( parent, SIGNAL( complexityChanged( bool ) ), this, SIGNAL( changed() ) );

    _relativeIndex = _to -> edges( _from ).size();
    _showName = true;
    _showValue = true;
    _style = "solid";
    _width = 1;
    _cFrom = cFrom;
    _cTo = cTo;
}

Edge::~Edge()
{
    if( _from == _to )
    {
        _from->removeEdge( this, Node::Self );
    }
    else
    {
        _from->removeEdge( this, Node::Out );
        _to->removeEdge( this, Node::In );
    }
    _from = 0;
    _to = 0;
    emit removed();
}

void Edge::remove()
{
    _graph->remove( this );
}

QString Edge::fromConnector()
{
    return qobject_cast<NodeItem*>( _from->nodeItem() )->connectors().key( _cFrom );
}

QString Edge::toConnector()
{
    return qobject_cast<NodeItem*>( _to->nodeItem() )->connectors().key( _cTo );
}

QString Edge::fromNode()
{
    return _from->name();
}

QString Edge::toNode()
{
    return _to->name();
}


bool Edge::showName()
{
    return _showName;
}

bool Edge::showValue()
{
    return _showValue;
}

void Edge::hideName( bool b )
{
    _showName = b;
    emit changed();
    kDebug() << "Hide Name: " << b;
}

void Edge::hideValue( bool b )
{
    _showValue = b;
    emit changed();
    kDebug() << "Hide Value: " << b;
}

void Edge::addDynamicProperty( QString property, QVariant value )
{
    this->setProperty( property.toUtf8(), value );
    if( value.isValid() )
    {
        DynamicPropertiesList::New()->addProperty( this, property );
    }
}

void Edge::removeDynamicProperty( QString property )
{
    addDynamicProperty( property.toUtf8(), QVariant::Invalid );
    DynamicPropertiesList::New()->removeProperty( this, property );
}
