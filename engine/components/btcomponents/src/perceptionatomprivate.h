#ifndef PERCEPTIONATOMPRIVATE_H
#define PERCEPTIONATOMPRIVATE_H

#include <QtCore/QSharedData>

class btPerceptionAtom;

namespace BehaviorTree
{
	class PerceptionInfo;
	
	class PerceptionAtomPrivate : public QSharedData
	{
		public:
			PerceptionAtomPrivate();
			PerceptionAtomPrivate(const PerceptionAtomPrivate& other );
			~PerceptionAtomPrivate();
			
			btPerceptionAtom * atom;
			BehaviorTree::PerceptionInfo * info;
	};
}

#endif