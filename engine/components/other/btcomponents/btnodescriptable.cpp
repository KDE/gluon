#include "btnodescriptable.h"

#include <QtScript/QScriptEngine>
#include <QtCore/QMimeData>
#include <engine/gameobject.h>
#include <QtCore/QDebug>
#include <engine/game.h>
#include "btcharacterscriptable.h"
#include "character.h"
#include <engine/scene.h>

using namespace GluonEngine;

Q_DECLARE_METATYPE(btNode::status)

void qtscript_initialize_com_trolltech_qt_gui_bindings(QScriptValue &);
class btNodeScriptable::btNodeScriptablePrivate
{
	public:
		btNodeScriptablePrivate()
		{
            QScriptValue extensionObject = engine.globalObject();
            qtscript_initialize_com_trolltech_qt_gui_bindings(extensionObject);
            script = 0;
		}
		
		~btNodeScriptablePrivate()
		{
		}
		
		QScriptEngine engine;
		GluonEngine::Asset * script;
		QScriptValue runFunc;
        Character * character;
};

btNodeScriptable::btNodeScriptable(Character * character)
{
	d = new btNodeScriptablePrivate();
    d->character = character;
}

btNodeScriptable::~btNodeScriptable()
{
	delete d;
}

btNode::status btNodeScriptable::run(btCharacter* self)
{
	QScriptValue character = d->engine.newQObject(self, QScriptEngine::QtOwnership, QScriptEngine::AutoCreateDynamicProperties);
	d->engine.globalObject().setProperty("Character", character);
    
    QScriptValue component = d->engine.newQObject(d->character, QScriptEngine::QtOwnership, QScriptEngine::AutoCreateDynamicProperties);
    d->engine.globalObject().setProperty("Component", component);
    
     QScriptValue gameObj = d->engine.newQObject(d->character->gameObject(), QScriptEngine::QtOwnership, QScriptEngine::AutoCreateDynamicProperties);
    d->engine.globalObject().setProperty("GameObject", gameObj);
    
    QScriptValue btnode = d->engine.newQObject(this, QScriptEngine::QtOwnership, QScriptEngine::AutoCreateDynamicProperties);
    d->engine.globalObject().setProperty("Node", btnode);
    
    QScriptValue scene = d->engine.newQObject(GluonEngine::Game::instance()->currentScene()->sceneContents(), QScriptEngine::QtOwnership, QScriptEngine::AutoCreateDynamicProperties);
    d->engine.globalObject().setProperty("Scene", scene);
    
    QScriptValue game = d->engine.newQObject(GluonEngine::Game::instance(), QScriptEngine::QtOwnership, QScriptEngine::AutoCreateDynamicProperties);
    d->engine.globalObject().setProperty("Game", game);
	
	if(d->runFunc.isFunction())
	{
		d->runFunc.call();
		if (d->engine.uncaughtException().isValid())
        {
            d->character->debug(QString("%1: %2").arg(d->engine.uncaughtException().toString()).arg(d->engine.uncaughtExceptionBacktrace().join(" ")));
        }
	}
	
    return (btNode::status)this->property(QString("status").toUtf8()).toInt();
}

void btNodeScriptable::setScriptAsset(GluonEngine::Asset * asset)
{
	d->script = asset;

    d->script->load();

    if (d->script->data()->hasText())
    {
        d->engine.evaluate(d->script->data()->text(), this->className());
        if (d->engine.uncaughtException().isValid())
        {
            d->character->debug(QString("%1: %2").arg(d->engine.uncaughtException().toString()).arg(d->engine.uncaughtExceptionBacktrace().join(" ")));
            return;
        }
        
        d->runFunc = d->engine.globalObject().property("run");
    }
}

#include "btnodescriptable.moc"
