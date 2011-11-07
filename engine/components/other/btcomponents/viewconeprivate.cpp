#include "viewconeprivate.h"

#include <QtCore/QObject>

using namespace GluonEngine;

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


