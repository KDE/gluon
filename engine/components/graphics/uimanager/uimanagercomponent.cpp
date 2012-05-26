/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2011 Giulio Camuffo <giuliocamuffo@gmail.com>
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

#include "uimanagercomponent.h"

#include "uiasset.h"
#include "engineaccess.h"
#include "renderablescene.h"

#include "engine/gameobject.h"
#include "engine/asset.h"
#include "engine/game.h"

#include <core/messagehandler.h>
#include <graphics/engine.h>
#include <graphics/item.h>
#include <graphics/material.h>
#include <graphics/spritemesh.h>
#include <graphics/rendertarget.h>
#include <graphics/materialinstance.h>
#include <graphics/texture.h>

#include <QtDeclarative/QDeclarativeItem>
#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeExpression>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/qdeclarative.h>
#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValueIterator>

REGISTER_OBJECTTYPE( GluonEngine, UiManagerComponent )

using namespace GluonEngine;
using namespace GluonGraphics;

template <typename Tp>
QScriptValue scriptValueFromQObject( QScriptEngine* engine, Tp const& qobject )
{
    return engine->newQObject( qobject );
}

template <typename Tp>
void scriptValueToQObject( const QScriptValue& value, Tp& qobject )
{
    qobject = qobject_cast<Tp>( value.toQObject() );
}

template <typename Tp>
int qScriptRegisterQObjectMetaType( QScriptEngine* engine )
{
    return qScriptRegisterMetaType<Tp>( engine, scriptValueFromQObject, scriptValueToQObject );
}

class UiManagerComponent::UiManagerComponentPrivate
{
    public:
        UiManagerComponentPrivate( UiManagerComponent* component )
            : q( component )
            , scene( 0 )
            , ui( 0 )
            , updateFunction( 0 )
        {
        }

        void setupBindings( QScriptEngine* engine )
        {
            //FIXME: this code is duplicated with the scripting conponent.
            //It should be moved to a common place.

            engine->importExtension( "jsmoke.qtcore" );
            engine->importExtension( "jsmoke.qtgui" );
            engine->importExtension( "jsmoke.qtopengl" );

            qScriptRegisterQObjectMetaType<GameObject*>( engine );
            qScriptRegisterQObjectMetaType<GluonObject*>( engine );
            qScriptRegisterQObjectMetaType<Component*>( engine );
            qScriptRegisterQObjectMetaType<Asset*>( engine );
            qScriptRegisterQObjectMetaType<Scene*>( engine );
            qScriptRegisterQObjectMetaType<GameProject*>( engine );

            QScriptEngine::QObjectWrapOptions wrapOptions = QScriptEngine::AutoCreateDynamicProperties | QScriptEngine::ExcludeDeleteLater | QScriptEngine::PreferExistingWrapperObject;
            QScriptEngine::ValueOwnership ownership = QScriptEngine::QtOwnership;
            QScriptValue object = engine->globalObject();

            QScriptValue component = engine->newQObject( q, ownership, wrapOptions );
            object.setProperty( "Component", component );

            QScriptValue gameObj = engine->newQObject( q->gameObject(), ownership, wrapOptions );
            object.setProperty( "GameObject", gameObj );

            QScriptValue sceneObj = engine->newQObject( q->gameObject()->scene(), ownership, wrapOptions );
            object.setProperty( "Scene", sceneObj );

            QScriptValue gameProjectObj = engine->newQObject( GluonEngine::Game::instance()->gameProject(), ownership, wrapOptions );
            object.setProperty( "GameProject", gameProjectObj );

            QScriptValue game = engine->newQObject( GluonEngine::Game::instance(), ownership, wrapOptions );
            object.setProperty( "Game", game );

            QScriptValue messageHandler = engine->newQObject( GluonCore::MessageHandler::instance(), ownership, wrapOptions );
            object.setProperty( "MessageHandler", messageHandler );
        }

        void resizeQmlItem( const QRectF& rect )
        {
            if( ui )
            {
                QDeclarativeItem* item = ui->qmlItem();
                if( item )
                {
                    item->setWidth( rect.width() );
                    item->setHeight( rect.height() );
                }
            }
        }

        void reload()
        {
            if( ui )
            {
                QDeclarativeItem* item = ui->qmlItem();
                if( scene && item && item->scene() == scene )
                {
                    scene->removeItem( item );
                }
            }

            q->initialize();
        }

        UiManagerComponent* q;
        RenderableScene* scene;
        UiAsset* ui;
        QSizeF size;
        Entity* item;
        EngineAccess* engineAccess;
        QScriptEngine* scriptEngine;

        QScriptValue scriptItem;
        QScriptValue updateFunction;
};

UiManagerComponent::UiManagerComponent( QObject* parent )
    : Component( parent )
    , d( new UiManagerComponentPrivate( this ) )
{

}

UiManagerComponent::~UiManagerComponent()
{
    if( d->ui )
        d->ui->deref();

    delete d;
}

QString UiManagerComponent::category() const
{
    return QString( "Graphics Rendering" );
}

void UiManagerComponent::initialize()
{
    if( !d->scene )
    {
        d->scene = new RenderableScene( );
        connect( d->scene, SIGNAL(sceneRectChanged(QRectF)),
                 this, SLOT(resizeQmlItem(QRectF)) );
    }

    if( d->ui )
    {
        if( !d->ui->isLoaded() )
        {
            qmlRegisterType<GluonEngine::GameObject>( "org.kde.gluon", 1, 0, "GameObject" );
            qmlRegisterInterface<GluonEngine::GameObject>( "gameObject" );

            d->ui->load();
        }

        QDeclarativeEngine* engine = d->ui->engine();

        d->engineAccess = new EngineAccess( this );
        engine->rootContext()->setContextProperty( "__engineAccess", d->engineAccess );

        //Glorious hack:steal the engine
        QDeclarativeExpression* expr = new QDeclarativeExpression( engine->rootContext(), 0,
                "__engineAccess.setEngine( this )" );
        expr->evaluate();
        delete expr;

        d->ui->execute();

        QDeclarativeItem* item = d->ui->qmlItem();
        if( item )
        {
            d->scene->addItem( item );
            QRectF rect( d->scene->sceneRect() );
            item->setWidth( rect.width() );
            item->setHeight( rect.height() );

            d->scriptItem = d->scriptEngine->newQObject( item );
            d->updateFunction = d->scriptItem.property( "update" );
        }
    }
}

void UiManagerComponent::setScriptEngine( QScriptValue& value )
{
    d->scriptEngine = value.engine();

    QScriptValue originalGlobalObject = d->scriptEngine->globalObject();
    QScriptValue newGlobalObject = d->scriptEngine->newObject();

    QString eval = QLatin1String( "eval" );
    QString version = QLatin1String( "version" );

    QScriptValueIterator iter( originalGlobalObject );
    QVector<QString> names;
    QVector<QScriptValue> values;
    QVector<QScriptValue::PropertyFlags> flags;
    while( iter.hasNext() )
    {
        iter.next();

        QString name = iter.name();

        if( name == version )
        {
            continue;
        }

        if( name != eval )
        {
            names.append( name );
            values.append( iter.value() );
            flags.append( iter.flags() | QScriptValue::Undeletable );
        }
        newGlobalObject.setProperty( iter.scriptName(), iter.value() );
    }

    d->scriptEngine->setGlobalObject( newGlobalObject );

    d->setupBindings( d->scriptEngine );

    delete d->engineAccess;
    d->ui->engine()->rootContext()->setContextProperty( "__engineAccess", 0 );
}

void UiManagerComponent::start()
{

}

void UiManagerComponent::draw( int /* timeLapse */ )
{
    if( !d->scene || !d->ui || !d->ui->qmlItem() )
    {
        return;
    }

    d->scene->renderScene();
}

void UiManagerComponent::update( int elapsedMilliseconds )
{
    if( d->updateFunction.isFunction() )
    {
        d->updateFunction.call( d->scriptItem, QScriptValueList() << elapsedMilliseconds );
        if( d->scriptEngine->uncaughtException().isValid() )
        {
            // This needs to be mapped...
            debug( QString( "%1: %2" )
                   .arg( d->scriptEngine->uncaughtException().toString() )
                   .arg( d->scriptEngine->uncaughtExceptionBacktrace().join( " " ) ) );
            d->updateFunction = QScriptValue();
        }
    }
}

void UiManagerComponent::cleanup()
{
    if( !d->ui )
    {
        return;
    }

    QDeclarativeItem* item = d->ui->qmlItem();
    if( d->scene && item && item->scene() == d->scene )
    {
        d->scene->removeItem( item );
    }
    delete d->scene;
    d->scene = 0;
}

void UiManagerComponent::setUi( UiAsset* ui )
{
    if( ui == d->ui )
    {
        return;
    }

    if( d->ui )
        d->ui->deref();

    d->ui = ui;

    if( d->ui )
        d->ui->ref();

    connect( ui, SIGNAL(dataChanged()), this, SLOT(reload()) );
}

UiAsset* UiManagerComponent::ui() const
{
    return d->ui;
}

void UiManagerComponent::setSize( const QSizeF& size )
{
    d->size = size;
}

QSizeF UiManagerComponent::size() const
{
    return d->size;
}

Q_EXPORT_PLUGIN2( gluon_component_uimanager, GluonEngine::UiManagerComponent );

#include "uimanagercomponent.moc"
