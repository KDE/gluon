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

#include <core/gluonobject.h>
#include <core/gdlserializer.h>

#include <iostream>

using namespace std;

using namespace GluonEngine;

// Pointer used for comparison
GluonEngine::SceneGraphObject* cobject;

SceneGraph::SceneGraph( bool ref ) 
    : p( new SceneGraphPrivate( this, ref ) )
{
    initHelper( ref );
}

SceneGraph::SceneGraph( GluonEngine::GameObject* parent, bool ref )
    : p( new SceneGraphPrivate( this, parent, ref ) )
{
    initHelper( ref );
}

void SceneGraph::initHelper( bool ref )
{
    populate( p->root , 0 );
    if( !ref )
        compare();
}

SceneGraph::~SceneGraph()
{
}

void SceneGraph::populate( GluonEngine::SceneGraphObject* object, int level )
{
    QList<GluonEngine::SceneGraphObject*> children;
    QList<GluonEngine::GameObject*> members;
    QHash<QString, QList<GluonEngine::GameObject*> > hash;
    for( int i = 0; i < object->getMember()->childCount(); i++ )
        members.append( object->getMember()->childGameObject( i ) );
    foreach( GluonEngine::GameObject* member, members )
    {
        QString tags = p->tags->getTags( member->name() );
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
        group->setLevel( level );
        QList<GluonEngine::SceneGraphObject*> childrenofgroup;
        foreach( GluonEngine::GameObject* member, hash.value( key ) )
        {
            GluonEngine::SceneGraphObject* child = new GluonEngine::SceneGraphObject();
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
        GluonEngine::SceneGraphObject* child = new GluonEngine::SceneGraphObject();
        child->setMember( member );
        child->setParent( object );
        child->setLevel( level );
        children.append( child );
        populate( child, level + 1 );
    }
    object->addChildren( children );
}

void SceneGraph::debugprint( GluonEngine::SceneGraphObject* object, int level )
{
    for( int i = 0; i < level; i++ )
        cout << "  ";
    QString name;
    if( object->isGroupHead() )
        name = object->getGroupName();
    else
        name = object->getMember()->name();
    cout << name.toUtf8().constData() << endl;
    foreach( GluonEngine::SceneGraphObject *child, object->getChildren() )
        debugprint( child, level + 1 );
    cout << "  ";
}

void SceneGraph::debugprint( GluonEngine::SceneGraphObject* object )
{
    debugprint( object, 0 );
}


GluonEngine::SceneGraphObject* SceneGraph::getRoot()
{
    return p->root;
}

void SceneGraph::findChild( QString name )
{
    cobject = 0;
    findChild( getRoot(), name );
}

void SceneGraph::findChild( SceneGraphObject* object, QString name )
{
    if( object->isGroupHead() )
    {
        if( object->getGroupName().compare( name ) == 0 )
        {
            cobject = object;
            return;
        }
    }
    else
    {
        if( object->getMember()->name().compare( name ) == 0 )
        {
            cobject = object;
            return;
        }
    }
    foreach( GluonEngine::SceneGraphObject* obj, object->getChildren() )
        findChild( obj, name );
}

void SceneGraph::getBaseObject( GluonEngine::SceneGraphObject* object )
{
    findChild( p->tags->getBaseName( object->getMember()->name() ) );
}

void SceneGraph::compare( GluonEngine::SceneGraphObject* object )
{
    if( ! object->isGroupHead() )
    {
        p->refgraph->findChild( object->getMember()->name() );
        if( ! cobject )
            p->refgraph->getBaseObject( object );
        if( ! cobject )
            object->diff = 0;
        else
        {
            object->setRefObject( cobject );
            object->diff = ( object->compare( cobject ) == 0 ? 0 : 1 );
            object->modifyMember();
        }
    }
    foreach( GluonEngine::SceneGraphObject* obj, object->getChildren() )
        compare( obj );
}

void SceneGraph::compare()
{
    compare( getRoot() );
}

GluonCore::GluonObject* SceneGraph::toScene()
{
    GluonCore::GluonObject* scene = new GluonCore::GluonObject( GluonEngine::Game::instance()->gameProject()->fullyQualifiedName() );
    const char* refers = "refers";
    scene->setProperty( refers, GluonEngine::Game::instance()->currentScene()->absolutePath() );
    scene->addChild( getRoot()->getModifiedMember() );
    return scene;
}


#include "scenegraph.moc"