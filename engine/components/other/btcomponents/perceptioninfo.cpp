#include "perceptioninfo.h"

#include "perceptioninfoprivate.h"
#include "btperceptioninfoscriptable.h"
#include <QtScript/QScriptEngine>
#include <QtCore/QDebug>
#include <QtCore/QMimeData>
#include <engine/gameobject.h>
#include <engine/game.h>

REGISTER_OBJECTTYPE(GluonEngine, PerceptionInfo)

using namespace GluonEngine;

PerceptionInfo::PerceptionInfo(QObject* parent)
	: Component(parent)
{
	d = new PerceptionInfoPrivate(this);
	connect(this,SIGNAL(infoUpdated()), d->info, SIGNAL(infoUpdated()));
}

PerceptionInfo::PerceptionInfo(const PerceptionInfo& other, QObject* parent)
	: Component(parent)
	, d(other.d)
{

}

PerceptionInfo::~PerceptionInfo()
{

}

QVector3D PerceptionInfo::position() const
{
	return d->info->position();
}

void PerceptionInfo::setPosition(const QVector3D& newPosition)
{
	d->info->setPosition(newPosition);
}
        
qreal PerceptionInfo::radius() const
{
	return d->info->radius();
}

void PerceptionInfo::setRadius(const qreal& newRadius)
{
	d->info->setRadius(newRadius);
}

btPerceptionInfo* PerceptionInfo::getBtPerceptionInfo()
{
	return d->info;
}

void PerceptionInfo::initialize()
{
    if (!d->script) return;

    d->script->load();

    if (d->script->data()->hasText())
    {
        d->engine.evaluate(d->script->data()->text(), gameObject()->name());
        if (d->engine.uncaughtException().isValid())
        {
            qDebug() << d->engine.uncaughtException().toString();
            qDebug() << d->engine.uncaughtExceptionBacktrace().join(" ");
            return;
        }

        QScriptValue component = d->engine.newQObject(this, QScriptEngine::QtOwnership, QScriptEngine::AutoCreateDynamicProperties);
        d->engine.globalObject().setProperty("Component", component);

        QScriptValue gameObj = d->engine.newQObject(gameObject(), QScriptEngine::QtOwnership, QScriptEngine::AutoCreateDynamicProperties);
        d->engine.globalObject().setProperty("GameObject", gameObj);

        QScriptValue game = d->engine.newQObject(GluonEngine::Game::instance(), QScriptEngine::QtOwnership, QScriptEngine::AutoCreateDynamicProperties);
        d->engine.globalObject().setProperty("Game", game);

        d->updateFunc = d->engine.globalObject().property("update");
        d->drawFunc = d->engine.globalObject().property("draw");
		d->getAdjustedValueFunc = d->engine.globalObject().property("getAdjustedValue");
        
        QScriptValue initFunc = d->engine.globalObject().property("initialize");
        if (initFunc.isFunction())
        {
            initFunc.call(QScriptValue());
            if (d->engine.uncaughtException().isValid())
            {
                qDebug() << d->engine.uncaughtException().toString();
                qDebug() << d->engine.uncaughtExceptionBacktrace().join(" ");
            }
        }
    }
}

void PerceptionInfo::start()
{
    if(d->script)
    {
        QScriptValue startFunc = d->engine.globalObject().property("start");
        if (startFunc.isFunction())
        {
            startFunc.call(QScriptValue());
            if (d->engine.uncaughtException().isValid())
            {
                debug(QString("%1: %2").arg(d->engine.uncaughtException().toString()).arg(d->engine.uncaughtExceptionBacktrace().join(" ")));
            }
        }
    }
}

void PerceptionInfo::draw(int timeLapse)
{
    if(d->drawFunc.isFunction())
    {
        d->drawFunc.call(QScriptValue(), QScriptValueList() << timeLapse);
        if (d->engine.uncaughtException().isValid())
        {
            debug(QString("%1: %2").arg(d->engine.uncaughtException().toString()).arg(d->engine.uncaughtExceptionBacktrace().join(" ")));
        }
    }
}

void PerceptionInfo::update(int elapsedMilliseconds)
{
    if(d->updateFunc.isFunction())
    {
        d->updateFunc.call(QScriptValue(), QScriptValueList() << elapsedMilliseconds);
        if (d->engine.uncaughtException().isValid())
        {
            qDebug() << d->engine.uncaughtException().toString();
            qDebug() << d->engine.uncaughtExceptionBacktrace().join(" ");
        }
    }
}

void PerceptionInfo::stop()
{
    if(d->script)
    {
        QScriptValue stopFunc = d->engine.globalObject().property("stop");
        if (stopFunc.isFunction())
        {
            stopFunc.call(QScriptValue());
            if (d->engine.uncaughtException().isValid())
            {
                debug(QString("%1: %2").arg(d->engine.uncaughtException().toString()).arg(d->engine.uncaughtExceptionBacktrace().join(" ")));
            }
        }
    }
}

void PerceptionInfo::cleanup()
{
    if(d->script)
    {
        QScriptValue cleanupFunc = d->engine.globalObject().property("cleanup");
        if (cleanupFunc.isFunction())
        {
            cleanupFunc.call(QScriptValue());
            if (d->engine.uncaughtException().isValid())
            {
                debug(QString("%1: %2").arg(d->engine.uncaughtException().toString()).arg(d->engine.uncaughtExceptionBacktrace().join(" ")));
            }
        }
    }
}

GluonEngine::Asset* PerceptionInfo::script()
{
    return d->script;
}

void PerceptionInfo::setScript(GluonEngine::Asset* asset)
{
    d->script = asset;
}

QVariant PerceptionInfo::getAdjustedValue(qreal precision)
{
	if(d->getAdjustedValueFunc.isFunction())
    {
        d->getAdjustedValueFunc.call(QScriptValue(), QScriptValueList() << precision);
        if (d->engine.uncaughtException().isValid())
        {
            debug(QString("%1: %2").arg(d->engine.uncaughtException().toString()).arg(d->engine.uncaughtExceptionBacktrace().join(" ")));
			return QVariant();
        }
        else
		{
			return this->property(QString("adjustedValue").toUtf8());
		}
    }
}

#include "perceptioninfo.moc"
