/* This file is part of Rocs,
     Copyright (C) 2008 by:
     Tomaz Canabrava <tomaz.canabrava@gmail.com>
     Ugo Sangiori <ugorox@gmail.com>
     Laszlo Papp <lpapp@kde.org>

     Rocs is free software; you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation; either version 2 of the License, or
     (at your option) any later version.

     Rocs is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.   See the
     GNU General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with Step; if not, write to the Free Software
     Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "NodeEditor.h"

#include "lib/abstractundocommand.h"
#include "lib/objectmanager.h"

// UI RELATED INCLUDES

#include "GraphVisualEditor.h"
#include "GraphScene.h"

// MODEL Related Includes
#include "model_GraphDocument.h"

// Graph Related Includes
#include "graphDocument.h"
#include "graph.h"

// Action Related Includes
#include "AbstractAction.h"
#include "AddNode.h"
#include "AddTypedNode.h"
#include "AddEdge.h"
#include "MoveNode.h"
#include "Select.h"
#include "DeleteAction.h"
#include "AlignAction.h"

#include <core/gluonobject.h>
#include <core/gdlserializer.h>

// KDE Related Includes
#include <KDE/KActionCollection>
#include <KDE/KIcon>
#include <KDE/KDebug>
#include <KDE/KLocalizedString>
#include <KDE/KPushButton>
#include <kstandarddirs.h>

#include <QtGui/QActionGroup>
#include <QtCore/QList>
#include <QtCore/QFile>
#include <QtCore/QDir>


NodeEditor::NodeEditor() :  QWidget()
{
    _tDocument = new    GraphDocument( "Untitled" );

    setupWidgets();
    setupActions();
    setupLists();

    setActiveGraphDocument( _tDocument );
    _graph = _tDocument->addGraph();
    setActiveGraph( _graph );
    _lastScene = "";
    _skipNextUpdate = false;
    _isGameObject = false;
    _isGameComponent = false;
    connect( GluonEngine::Game::instance(), SIGNAL(currentSceneChanged(GluonEngine::Scene*)), SLOT(readTheScene()) );
    connect( GluonCreator::HistoryManager::instance(), SIGNAL(historyChanged(const QUndoCommand*)), SLOT(updateNodesFromModel(const QUndoCommand*)) );
    connect( GluonCreator::ObjectManager::instance(), SIGNAL(newGameObject(GluonEngine::GameObject*)), SLOT(markAsGameObject()) );
    connect( GluonCreator::ObjectManager::instance(), SIGNAL(newComponent(GluonEngine::Component*)), SLOT(markAsGameComponent()) );
}

GraphDocument* NodeEditor::activeDocument() const
{
    return _tDocument;
}

void NodeEditor::eatChildren( GluonEngine::GameObject* trap )
{
    qsrand( trap->childCount() );
    int i = trap->childCount();
    while( i > 0 )
    {
        _graph->addNode( trap->childGameObject( i - 1 )->name(), QPointF( ( ( double( qrand() ) / RAND_MAX )*_graph->document()->width() ) + 10, ( ( double( qrand() ) / RAND_MAX )*_graph->document()->height() ) + 10 ), "base" );
        _graph->node( trap->childGameObject( i - 1 )->name() )->setProperty( "parentObject", trap->objectName() );
        foreach( const QString & s, _objectTypes )
        {
            foreach( GluonEngine::Component * c, trap->childGameObject( i - 1 )->findComponentsByType( s ) )
            {
                _graph->addNode( c->name(), QPointF( ( ( double( qrand() ) / RAND_MAX )*_graph->document()->width() ) + 10, ( ( double( qrand() ) / RAND_MAX )*_graph->document()->height() ) + 10 ), "others" );
                _graph->node( c->name() )->setValue( s );
                _graph->node( c->name() )->setValueHeader( "Type" );
                _graph->node( c->name() )->setProperty( "parentObject", c->parent()->objectName() );
                _graph->node( c->name() )->hideValue( true );
            }
        }
        if( trap->childGameObject( i - 1 )->childCount() > 0 )
        {
            eatChildren( trap->childGameObject( i - 1 ) );
        }
        i--;
    }
}

GluonCore::GluonObject* NodeEditor::surfNodesIntoTree()
{
    GluonCore::GluonObject* nodelist = new GluonCore::GluonObject( "plantaseedgrowatree" );
    foreach( Edge * e, _graph->edges() )
    {
        if( _graph->node( e->fromNode() )->in_edges().count() < 1 )
        {
            GluonCore::GluonObject* node = new GluonCore::GluonObject( e->fromNode(), nodelist );
            traceNodeGen( node );
        }

    }
    return nodelist;
}

void NodeEditor::traceNodeGen( GluonCore::GluonObject* n )
{
    foreach( Edge * e, _graph->node( n->objectName() )->out_edges() )
    {
        GluonCore::GluonObject* node = new GluonCore::GluonObject( e->toNode(), n );
        traceNodeGen( node );
    }
}

void NodeEditor::markAsGameObject()
{
    _isGameObject = true;
}

void NodeEditor::markAsGameComponent()
{
    _isGameComponent = true;
}

void NodeEditor::updateNodesFromModel( const QUndoCommand* cmd )
{
    if( _skipNextUpdate != false )
    {
        if( dynamic_cast<const GluonCreator::AbstractUndoCommand*>( cmd ) != NULL && dynamic_cast<const GluonCreator::AbstractUndoCommand*>( cmd )->commandName() == "NewObjectCommand" && ( _isGameObject || _isGameComponent ) )
        {
            if( dynamic_cast<const GluonCreator::AbstractUndoCommand*>( cmd )->commandDirection() == "redo" )
            {
                if( _isGameObject )
                {
                    _graph->addNode( dynamic_cast<const GluonCreator::AbstractUndoCommand*>( cmd )->object()->objectName(), QPointF( ( ( double( qrand() ) / RAND_MAX )*_graph->document()->width() ) + 10, ( ( double( qrand() ) / RAND_MAX )*_graph->document()->height() ) + 10 ), "base" );
                    _graph->node( dynamic_cast<const GluonCreator::AbstractUndoCommand*>( cmd )->object()->objectName() )->setProperty( "parentObject", dynamic_cast<const GluonCreator::AbstractUndoCommand*>( cmd )->object()->parent()->objectName() );
                }
                if( _isGameComponent )
                {
                    _graph->addNode( dynamic_cast<const GluonCreator::AbstractUndoCommand*>( cmd )->object()->objectName(), QPointF( ( ( double( qrand() ) / RAND_MAX )*_graph->document()->width() ) + 10, ( ( double( qrand() ) / RAND_MAX )*_graph->document()->height() ) + 10 ), "others" );
                    _graph->node( dynamic_cast<const GluonCreator::AbstractUndoCommand*>( cmd )->object()->objectName() )->setValue( QString( dynamic_cast<GluonEngine::Component*>( dynamic_cast<const GluonCreator::AbstractUndoCommand*>( cmd )->object() )->metaObject()->className() ) );
                    _graph->node( dynamic_cast<const GluonCreator::AbstractUndoCommand*>( cmd )->object()->objectName() )->setValueHeader( "Type" );
                    _graph->node( dynamic_cast<const GluonCreator::AbstractUndoCommand*>( cmd )->object()->objectName() )->setProperty( "parentObject", dynamic_cast<const GluonCreator::AbstractUndoCommand*>( cmd )->object()->parent()->objectName() );
                    _graph->node( dynamic_cast<const GluonCreator::AbstractUndoCommand*>( cmd )->object()->objectName() )->hideValue( true );
                }
            }
            else
            {
                _graph->remove( _graph->node( dynamic_cast<const GluonCreator::AbstractUndoCommand*>( cmd )->object()->objectName() ) );
            }
        }
        else if( dynamic_cast<const GluonCreator::AbstractUndoCommand*>( cmd ) != NULL && dynamic_cast<const GluonCreator::AbstractUndoCommand*>( cmd )->commandName() == "DeleteObjectCommand" )
        {
            if( dynamic_cast<const GluonCreator::AbstractUndoCommand*>( cmd )->commandDirection() == "redo" )
            {
                _graph->remove( _graph->node( dynamic_cast<const GluonCreator::AbstractUndoCommand*>( cmd )->object()->objectName() ) );
            }
            else
            {
                if( dynamic_cast<GluonEngine::GameObject*>( dynamic_cast<const GluonCreator::AbstractUndoCommand*>( cmd )->object() ) != NULL )
                {
                    _graph->addNode( dynamic_cast<const GluonCreator::AbstractUndoCommand*>( cmd )->object()->objectName(), QPointF( ( ( double( qrand() ) / RAND_MAX )*_graph->document()->width() ) + 10, ( ( double( qrand() ) / RAND_MAX )*_graph->document()->height() ) + 10 ), "base" );
                    _graph->node( dynamic_cast<const GluonCreator::AbstractUndoCommand*>( cmd )->object()->objectName() )->setProperty( "parentObject", dynamic_cast<const GluonCreator::AbstractUndoCommand*>( cmd )->object()->parent()->objectName() );
                }
                if( dynamic_cast<GluonEngine::Component*>( dynamic_cast<const GluonCreator::AbstractUndoCommand*>( cmd )->object() ) != NULL )
                {
                    _graph->addNode( dynamic_cast<const GluonCreator::AbstractUndoCommand*>( cmd )->object()->objectName(), QPointF( ( ( double( qrand() ) / RAND_MAX )*_graph->document()->width() ) + 10, ( ( double( qrand() ) / RAND_MAX )*_graph->document()->height() ) + 10 ), "others" );
                    _graph->node( dynamic_cast<const GluonCreator::AbstractUndoCommand*>( cmd )->object()->objectName() )->setValue( QString( dynamic_cast<GluonEngine::Component*>( dynamic_cast<const GluonCreator::AbstractUndoCommand*>( cmd )->object() )->metaObject()->className() ) );
                    _graph->node( dynamic_cast<const GluonCreator::AbstractUndoCommand*>( cmd )->object()->objectName() )->setValueHeader( "Type" );
                    _graph->node( dynamic_cast<const GluonCreator::AbstractUndoCommand*>( cmd )->object()->objectName() )->setProperty( "parentObject", dynamic_cast<const GluonCreator::AbstractUndoCommand*>( cmd )->object()->parent()->objectName() );
                    _graph->node( dynamic_cast<const GluonCreator::AbstractUndoCommand*>( cmd )->object()->objectName() )->hideValue( true );
                }
            }
        }
    }
    _skipNextUpdate = false;
    _isGameObject = false;
    _isGameComponent = false;
}

void NodeEditor::deleteThisSceneObject( QString objectName, QString objectParent )
{
    //not sure if this whole piece is correctly identifing child object.
    GluonEngine::GameObject* parent;
    if( GluonEngine::Game::instance()->getFromScene( objectParent ) != NULL )
    {
        parent = GluonEngine::Game::instance()->getFromScene( objectParent );
    }
    else
    {
        parent = GluonEngine::Game::instance()->currentScene()->sceneContents();
    }
    if( parent->child( objectName ) != NULL )
    {
        _skipNextUpdate = true;
        if( qobject_cast<GluonEngine::GameObject*>( parent->findItemByName( objectName ) ) != NULL ) GluonCreator::ObjectManager::instance()->deleteGameObject( qobject_cast<GluonEngine::GameObject*>( parent->findItemByName( objectName ) ) );
        if( qobject_cast<GluonEngine::Component*>( parent->findItemByName( objectName ) ) != NULL ) parent->removeChild( parent->findItemByName( objectName ) );
    }
}

void NodeEditor::exportFromThisNode( GluonCore::GluonObject* o, QTextStream* file )
{
    if( _graph->node( o->objectName() )->type() == "if" )
    {
        *file << "if(" + _graph->node( o->objectName() )->value().toString() + ")\n{\n";
        foreach( Edge * e, _graph->node( o->objectName() )->out_edges() )
        {
            if( e->fromConnector() == "true" )
            {
                foreach( QObject * obj, o->children() )
                {
                    if( e->toNode() == qobject_cast<GluonCore::GluonObject*>( obj )->objectName() )  exportFromThisNode( qobject_cast<GluonCore::GluonObject*>( obj ), file );
                }
            }
            else if( e->fromConnector() == "false" )
            {
                *file << "}\n else{\n";
                foreach( QObject * obj, o->children() )
                {
                    if( e->toNode() == qobject_cast<GluonCore::GluonObject*>( obj )->objectName() )  exportFromThisNode( qobject_cast<GluonCore::GluonObject*>( obj ), file );
                }
            }
        }
        *file << "}\n";
    }
    //this section really needs to rely on a list of components and thier functions in order to make proper javascript entry points.
    else if( _graph->node( o->objectName() )->type() == "base" )
    {
        *file << "function " + o->objectName() + "start()\n{\n";
        foreach( QObject * obj, o->children() )
        {
            if( _graph->node( o->objectName() )->out_edges().first()->toNode() == qobject_cast<GluonCore::GluonObject*>( obj )->objectName() )  exportFromThisNode( qobject_cast<GluonCore::GluonObject*>( obj ), file );
        }
        *file << "}\n";
    }
    else
    {
        *file << o->objectName() + "();\n";
        foreach( QObject * obj, o->children() )
        {
            if( _graph->node( o->objectName() )->out_edges().first()->toNode() == qobject_cast<GluonCore::GluonObject*>( obj )->objectName() )  exportFromThisNode( qobject_cast<GluonCore::GluonObject*>( obj ), file );
        }
    }
}

void NodeEditor::exportCode( bool /* checked */ )
{
    if( GluonEngine::Game::instance()->gameProject()->findGlobalItemByName( "vn-" + GluonEngine::Game::instance()->currentScene()->name() ) == NULL )
    {
        GluonEngine::Asset* script = new GluonEngine::Asset();
        script->setName( "vn-" + GluonEngine::Game::instance()->currentScene()->name() );
        script->setFile( QString( "Assets/" ) + script->name() + ".js" );
        GluonEngine::Game::instance()->gameProject()->addChild( script );
        QFile codeFile( script->absolutePath().toLocalFile() );
        if( !codeFile.open( QIODevice::WriteOnly ) ) return;
        QTextStream filewrite( &codeFile );
        foreach( QObject * o, surfNodesIntoTree()->children() )
        {
            exportFromThisNode( qobject_cast<GluonCore::GluonObject*>( o ), &filewrite );
        }
        codeFile.close();
    }
    else
    {
        GluonEngine::Asset* scriptE = GluonEngine::Game::instance()->gameProject()->findChild<GluonEngine::Asset*>( "vn-" + GluonEngine::Game::instance()->currentScene()->name() );
        if( !scriptE ) return;
        QFile codeFileE( scriptE->absolutePath().toLocalFile() );
        if( !codeFileE.open( QIODevice::WriteOnly ) ) return;
        QTextStream filewriteE( &codeFileE );
        foreach( QObject * o, surfNodesIntoTree()->children() )
        {
            exportFromThisNode( qobject_cast<GluonCore::GluonObject*>( o ), &filewriteE );
        }
        codeFileE.close();
    }
}

void NodeEditor::saveStateGDL()
{
    if( !_skipSaving )
    {
        QList<GluonCore::GluonObject*> objects;
        GluonCore::GluonObject* nodelist = new GluonCore::GluonObject( "Nodes" );
        GluonCore::GluonObject* edgelist = new GluonCore::GluonObject( "Edges" );
        objects.append( nodelist );
        objects.append( edgelist );
        foreach( Node * n, _graph->nodes() )
        {
            GluonCore::GluonObject* node = new GluonCore::GluonObject( n->name(), nodelist );
            node->setProperty( "NodeType", n->type() );
            node->setProperty( "NodeValue", n->value() );
            node->setProperty( "NodeValueHeader", n->valueHeader() );
            node->setProperty( "parentObject", n->property( "parentObject" ) );
            node->setProperty( "Nodex", n->x() );
            node->setProperty( "Nodey", n->y() );
        }
        foreach( Edge * e, _graph->edges() )
        {
            GluonCore::GluonObject* edge = new GluonCore::GluonObject( e->name(), edgelist );
            edge->setProperty( "value", e->value() );
            edge->setProperty( "fromConnector", e->fromConnector() );
            edge->setProperty( "toConnector", e->toConnector() );
            edge->setProperty( "fromNode", e->fromNode() );
            edge->setProperty( "toNode", e->toNode() );
        }

        if( !QDir( QFileInfo( GluonEngine::Game::instance()->gameProject()->filename().toLocalFile() ).dir().absolutePath() + "/Assets" ).exists() ) QDir( QFileInfo( GluonEngine::Game::instance()->gameProject()->filename().toLocalFile() ).dir().absolutePath() ).mkdir( "Assets" );

        QString file = QFileInfo( GluonEngine::Game::instance()->gameProject()->filename().toLocalFile() ).dir().absolutePath() + "/Assets/visualnodes-" + GluonEngine::Game::instance()->currentScene()->name() + ".gdl";

        GluonCore::GDLSerializer::instance()->write( QUrl( file ), objects );
    }
}

void NodeEditor::loadStateGDL()
{
    QList<GluonCore::GluonObject*> rootlist;
    if( !GluonCore::GDLSerializer::instance()->read( QFileInfo( GluonEngine::Game::instance()->gameProject()->filename().toLocalFile() ).dir().absolutePath() + "/Assets/visualnodes-" + GluonEngine::Game::instance()->currentScene()->name() + ".gdl", rootlist ) )
        return;

    foreach( QObject * n, rootlist.first()->children() )
    {
        _graph->addNode( n->objectName(), QPoint( n->property( "Nodex" ).toInt(), n->property( "Nodey" ).toInt() ), n->property( "NodeType" ).toString() );
        _graph->node( n->objectName() )->setValue( n->property( "NodeValue" ).toString() );
        _graph->node( n->objectName() )->setValueHeader( n->property( "NodeValueHeader" ).toString() );
        _graph->node( n->objectName() )->setProperty( "parentObject", n->parent()->objectName() );
        if( _graph->node( n->objectName() )->valueHeader() != "Value" )_graph->node( n->objectName() )->hideValue( true );
    }
    foreach( QObject * e, rootlist.last()->children() )
    {
        _graph->addEdge( _graph->node( e->property( "fromNode" ).toString() ), _graph->node( e->property( "toNode" ).toString() ), qobject_cast<NodeItem*>( _graph->node( e->property( "fromNode" ).toString() )->nodeItem() )->connectors().value( e->property( "fromConnector" ).toString() ), qobject_cast<NodeItem*>( _graph->node( e->property( "toNode" ).toString() )->nodeItem() )->connectors().value( e->property( "toConnector" ).toString() ) );
    }
}

void NodeEditor::readTheScene()
{
    QDir path = QDir( QFileInfo( GluonEngine::Game::instance()->gameProject()->filename().toLocalFile() ).dir().absolutePath() + "/Assets" );
    if( GluonEngine::Game::instance()->currentScene()->name() == _lastScene ) return;
    _skipSaving = true;
    foreach( Edge * e, _graph->edges() )
    {
        e->remove();
    }
    foreach( Node * n, _graph->nodes() )
    {
        n->remove();
    }
    _skipSaving = false;
    if( path.exists() && QFileInfo( path.absolutePath() + "/visualnodes-" + GluonEngine::Game::instance()->currentScene()->name() + ".gdl" ).exists() )
    {
        loadStateGDL();
    }
    else
    {
        eatChildren( GluonEngine::Game::instance()->currentScene()->sceneContents() );
    }
    _lastScene = GluonEngine::Game::instance()->currentScene()->name();
}

void NodeEditor::setupWidgets()
{
    _layout = new QVBoxLayout( this );
    _graphVisualEditor = new GraphVisualEditor( this );
    _actionButtons = new KToolBar( _graphVisualEditor, false );
    _widgetType = new KComboBox( _actionButtons );
    _exportCode = new KPushButton( _actionButtons );
    _exportCode->setText( "Export Code" );
    _exportCode->setIcon( KIcon( "arrow-up-double" ) );
    //_exportCode->setEnabled(false);
    addCustomTypes( _widgetType );
    _layout->addWidget( _actionButtons );
    _layout->addWidget( _graphVisualEditor );
}

void NodeEditor::setupLists()
{
    QHash<QString, const QMetaObject*> objectTypes = GluonCore::GluonObjectFactory::instance()->objectTypes();
    foreach( const QMetaObject * obj, objectTypes )
    {
        GluonEngine::Component* comp = qobject_cast<GluonEngine::Component*>( obj->newInstance() );
        if( comp )
        {
            _objectTypes.append( objectTypes.key( obj ) );
        }
    }
}

void NodeEditor::addCustomTypes( KComboBox* bigList )
{
    QList<GluonCore::GluonObject*> noderootlist;
    if( !GluonCore::GDLSerializer::instance()->read( KGlobal::dirs()->locate( "data", "nodetypes.gdl" ), noderootlist ) )
        return;

    QMap<QString, QVariant> propertlist;
    foreach( QObject * n, noderootlist.first()->children() )
    {
        propertlist.clear();
        foreach( const QByteArray & ba, n->dynamicPropertyNames() )
        {
            propertlist.insert( QString( ba.data() ), n->property( ba.data() ) );
        }
        bigList->addItem( qobject_cast<GluonCore::GluonObject*>( n )->name(), propertlist );
    }
}

void NodeEditor::setupActions()
{
    GraphScene* gc = _graphVisualEditor->scene();
    ac = new KActionCollection( this );
    QActionGroup* g = new QActionGroup( this );
    _actionButtons->addAction( g->addAction( ac->addAction( "add_typed_node", new AddTypedNodeAction( gc, this ) ) ) );
    _widgetTypeBar = _actionButtons->addWidget( _widgetType );
    _actionButtons->addAction( g->addAction( ac->addAction( "move_node", new MoveNodeAction( gc, this ) ) ) );
    _actionButtons->addAction( g->addAction( ac->addAction( "delete_action", new DeleteAction( gc, this ) ) ) );
    _actionButtons->addWidget( _exportCode );
    _widgetTypeBar->setVisible( false );
    qobject_cast<AddTypedNodeAction*>( ac->action( "add_typed_node" ) )->widgetTypeChanged( _widgetType->currentText() );
    connect( ac->action( "add_typed_node" ), SIGNAL(changed()), this, SLOT(toggleWidgetTypeShown()) );
    connect( ac->action( "delete_action" ), SIGNAL(deleteSceneItem(QString,QString)), this, SLOT(deleteThisSceneObject(QString,QString)) );
    connect( _widgetType, SIGNAL(currentIndexChanged(QString)), ac->action( "add_typed_node" ), SLOT(widgetTypeChanged(QString)) );
    connect( _exportCode, SIGNAL(clicked(bool)), this, SLOT(exportCode(bool)) );
    ac->action( "move_node" )->trigger();
}

void NodeEditor::toggleWidgetTypeShown()
{
    if( _widgetTypeBar->isVisible() )
    {
        _widgetTypeBar->setVisible( false );
    }
    else
    {
        _widgetTypeBar->setVisible( true );
    }
}

void NodeEditor::setActiveGraphDocument( GraphDocument* d )
{
    foreach( QAction * action, ac->actions() )
    {
        if( AbstractAction* absAction = qobject_cast<AbstractAction*> ( action ) )
        {
            absAction->setActiveGraphDocument( d );
        }
    }

    _graphVisualEditor->setActiveGraphDocument( d );
}

void NodeEditor::setActiveGraph( Graph* g )
{
    disconnect( SIGNAL(saveStateGDL()) );
    foreach( QAction * action, ac->actions() )
    {
        if( AbstractAction* absAction = qobject_cast<AbstractAction*> ( action ) )
            absAction->setActiveGraph( g );
    }
    _graphVisualEditor->setActiveGraph( g );
    _graph = g;
    g->setKCB( _widgetType );
    connect( g, SIGNAL(changed()), SLOT(saveStateGDL()) );
}

Graph* NodeEditor::graph() const
{
    return _graph;
}

GraphScene* NodeEditor::scene() const
{
    return _graphVisualEditor->scene();
}
