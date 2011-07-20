#ifndef PERCEPTIONINFOPRIVATE_H
#define PERCEPTIONINFOPRIVATE_H

#include <QtCore/QSharedData>
#include <engine/asset.h>
#include <QtScript/QScriptEngine>
#include <QtCore/QDebug>

namespace GluonEngine
{
	class btPerceptionInfoScriptable;
	
	class PerceptionInfoPrivate : public QSharedData
	{
		public:
			PerceptionInfoPrivate(QObject * parent = 0);
			PerceptionInfoPrivate(const PerceptionInfoPrivate& other );
			~PerceptionInfoPrivate();
			
			btPerceptionInfoScriptable * info;
			QScriptEngine engine;

			QScriptValue drawFunc;
			QScriptValue updateFunc;
			QScriptValue getAdjustedValueFunc;

			GluonEngine::Asset* script;
	};
}

#endif
