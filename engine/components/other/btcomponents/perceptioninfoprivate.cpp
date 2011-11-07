#include "perceptioninfoprivate.h"

#include "btperceptioninfoscriptable.h"

using namespace GluonEngine;

PerceptionInfoPrivate::PerceptionInfoPrivate(QObject * parent)
	: QSharedData()
{
	info = new btPerceptionInfoScriptable(parent);
	QScriptValue extensionObject = engine.globalObject();
	script = 0;
}

PerceptionInfoPrivate::PerceptionInfoPrivate(const PerceptionInfoPrivate& other)
	: QSharedData()
	, info(other.info)
	, drawFunc(other.drawFunc)
	, updateFunc(other.updateFunc)
	, getAdjustedValueFunc(other.getAdjustedValueFunc)
	, script(other.script)
{
	QScriptValue extensionObject = engine.globalObject();
}

PerceptionInfoPrivate::~PerceptionInfoPrivate()
{
}
