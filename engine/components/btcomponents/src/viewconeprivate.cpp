#include "viewconeprivate.h"

#include <QtCore/QObject>

using namespace BehaviorTree;

ViewConePrivate::ViewConePrivate()
	: QSharedData()
{

}

ViewConePrivate::ViewConePrivate(const ViewConePrivate& other)
	: QSharedData(other)
	, viewcone(other.viewcone)
{

}


ViewConePrivate::~ViewConePrivate()
{
}


