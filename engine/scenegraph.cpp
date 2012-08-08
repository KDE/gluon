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
#include "scenegraphprivate.h"
#include "scenegraphobject.h"

#include "game.h"
#include "gameproject.h"
#include "component.h"

#include <core/gluonobject.h>
#include <core/gdlserializer.h>

#include <iostream>
#include <QMetaProperty>
#include <QDebug>

using namespace std;

using namespace GluonEngine;

// Pointer used for comparison
GluonEngine::SceneGraphObject* cobject;

SceneGraph::SceneGraph( bool ref ) 
    : p( new SceneGraphPrivate( this, ref ) )
{
    populate( p->root );
}

SceneGraph::SceneGraph( GluonEngine::GameObject* parent, bool ref )
    : p( new SceneGraphPrivate( this, parent, ref ) )
{
    populate( p->root );
}

SceneGraph::~SceneGraph()
{
    delete p;
}

void SceneGraph::populate( GluonEngine::SceneGraphObject* object )
{
    QList<GluonEngine::SceneGraphObject*> children;
    QList<GluonEngine::GameObject*> members;
    QHash<QString, QList<GluonEngine::GameObject*> > hash;
    for( int i = 0; i < object->gameObject()->childCount(); i++ )
        members.append( object->gameObject()->childGameObject( i ) );
    
    foreach( GluonEngine::GameObject* member, members )
    {
        QString tags = p->tags->tags( member->name() );
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
        GluonEngine::SceneGraphObject* group = new GluonEngine::SceneGraphObject();
        group->setGroupHead( true );
        group->setParent( object );
        group->setGroupName( key );
        QList<GluonEngine::SceneGraphObject*> childrenofgroup;
        foreach( GluonEngine::GameObject* member, hash.value( key ) )
        {
            GluonEngine::SceneGraphObject* child = new GluonEngine::SceneGraphObject();
            child->setParent( group );
            child->setGameObject( member );
            childrenofgroup.append( child );
            populate( child );
            members.removeOne( member );
        }
        group->addChildren( childrenofgroup );
        object->addChild( group );
    }
    
    foreach( GluonEngine::GameObject* member, members )
    {
        GluonEngine::SceneGraphObject* child = new GluonEngine::SceneGraphObject();
        child->setGameObject( member );
        child->setParent( object );
        children.append( child );
        populate( child );
    }
    
    object->addChildren( children );
}

GluonEngine::SceneGraphObject* SceneGraph::root()
{
    return p->root;
}

void SceneGraph::findChild( QString name )
{
    cobject = 0;
    findChild( root(), name );
}

void SceneGraph::findChild( SceneGraphObject* object, QString name )
{
    if( object->isGroupHead() )
    {
        if( object->groupName().compare( name ) == 0 )
        {
            cobject = object;
            return;
        }
    }
    else
    {
        if( object->gameObject()->name().compare( name ) == 0 )
        {
            cobject = object;
            return;
        }
    }
    foreach( GluonEngine::SceneGraphObject* obj, object->children() )
        findChild( obj, name );
}

void SceneGraph::baseObject( GluonEngine::SceneGraphObject* object )
{
    findChild( p->tags->baseName( object->gameObject()->name() ) );
}

void SceneGraph::compare( GluonEngine::SceneGraphObject* object )
{
    if( ! object->isGroupHead() )
    {
        p->refgraph->findChild( object->gameObject()->name() );
        if( ! cobject )
            p->refgraph->baseObject( object );
        if( ! cobject )
            object->diff = 0;
        else
        {
            object->setRefObject( cobject );
            object->diff = object->compare( cobject );
            object->modifyGameObject();
        }
    }
    foreach( GluonEngine::SceneGraphObject* obj, object->children() )
        compare( obj );
}

GluonCore::GluonObject* SceneGraph::toScene()
{
    GluonCore::GluonObject* scene = new GluonCore::GluonObject( GluonEngine::Game::instance()->gameProject()->fullyQualifiedName() );
    const char* refers = "refers";
    scene->setProperty( refers, GluonEngine::Game::instance()->currentScene()->absolutePath() );
    scene->addChild( root()->modifiedGameObject() );
    return scene;
}

void SceneGraph::setRefGraph( QUrl pathtoref )
{
    p->setRefGraph( pathtoref );
}

void SceneGraph::build( SceneGraphObject* object )
{
    if( ! object->isGroupHead() )
    {
        p->refgraph->findChild( object->gameObject()->name() );
        if( ! cobject )
            p->refgraph->baseObject( object );
        object->setRefObject( cobject );
        object->buildGameObject();
    }
    foreach( SceneGraphObject* obj, object->children() )
        build( obj );
}

GluonCore::GluonObject* SceneGraph::forSave()
{
    compare( root() );
    return toScene();
}

GluonEngine::GameObject* SceneGraph::forLoad()
{
    build( root() );
    return root()->gameObject();
}



#include "scenegraph.moc"