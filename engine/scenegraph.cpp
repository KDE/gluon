#include "scenegraph.h"
#include "scenegraphobject.h"
#include "game.h"

#include <core/gluonobject.h>
#include <iostream>
#include <QMetaProperty>

using namespace std;

using namespace GluonEngine;

SceneGraph::SceneGraph()
{
    this->root = new SceneGraphObject();
    this->root->setMember( GluonEngine::Game::instance()->currentScene()->sceneContents() );
    populate( this->root, 0 );
}

SceneGraph::SceneGraph( GluonEngine::GameObject* parent )
{
    this->root = new SceneGraphObject();
    this->root->setMember( parent );
    populate( this->root, 0 );
}

SceneGraph::~SceneGraph()
{
}

void SceneGraph::populate( SceneGraphObject* object, int level )
{
    QList<SceneGraphObject*> children;
<<<<<<< HEAD
    GluonEngine::GameObject* child;
    for( int i = 0; i < object->getMember()->childCount(); i++ )
    {
        child = object->getMember()->childGameObject( i );
        SceneGraphObject *newobject = new SceneGraphObject;
=======
    foreach( QObject* childm, object->getMember()->children() )
    {
        GluonEngine::GameObject* child = qobject_cast< GluonEngine::GameObject* >( childm );
        SceneGraphObject *newobject = new SceneGraphObject();
>>>>>>> 876b9a7d8af3372fe4e3ddaf4a61eaaf3cf4e599
        newobject->setParent( object );
        newobject->setLevel( level + 1 );
        newobject->setMember( child );
        children.append( newobject );
        populate( newobject, level + 1);
    }
    object->addChildren( children );
}

void SceneGraph::debugprint( SceneGraphObject* object, int level )
{
    for( int i = 0; i < level; i++ )
<<<<<<< HEAD
        cout << "  ";
    cout << object->getMember()->name().toUtf8().constData() << endl;
    foreach( SceneGraphObject *child, object->getChildren() )
        debugprint( child, level + 1 );
    cout << "  ";
=======
        cout << ' ';
    QMetaProperty property = object->getMember()->metaObject()->property( 0 );
    cout << property.read( object->getMember() ).toString().toUtf8().constData() << ' ';
    foreach( SceneGraphObject *child, object->getChildren() )
        debugprint( child, level + 1 );
    cout << endl;
>>>>>>> 876b9a7d8af3372fe4e3ddaf4a61eaaf3cf4e599
}

void SceneGraph::debugprint(SceneGraphObject* object)
{
    debugprint( object, 0 );
}


SceneGraphObject* SceneGraph::getRoot()
{
    return this->root;
}

#include "scenegraph.moc"