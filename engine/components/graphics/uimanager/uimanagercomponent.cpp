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
#include <graphics/renderwidget.h>
#include <graphics/materialinstance.h>
#include <engine/gameobject.h>
#include <engine/asset.h>

#include <QtCore/QMimeData>
#include <QtCore/QVariant>
#include <QtGui/QMatrix4x4>
#include <QtGui/QColor>
#include <QtGui/QGraphicsView>
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsWidget>
#include <QtGui/QPixmap>
#include <QtOpenGL/QGLFramebufferObject>
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
        UiManagerComponentPrivate()
            : view(new QGraphicsView())
            , scene(new QGraphicsScene())
            , ui(0)
            , updateFunction(0)
        {
        }

        QPixmap pixmap;
        QGraphicsView* view;
        QGraphicsScene* scene;
        UiAsset *ui;
        QSizeF size;
        Item *item;
        EngineAccess* engineAccess;

        QDeclarativeExpression *updateFunction;
};

UiManagerComponent::UiManagerComponent( QObject* parent )
    : Component( parent )
    , d( new UiManagerComponentPrivate )
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
    QGLWidget* widget = GluonGraphics::Engine::instance()->renderWidget();
//     d->fbo = GluonGraphics::Engine::instance()->fbo();
    d->pixmap = QPixmap( widget->size() );
    d->pixmap.fill( Qt::transparent );
//     d->view->setParent(widget->parentWidget());
//     d->view->setAttribute(Qt::WA_TranslucentBackground);
//     d->view->setAttribute(Qt::WA_NoSystemBackground);
//     d->view->viewport()->setAttribute(Qt::WA_TranslucentBackground);
//     d->view->viewport()->setAttribute(Qt::WA_NoSystemBackground);
//     d->view->setStyleSheet("border: none");
//     QPalette p = d->view->viewport()->palette();
//     p.setColor(QPalette::Base, Qt::transparent);
//     d->view->viewport()->setPalette(p);
//     d->view->setScene(d->scene);
//     d->view->setSceneRect(QRectF(0,0,1000,1000));
    d->scene->setSceneRect(QRectF(QPointF(0,0), widget->size()));
//     d->view->resize(widget->size());
//     d->view->show();
//     d->scene->setBackgroundBrush(Qt::blue);

//     d->texture = widget->bindTexture(d->pixmap);
//     widget->update();
//     widget->updateGL();
//     widget->makeCurrent();
    if( d->ui && !d->ui->isLoaded() )
    {
        qmlRegisterType<GluonEngine::GameObject>("org.kde.gluon", 1, 0, "GameObject" );
        qmlRegisterInterface<GluonEngine::GameObject>("gameObject");

        d->ui->load();

        QDeclarativeEngine* engine = d->ui->engine();

        d->engineAccess = new EngineAccess(this);
        engine->rootContext()->setContextProperty( "__engineAccess", d->engineAccess );

        //Glorious hack:steal the engine
        QDeclarativeExpression *expr = new QDeclarativeExpression( engine->rootContext(), d->ui->widget(),
                                                                   "__engineAccess.setEngine( this )" );
        expr->evaluate();
        delete expr;

        start();
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

    qScriptRegisterQObjectMetaType<GameObject*>( engine );
    qScriptRegisterQObjectMetaType<GluonObject*>( engine );

    QScriptEngine::QObjectWrapOptions wrapOptions = QScriptEngine::AutoCreateDynamicProperties | QScriptEngine::ExcludeDeleteLater | QScriptEngine::PreferExistingWrapperObject;
    QScriptEngine::ValueOwnership ownership = QScriptEngine::QtOwnership;

    QScriptValue gameObj = engine->newQObject( gameObject(), ownership, wrapOptions );
    engine->globalObject().setProperty( "GameObject", gameObj );

    delete d->engineAccess;
    d->ui->engine()->rootContext()->setContextProperty( "__engineAccess", 0 );
}

void UiManagerComponent::start()
{
    if( d->ui && d->ui->isLoaded() )
    {
        d->ui->execute();

        d->updateFunction = new QDeclarativeExpression( d->ui->engine()->rootContext(),
                                                        d->ui->widget(), "update()" );

        QGraphicsWidget* widget = d->ui->widget();
        if( widget )
        {
            d->scene->addItem( widget );
//             widget->setGeometry( 0, 0, 100, 100 );
        }
    }
}

void UiManagerComponent::draw( int timeLapse )
{
    Q_UNUSED( timeLapse )

    RenderWidget* widget = GluonGraphics::Engine::instance()->renderWidget();

    d->pixmap.fill( Qt::transparent );
    QPainter p( &d->pixmap );

    d->scene->render( &p );
    widget->setPixmap(d->pixmap);
}

void UiManagerComponent::update( int elapsedMilliseconds )
{
    if( d->ui && d->ui->isLoaded() )
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

    QGraphicsWidget* widget = d->ui->widget();
    if( d->scene && widget && widget->scene() == d->scene )
    {
//         d->scene->removeItem( widget );
    }

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
