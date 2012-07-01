/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2012 Vinay S Rao <sr.vinay@gmail.com>
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "scenegraph.h"
#include "scenegraphobject.h"

#include "game.h"
#include "gameproject.h"
#include <core/gluonobject.h>

#include <iostream>
#include <QMetaProperty>

using namespace std;

using namespace GluonEngine;

SceneGraph::SceneGraph()
{
    this->root = new SceneGraphObject();
    this->root->setMember( GluonEngine::Game::instance()->currentScene()->sceneContents() );
    this->tags = GluonEngine::Game::instance()->gameProject()->getTagObject();
    populate( this->root, 0 );
}

SceneGraph::SceneGraph( GluonEngine::GameObject* parent )
{
    this->root = new SceneGraphObject();
    this->root->setMember( parent );
    this->tags = GluonEngine::Game::instance()->gameProject()->getTagObject();
    populate( this->root, 0 );
}

SceneGraph::~SceneGraph()
{
}

void SceneGraph::populate( SceneGraphObject* object, int level )
{
    QList<SceneGraphObject*> children;
    QList<GluonEngine::GameObject*> members;
    QHash<QString, QList<GluonEngine::GameObject*> > hash;
    for( int i = 0; i < object->getMember()->childCount(); i++ )
        members.append( object->getMember()->childGameObject( i ) );
    foreach( GluonEngine::GameObject* member, members )
    {
        QString tags = this->tags->getTags( member->name() );
        if( tags.isEmpty() )
            continue;
        QList<GluonEngine::GameObject*> list;
        if( hash.contains( tags ) )
            list = hash.value( tags );
        list.append( member );
        hash.insert( tags, list );
    }
    foreach( QString key, hash.keys() )
    {
        SceneGraphObject* group = new SceneGraphObject();
        group->setGroupHead( true );
        group->setParent( object );
        group->setGroupName( key );
        group->setLevel( level );
        QList<GluonEngine::SceneGraphObject*> childrenofgroup;
        foreach( GluonEngine::GameObject* member, hash.value( key ) )
        {
            SceneGraphObject* child = new SceneGraphObject();
            child->setParent( group );
            child->setLevel( level + 1 );
            child->setMember( member );
            childrenofgroup.append( child );
            populate( child, level + 2 );
            members.removeOne( member );
        }
        group->addChildren( childrenofgroup );
        object->addChild( group );
    }
    foreach( GluonEngine::GameObject* member, members )
    {
        SceneGraphObject* child = new SceneGraphObject();
        child->setMember( member );
        child->setParent( object );
        child->setLevel( level );
        children.append( child );
        populate( child, level + 1 );
    }
    object->addChildren( children );
}

void SceneGraph::debugprint( SceneGraphObject* object, int level )
{
    for( int i = 0; i < level; i++ )
        cout << "  ";
    QString name;
    if( object->isGroupHead() )
        name = object->getGroupName();
    else
        name = object->getMember()->name();
    cout << name.toUtf8().constData() << endl;
    foreach( SceneGraphObject *child, object->getChildren() )
        debugprint( child, level + 1 );
    cout << "  ";
}

void SceneGraph::debugprint( SceneGraphObject* object )
{
    debugprint( object, 0 );
}


SceneGraphObject* SceneGraph::getRoot()
{
    return this->root;
}

SceneGraphObject* SceneGraph::findChild( QString name )
{
    return findChild( this->root, name );
}

SceneGraphObject* SceneGraph::findChild( SceneGraphObject* object, QString name )
{
    if( object->isGroupHead() )
        if( object->getGroupName().compare( name ) == 0 )
            return object;
    else
        if( object->getMember()->name().compare( name ) == 0 )
            return object;
    foreach( GluonEngine::SceneGraphObject* obj, object->getChildren() )
        findChild( obj, name );
    return 0;
}

SceneGraphObject* SceneGraph::getBaseObject( GluonEngine::SceneGraphObject* object )
{
    return findChild( this->tags->getBaseName( object->getMember()->name() ) );
}

void SceneGraph::compare( GluonEngine::SceneGraphObject* object )
{
    GluonEngine::SceneGraphObject *cobject = this->refgraph->findChild( object->getMember()->name() );
    if( cobject == 0 )
        cobject = this->refgraph->getBaseObject( object );
    object->diff = object->compare( cobject );
    foreach( GluonEngine::SceneGraphObject* obj, object->getChildren() )
        compare( obj );
}

void SceneGraph::compare()
{
    compare( this->root );
}

#include "scenegraph.moc"