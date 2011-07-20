#ifndef BTPERCEPTIONINFOSCRIPTABLE_H
#define BTPERCEPTIONINFOSCRIPTABLE_H

#include <engine/gluon_engine_export.h>
#include <smarts/lib/btperceptioninfo.h>

namespace GluonEngine
{
	class BTCOMPONENT_EXPORT btPerceptionInfoScriptable : public btPerceptionInfo
	{
		Q_OBJECT
		public:
			btPerceptionInfoScriptable(QObject* parent);
			~btPerceptionInfoScriptable();
			
			virtual QVariant getAdjustedValue(qreal precision) const;
	};
}

#endif
