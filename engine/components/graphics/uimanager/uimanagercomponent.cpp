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

#include <core/debughelper.h>
#include <graphics/item.h>
#include <graphics/engine.h>
#include <graphics/item.h>
#include <graphics/material.h>
#include <graphics/mesh.h>
#include <graphics/rendertarget.h>
#include <graphics/materialinstance.h>
#include <engine/gameobject.h>
#include <engine/asset.h>

#include <QtCore/QMimeData>
#include <QtCore/QVariant>
#include <QtGui/QMatrix4x4>
#include <QtGui/QColor>
#include <QtGui/QGraphicsView>
#include <QtGui/QGraphicsScene>
#include <QtGui/QPixmap>
#include <QtDeclarative/QDeclarativeItem>
#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeExpression>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/qdeclarative.h>
#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValueIterator>
#include <texture.h>
#include <game.h>

#include "uiasset.h"
#include "engineaccess.h"
#include "renderablescene.h"

REGISTER_OBJECTTYPE( GluonEngine, UiManagerComponent )

using namespace GluonEngine;
using namespace GluonGraphics;

template <typename Tp>
QScriptValue scriptValueFromQObject( QScriptEngine *engine, Tp const& qobject)
{
    return engine->newQObject( qobject );
}

template <typename Tp>
void scriptValueToQObject(const QScriptValue &value, Tp &qobject)
{
    qobject = qobject_cast<Tp>( value.toQObject() );
}

template <typename Tp>
int qScriptRegisterQObjectMetaType( QScriptEngine *engine )
{
    return qScriptRegisterMetaType<Tp>( engine, scriptValueFromQObject, scriptValueToQObject );
}

class UiManagerComponent::UiManagerComponentPrivate
{
    public:
        UiManagerComponentPrivate( UiManagerComponent *component )
            : q(component)
            , scene(0)
            , ui(0)
            , updateFunction(0)
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
        }

        void resizeQmlItem( const QRectF& rect )
        {
            if ( ui )
            {
                QDeclarativeItem* item = ui->qmlItem();
                if( item )
                {
                    item->setWidth( rect.width() );
                    item->setHeight( rect.height() );
                }
            }
        }

        UiManagerComponent* q;
        RenderableScene* scene;
        UiAsset *ui;
        QSizeF size;
        Item *item;
        EngineAccess* engineAccess;

        QDeclarativeExpression *updateFunction;
};

UiManagerComponent::UiManagerComponent( QObject* parent )
    : Component( parent )
    , d( new UiManagerComponentPrivate( this ) )
{

}

UiManagerComponent::UiManagerComponent( const UiManagerComponent& other )
    : Component( other )
    , d( other.d )
{
}

UiManagerComponent::~UiManagerComponent()
{
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
        d->scene = new RenderableScene( this );
        connect( d->scene, SIGNAL( sceneRectChanged( const QRectF& ) ),
                 this, SLOT( resizeQmlItem( const QRectF& ) ) );
    }

    if( d->ui && !d->ui->isLoaded() )
    {
        qmlRegisterType<GluonEngine::GameObject>("org.kde.gluon", 1, 0, "GameObject" );
        qmlRegisterInterface<GluonEngine::GameObject>("gameObject");

        d->ui->load();

        QDeclarativeEngine* engine = d->ui->engine();

        d->engineAccess = new EngineAccess(this);
        engine->rootContext()->setContextProperty( "__engineAccess", d->engineAccess );

        //Glorious hack:steal the engine
        QDeclarativeExpression *expr = new QDeclarativeExpression( engine->rootContext(), 0,
                                                                   "__engineAccess.setEngine( this )" );
        expr->evaluate();
        delete expr;
    }

    if( d->ui && d->ui->isLoaded() )
    {
        d->ui->execute();

        QDeclarativeItem* item = d->ui->qmlItem();
        if( item )
        {
            d->scene->addItem( item );

            d->updateFunction = new QDeclarativeExpression( d->ui->engine()->rootContext(),
                                                            item, "update()" );
        }
    }
}

void UiManagerComponent::setScriptEngine( QScriptValue &value )
{
    QScriptEngine* engine = value.engine();

    QScriptValue originalGlobalObject = engine->globalObject();
    QScriptValue newGlobalObject = engine->newObject();

    QString eval = QLatin1String( "eval" );
    QString version = QLatin1String( "version" );

    QScriptValueIterator iter( originalGlobalObject );
    QVector<QString> names;
    QVector<QScriptValue> values;
    QVector<QScriptValue::PropertyFlags> flags;
    while ( iter.hasNext() )
    {
        iter.next();

        QString name = iter.name();

        if ( name == version )
        {
            continue;
        }

        if ( name != eval )
        {
            names.append( name );
            values.append( iter.value() );
            flags.append( iter.flags() | QScriptValue::Undeletable );
        }
        newGlobalObject.setProperty( iter.scriptName(), iter.value() );
    }

    engine->setGlobalObject( newGlobalObject );

    d->setupBindings( engine );

    delete d->engineAccess;
    d->ui->engine()->rootContext()->setContextProperty( "__engineAccess", 0 );
}

void UiManagerComponent::start()
{

}

void UiManagerComponent::draw( int timeLapse )
{
    Q_UNUSED( timeLapse )

    if( !d->scene || !d->ui || !d->ui->qmlItem() )
    {
        return;
    }

    d->scene->renderScene();
}

void UiManagerComponent::update( int elapsedMilliseconds )
{
    if( d->updateFunction )
    {
        d->updateFunction->evaluate();

        if( d->updateFunction->hasError() )
        {
            debug( d->updateFunction->error().toString() );
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

    delete d->updateFunction;
    d->updateFunction = 0;
}

void UiManagerComponent::setUi(UiAsset* ui)
{
    d->ui = ui;
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