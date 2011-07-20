#ifndef PERCEPTIONATOMPRIVATE_H
#define PERCEPTIONATOMPRIVATE_H

#include <QtCore/QSharedData>

class btPerceptionAtom;

namespace GluonEngine
{
	class PerceptionInfo;
	
	class PerceptionAtomPrivate : public QSharedData
	{
		public:
			PerceptionAtomPrivate();
			PerceptionAtomPrivate(const PerceptionAtomPrivate& other );
			~PerceptionAtomPrivate();
			
			btPerceptionAtom * atom;
                        GluonEngine::PerceptionInfo * info;
	};
}

#endif
