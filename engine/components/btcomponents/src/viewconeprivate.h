#ifndef VIEWCONEPRIVATE_H
#define VIEWCONEPRIVATE_H

#include <QtCore/QSharedData>

class btPerceptionViewcone;

namespace BehaviorTree
{
    class ViewConePrivate : public QSharedData
    {
	    public:
		ViewConePrivate();
		ViewConePrivate(const ViewConePrivate& other);
		~ViewConePrivate();
		
		btPerceptionViewcone * viewcone;
    };
}

#endif